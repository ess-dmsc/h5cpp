//
// (c) Copyright 2017 DESY,ESS
//               2021 Eugen Wintersberger <eugen.wintersberger@gmail.com>
//
// This file is part of h5pp.
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
//
// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty ofMERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the
// Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor
// Boston, MA  02110-1301 USA
// ===========================================================================
//
// Author: Martin Shetty <martin.shetty@esss.se>
//         Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Sep 13, 2017
//

/*

 Summary of test results

  hid does not uniquely identify an h5 node

  object_address is stable across all scenarios

  file_number:
     not equal if same file closed and reopened
     identifies the file that owns object, not owner of link (in case of ext
 link)

  file_name:
     not equal if file opened via symbolic link (h5 allows opening same file
 twice) not equal if object opened via external link vs. original node


  Conclusions:
    file_number adequately reflects identity, unless file has been closed and
 reopened. file_name does not adequately reflect identity. Resolving symbolic
 link would solve part of the problem, but would also need to somehow
 dereference external links to identify the name of the object-owning file.

*/
#include <catch2/catch.hpp>
#include <h5cpp/core/filesystem.hpp>
#include <h5cpp/core/hdf5_capi.hpp>
#include <h5cpp/core/object_handle.hpp>
#include <h5cpp/core/object_id.hpp>
#include <h5cpp/core/types.hpp>
#include <h5cpp/property/property_list.hpp>
#include <iostream>
#include <tuple>

using namespace hdf5;

namespace {
hid_t to_hid(const ObjectHandle& handle) {
  return static_cast<hid_t>(handle);
}
ObjectHandle h5f_create(const fs::path& path) {
  hid_t id = H5Fcreate(path.string().data(), H5F_ACC_TRUNC, hdf5::property::kDefault, hdf5::property::kDefault);
  return ObjectHandle(id);
}

ObjectHandle h5g_create(const ObjectHandle& parent, const std::string& name) {
  return ObjectHandle(H5Gcreate(to_hid(parent), name.data(), hdf5::property::kDefault,
                                hdf5::property::kDefault, hdf5::property::kDefault));
}

auto open = [](const fs::path& p) {
  return H5Fopen(p.string().data(), H5F_ACC_RDONLY, hdf5::property::kDefault);
};

auto openrw = [](const fs::path& p) {
  return H5Fopen(p.string().data(), H5F_ACC_RDWR, hdf5::property::kDefault);
};

void hard_link(const ObjectHandle& parent,
               const std::string& orig_path,
               const std::string& link_path) {
  REQUIRE(H5Lcreate_hard(to_hid(parent), orig_path.data(), to_hid(parent),
                         link_path.data(), hdf5::property::kDefault, hdf5::property::kDefault) >= 0);
}

void soft_link(const ObjectHandle& parent,
               const std::string& orig_path,
               const std::string& link_path) {
  REQUIRE(H5Lcreate_soft(orig_path.data(), to_hid(parent), link_path.data(),
                         hdf5::property::kDefault, hdf5::property::kDefault) >= 0);
}
struct File {
  fs::path file_path;
  ObjectHandle file;
  ObjectHandle group1;
  ObjectHandle group2;
  ObjectHandle dataset;

  File(const fs::path& path)
      : file_path{path},
        file{h5f_create(file_path)},
        group1{h5g_create(file, "/group1")},
        group2{h5g_create(file, "/group2")},
        dataset{} {
    Dimensions dims{3, 3};
    ObjectHandle space(
        H5Screate_simple(static_cast<int>(dims.size()), dims.data(), nullptr));
    dataset = ObjectHandle(H5Dcreate(
        to_hid(group1), "dset1", H5T_NATIVE_DOUBLE,
        to_hid(space), hdf5::property::kDefault, hdf5::property::kDefault, hdf5::property::kDefault));
  }
};
}

SCENARIO("testing Id construction") {
  const auto path1 = fs::absolute(std::string("id_construction.h5"));
  GIVEN("a default constructed id") {
    ObjectId id;
    THEN("the file number must be 0") { REQUIRE(id.file_number() == 0l); }
    THEN("the objects' address must be 0") {
      REQUIRE(id.object_address() == 0l);
    }
    THEN("the filename must be an empty string") {
      REQUIRE(id.file_name().empty());
    }
    AND_GIVEN("a default constructed handle") {
      ObjectHandle handle;
      WHEN("constructing a new ID from this handle") {
        ObjectId id2(handle);
        THEN("this id must be equal to the default constructed id") {
          REQUIRE(id == id2);
        }
      }
      THEN("retrieving the file name from this handle must fail") {
        REQUIRE_THROWS_AS(ObjectId::get_file_name(handle), std::runtime_error);
      }
      THEN("retrieving the info instance from this handle must fail") {
        REQUIRE_THROWS_AS(ObjectId::get_info(handle), std::runtime_error);
      }
    }
  }

  GIVEN("a single HDF5 file with some content") {
    File file1(path1);
    WHEN("constructing an id from the handle to group1") {
      ObjectId id(file1.group1);
      THEN("we can retrieve the filename from this id instance") {
        REQUIRE(id.file_name() == path1);
      }
    }
  }
  fs::remove(path1);
}

SCENARIO("testing info retrievel from a file") {
  const fs::path path1 = fs::absolute("info_from_file.h5");
  GIVEN("an HDF5 file with some content") {
    File file1(path1);
    THEN("we can obtain the filename") {
      REQUIRE(ObjectId::get_file_name(file1.group1) == path1);
    }
    THEN("we can obtain object info via that id") {
      REQUIRE_NOTHROW(ObjectId::get_info(file1.group1));
    }
  }
  fs::remove(path1);
}
SCENARIO("working with links") {
  const fs::path path1 = fs::absolute("working_with_links_1.h5");
  GIVEN("a file object with a group and a dataset") {
    File file1(path1);
    ObjectId id_group1(file1.group1);
    ObjectId id_dataset(file1.dataset);

    GIVEN("a hard link to group1 with name group3") {
      hard_link(file1.file, "/group1", "/group3");
      AND_GIVEN("an id to group3") {
        ObjectHandle g(H5Gopen(to_hid(file1.file), "/group3", hdf5::property::kDefault));
        THEN("the handles must not be equal") {
          REQUIRE(to_hid(g) != to_hid(file1.group1));
        }
        WHEN("constructing an id from this handle") {
          ObjectId id(g);
          THEN("all id attributes must be equal") {
            REQUIRE(id_group1.file_name() == id.file_name());
            REQUIRE(id_group1 == id);
          }
        }
      }
    }
    GIVEN("a soft link to group1 with name group4") {
      soft_link(file1.file, "/group1", "/group4");
      AND_GIVEN("a handle to group4") {
        ObjectHandle g(H5Gopen(to_hid(file1.file), "/group4", hdf5::property::kDefault));
        THEN("the handles to group4 and group1 must be different") {
          REQUIRE(to_hid(g) != to_hid(file1.group1));
        }
        WHEN("constructing an id from this handle") {
          ObjectId id(g);
          THEN("all the ID parameters must match the original") {
            REQUIRE(id_group1.file_name() == id.file_name());
            REQUIRE(id_group1 == id);
          }
        }
      }
    }
    GIVEN("a hard link to dset1 of name dset2") {
      hard_link(file1.file, "/group1/dset1", "/group2/dset2");
      AND_GIVEN("a handle to /group2/dset2") {
        ObjectHandle d(H5Dopen(to_hid(file1.group2), "dset2", hdf5::property::kDefault));
        THEN("handles must not be equal") {
          REQUIRE(to_hid(d) != to_hid(file1.dataset));
        }
        WHEN("constructing and id from this handle") {
          ObjectId id(d);
          THEN("all id parameters must be equal") {
            REQUIRE(id_dataset.file_name() == id.file_name());
            REQUIRE(id_dataset == id);
          }
        }
      }
    }
    GIVEN("a soft link to dset1 of name /group2/dset3") {
      soft_link(file1.file, "/group1/dset1", "/group2/dset3");
      AND_GIVEN("a handle to /group2/dset3") {
        ObjectHandle d(H5Dopen(to_hid(file1.group2), "dset3", hdf5::property::kDefault));
        THEN("handles must not be equal") {
          REQUIRE(to_hid(d) != to_hid(file1.dataset));
        }
        WHEN("constructing an id from this handle") {
          ObjectId id(d);
          THEN("all id parameters must be equal") {
            REQUIRE(id_dataset.file_name() == id.file_name());
            REQUIRE(id_dataset == id);
          }
        }
      }
    }
  }
  fs::remove(path1);
}

SCENARIO("checking copies and files of identical structure") {
  auto path1 = fs::absolute("cp_and_id_structs_1.h5");
  auto path2 = fs::absolute("cp_and_id_structs_2.h5");
  auto path3 = fs::absolute("cp_and_id_structs_3.h5");
  {
    // create two files with identical structure
    File{path1};
    File{path2};
  }

  // create a copy of the first file.
  #ifdef H5CPP_WITH_BOOST
  fs::copy_file(path1, path3,
                fs::copy_option::overwrite_if_exists);
#else
  std::cout<<path1<<std::endl;
  std::cout<<path2<<std::endl;
  std::cout<<path3<<std::endl;
  fs::copy_file(path1, path3, fs::copy_options::overwrite_existing);
#endif

  using files_t = std::tuple<fs::path, fs::path>;
  auto files = GENERATE_REF(
      table<fs::path, fs::path>({files_t{path1, path2},
                                 files_t{path1, path3}}));
  GIVEN("a handle to group 1 in the first file") {
    ObjectHandle file1{open(std::get<0>(files))};
    ObjectHandle g_file1(H5Gopen(to_hid(file1), "/group1", hdf5::property::kDefault));
    AND_GIVEN("a handle to group 1 in the second file") {
      ObjectHandle file2{open(std::get<1>(files))};
      ObjectHandle g_file2(H5Gopen(to_hid(file2), "/group1", hdf5::property::kDefault));
      THEN("we expect the two handles to be different") {
        REQUIRE(to_hid(g_file1) != to_hid(g_file2));
      }
      WHEN("constructing ids from this group handles") {
        ObjectId id_file1(g_file1);
        ObjectId id_file2(g_file2);
        THEN("the file names must be different") {
          REQUIRE(id_file1.file_name() != id_file2.file_name());
        }
        THEN("the file number must be different") {
          REQUIRE(id_file1.file_number() != id_file2.file_number());
        }
        THEN("the object address in the file must be equal") {
          REQUIRE(id_file1.object_address() == id_file2.object_address());
        }
      }
    }
  }
  fs::remove(path1);
  fs::remove(path2);
  fs::remove(path3);
}

#ifndef _MSC_VER
// Symbolic link (in OS) is made FILE2 -> FILE1
//   only file_number and object_address are equal
//   file_name is not equal
SCENARIO("testing symbolic links") {
  const fs::path path1 = fs::absolute("symbolic_links_1.h5");
  const fs::path path2 = fs::absolute("symbolic_links_2.h5");
  { File{path1}; }

  // Symlink FILE2 -> FILE1
  fs::create_symlink(path1, path2);

  REQUIRE(fs::canonical(path1) == fs::canonical(path2));
  GIVEN("a handler to the first group in the original file") {
    ObjectHandle orig(open(path1));
    ObjectHandle link(open(path2));
    ObjectHandle g_orig(H5Gopen(to_hid(orig), "/group1", hdf5::property::kDefault));
    AND_GIVEN("a handle to the group in the symbolic link") {
      ObjectHandle g_link(H5Gopen(to_hid(link), "/group1", hdf5::property::kDefault));
      THEN("the two handle must be different") {
        REQUIRE(to_hid(g_orig) != to_hid(g_link));
      }
      WHEN("constructing Ids for the the two handles") {
        ObjectId id_orig(g_orig);
        ObjectId id_link(g_link);
        THEN("the file names must be different") {
          REQUIRE(id_orig.file_name() != id_link.file_name());
        }
        THEN("the ids must be equal") { REQUIRE(id_orig == id_link); }
      }
    }
  }
  fs::remove(path1);
  fs::remove(path2);
}
#endif

static void external_link(const fs::path& target_file,
                   const std::string& target_path,
                   const ObjectHandle& link_file,
                   const std::string& link_path) {
  REQUIRE(H5Lcreate_external(target_file.string().data(), target_path.c_str(),
                             to_hid(link_file), link_path.c_str(), hdf5::property::kDefault,
                             hdf5::property::kDefault) >= 0);
}

SCENARIO("testing with external links") {
  const fs::path path1 = fs::absolute("external_links_1.h5");
  const fs::path path2 = fs::absolute("external_links_2.h5");
  {
    File{path1};
    File{path2};
  }

  // Extlink file2/group3 -> file1/group1
  GIVEN("an external link in file2 to group1 in file1") {
    ObjectHandle file2(openrw(path2));
    external_link(path1, "/group1", file2, "/group3");
    AND_GIVEN("a handle to this external link group in file") {
      ObjectHandle linked(H5Gopen(to_hid(file2), "/group3", hdf5::property::kDefault));
      AND_GIVEN("a handle to the original group in the first file") {
        ObjectHandle file1(open(path1));
        ObjectHandle original(H5Gopen(to_hid(file1), "/group1", hdf5::property::kDefault));
        THEN("the two handles must be different") {
          REQUIRE(linked != original);
        }
        WHEN("creating the ids from this to handles") {
          ObjectId id_original(original);
          ObjectId id_linked(linked);
          THEN("all attributes of the ids must be equal") {
            REQUIRE(id_original.file_number() == id_linked.file_number());
            REQUIRE(id_original.file_name() == id_linked.file_name());
            REQUIRE(id_original.object_address() == id_linked.object_address());
          }
        }
      }
    }
  }

  fs::remove(path1);
  fs::remove(path2);
}

#ifndef _MSC_VER
// Symbolic link (in OS) is made FILE3 -> FILE1
// External link is made file2/group3 -> File3/group1
//   only file_number and object_address are equal
//   file_name is not equal
SCENARIO("testing wiht external synmbolic link") {
  const fs::path path1 = fs::absolute("ext_symlink_1.h5");
  const fs::path path2 = fs::absolute("ext_symlink_2.h5");
  const fs::path path3 = fs::absolute("ext_symlink_3.h5");
  {
    File{path1};
    File{path2};
  }

  // Symlink FILE3 -> FILE1
  fs::create_symlink(path1, path3);

  // Extlink file2/group3 -> file3/group1
  ObjectHandle file2(openrw(path2));
  external_link(path3, "/group1", file2, "/group3");
  ObjectHandle group23(H5Gopen(to_hid(file2), "/group3", hdf5::property::kDefault));

  // Original node
  ObjectHandle file1(open(path1));
  ObjectHandle group11(H5Gopen(to_hid(file1), "/group1", hdf5::property::kDefault));

  // Node in symlinked file
  ObjectHandle file3(open(path3));
  ObjectHandle group31(H5Gopen(to_hid(file3), "/group1", hdf5::property::kDefault));

  ObjectId info11(group11);
  ObjectId info31(group31);
  ObjectId info23(group23);

  REQUIRE(to_hid(group11) != to_hid(group31));
  REQUIRE(to_hid(group11) != to_hid(group23));
  REQUIRE(to_hid(group23) != to_hid(group31));

  REQUIRE(info11.file_name() != info31.file_name());
  REQUIRE(info31.file_name() == info23.file_name());
  REQUIRE(info11.file_name() != info23.file_name());

  REQUIRE(info11.file_number() == info31.file_number());
  REQUIRE(info11.file_number() == info23.file_number());
  REQUIRE(info31.file_number() == info23.file_number());

  REQUIRE(info11.object_address() == info31.object_address());
  REQUIRE(info11.object_address() == info23.object_address());
  REQUIRE(info31.object_address() == info23.object_address());

  fs::remove(path1);
  fs::remove(path2);
  fs::remove(path3);
}
#endif

SCENARIO("opening an instance serveral time") {
  const fs::path path1 = fs::absolute("open_several_times_1.h5");
  // This works because the ObjectId does not store any HDF5 object.
  // It only stores some metadata about an object.
  GIVEN("an id to the first file object") {
    ObjectId id1;
    {
      File file(path1);
      id1 = ObjectId(file.file);
    }
    AND_GIVEN("an id to the file object opend the second time") {
      ObjectId id2;
      {
        File file(path1);
        id2 = ObjectId(file.file);
      }
      THEN("the filenames must be equal") {
        REQUIRE(id1.file_name() == id2.file_name());
      }
      THEN("the file numbers must be different") {
        REQUIRE(id1.file_number() != id2.file_number());
      }
      THEN("the object addresses must be equal") {
        REQUIRE(id1.object_address() == id2.object_address());
      }
    }
  }
  fs::remove(path1);
}

SCENARIO("comparing ids") {
  const fs::path path1 = fs::absolute("cmp_ids_1.h5");
  const fs::path path2 = fs::absolute("cmp_ids_2.h5");
  ObjectId file1_id, file2_id, group1_id, group2_id;

  {
    File file1(path1);
    File file2(path2);

    file1_id = ObjectId(file1.file);
    file2_id = ObjectId(file2.file);
    group1_id = ObjectId(file2.group1);
    group2_id = ObjectId(file2.group2);
  }

  REQUIRE(file1_id == file1_id);
  REQUIRE(group1_id == group1_id);
  REQUIRE(file1_id != file2_id);
  REQUIRE(group1_id != group2_id);
  REQUIRE(file1_id != group1_id);
  REQUIRE(file1_id != group2_id);
  REQUIRE(file2_id != group1_id);
  REQUIRE(file2_id != group2_id);
  REQUIRE(file1_id < file2_id);
  REQUIRE_FALSE(file1_id < file1_id);
  REQUIRE_FALSE(file2_id < file1_id);
  REQUIRE_FALSE(group2_id < group1_id);
  REQUIRE(group1_id < group2_id);
  REQUIRE(file1_id < group1_id);
  REQUIRE(file2_id < group1_id);

  // remove the two HDF5 file as the yare no longer required
  fs::remove(path1);
  fs::remove(path2);
}
