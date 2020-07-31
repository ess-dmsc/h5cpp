//
// (c) Copyright 2017 DESY,ESS
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
// Created on: Sep 13, 2017
//


/*

 Summary of test results

  hid does not uniquely identify an h5 node

  object_address is stable across all scenarios

  file_number:
     not equal if same file closed and reopened
     identifies the file that owns object, not owner of link (in case of ext link)

  file_name:
     not equal if file opened via symbolic link (h5 allows opening same file twice)
     not equal if object opened via external link vs. original node


  Conclusions:
    file_number adequately reflects identity, unless file has been closed and reopened.
    file_name does not adequately reflect identity. Resolving symbolic link would solve
    part of the problem, but would also need to somehow dereference external links to
    identify the name of the object-owning file.

*/


#include <gtest/gtest.h>
#include <h5cpp/core/hdf5_capi.hpp>
#include <h5cpp/core/filesystem.hpp>
#include <h5cpp/core/object_id.hpp>
#include <h5cpp/core/object_handle.hpp>
#include <h5cpp/core/types.hpp>
#include <iostream>

static const fs::path kFilePath_1 = fs::absolute("file1.h5");
static const fs::path kFilePath_2 = fs::absolute("file2.h5");
static const fs::path kFilePath_3 = fs::absolute("file3.h5");

#define FILE1 fs::absolute("file1.h5").string().data()
#define FILE2 fs::absolute("file2.h5").string().data()
#define FILE3 fs::absolute("file3.h5").string().data()

using namespace hdf5;

class ObjectIdTest : public testing::Test
{
  public:
    ObjectIdTest() {}
    ~ObjectIdTest()
    {
      fs::remove(FILE1);
      fs::remove(FILE2);
      fs::remove(FILE3);
    }
};

struct FileGuard
{
    fs::path fs;
    ObjectHandle file_handle;
    ObjectHandle group1_handle;
    ObjectHandle group2_handle;
    ObjectHandle dataset_handle;

    FileGuard(const fs::path &path):
      fs{path},
      file_handle{},
      group1_handle{},
      group2_handle{},
      dataset_handle{}
    {
      file_handle = ObjectHandle(H5Fcreate(fs.string().data(),
                                           H5F_ACC_TRUNC,
                                           H5P_DEFAULT,
                                           H5P_DEFAULT));
      group1_handle = ObjectHandle(H5Gcreate(static_cast<hid_t>(file_handle),
                                             "/group1",
                                             H5P_DEFAULT,
                                             H5P_DEFAULT,
                                             H5P_DEFAULT));
      group2_handle = ObjectHandle(H5Gcreate(static_cast<hid_t>(file_handle),
                                             "/group2",
                                             H5P_DEFAULT,
                                             H5P_DEFAULT,
                                             H5P_DEFAULT));
      Dimensions dims{3,3};
      ObjectHandle space(H5Screate_simple(dims.size(),dims.data(),nullptr));
      dataset_handle = ObjectHandle(H5Dcreate(static_cast<hid_t>(group1_handle),
                                              "dset1",
                                              H5T_NATIVE_DOUBLE,
                                              static_cast<hid_t>(space),
                                              H5P_DEFAULT,
                                              H5P_DEFAULT,
                                              H5P_DEFAULT));
    }
};

struct OneFile
{
  OneFile(std::string fname)
  {
    fname_ = fname;
    file = H5Fcreate(fname.data(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    group1 = H5Gcreate(file, "/group1",
                       H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    group2 = H5Gcreate(file, "/group2",
                       H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    hsize_t dims[2];
    dims[0] = 3;
    dims[1] = 3;
    hid_t dataspace = H5Screate_simple(2, dims, NULL);

    dset1 = H5Dcreate(group1, "dset1", H5T_NATIVE_DOUBLE, dataspace,
                      H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  }

  ~OneFile()
  {
    H5Dclose(dset1);
    H5Gclose(group1);
    H5Gclose(group2);
    H5Fclose(file);
  }

  std::string fname_;
  hid_t file, group1, group2, dset1;
};

// Print
TEST_F(ObjectIdTest,  printing )
{
  FileGuard file1(kFilePath_1);
  ObjectId f1(file1.file_handle);

  std::stringstream ss;
  ss << f1;
  EXPECT_TRUE(!ss.str().empty());
}

TEST_F(ObjectIdTest,default_construction)
{
  ObjectId id;
  EXPECT_EQ(id.file_number(),0ul);
  EXPECT_EQ(id.object_address(),0ul);
  EXPECT_TRUE(id.file_name().empty());
}

TEST_F(ObjectIdTest, construction_from_invalid_handler)
{
  ObjectHandle handle;
  ObjectId id(handle);
  ObjectId id2;
  EXPECT_EQ(id, id2);
}

TEST_F(ObjectIdTest, get_file_name)
{
  FileGuard file1(kFilePath_1);
  EXPECT_EQ(ObjectId::get_file_name(file1.group1_handle), kFilePath_1);

  ObjectHandle handle;
  EXPECT_THROW(ObjectId::get_file_name(handle), std::runtime_error);
}

TEST_F(ObjectIdTest, get_info)
{
  FileGuard file1(kFilePath_1);
  EXPECT_NO_THROW(ObjectId::get_info(file1.group1_handle));

  ObjectHandle handle;
  EXPECT_THROW(ObjectId::get_info(handle), std::runtime_error);
}

TEST_F(ObjectIdTest,construction)
{
  FileGuard file1(kFilePath_1);
  ObjectId id(file1.group1_handle);

  EXPECT_EQ(id.file_name(),kFilePath_1);
}

// For h5 hard links (to group):
//   file_name, file_number and address are all equal
TEST_F(ObjectIdTest,  hard_group )
{
  FileGuard file1(kFilePath_1);

  //create a new hard link to group1 with the name group3
  //we use an assert here as we can break the test if this operation fails
  herr_t ret = H5Lcreate_hard(static_cast<hid_t>(file1.file_handle), "/group1",
                              static_cast<hid_t>(file1.file_handle), "/group3",
                              H5P_DEFAULT, H5P_DEFAULT);
  ASSERT_GE(ret,0);
  ObjectHandle group3_handle(H5Gopen(static_cast<hid_t>(file1.file_handle),
                                     "/group3", H5P_DEFAULT));

  ObjectId info1(file1.group1_handle);
  ObjectId info3(group3_handle);

  //the handler must not be equal - sanity check
  EXPECT_NE(static_cast<hid_t>(file1.group1_handle),
            static_cast<hid_t>(group3_handle));

  //everything else must be
  EXPECT_EQ(info1.file_name(), info3.file_name());
  EXPECT_EQ(info1.file_number(), info3.file_number());
  EXPECT_EQ(info1.object_address(), info3.object_address());
}

// For h5 hard links (to dataset):
//   file_name, file_number and address are all equal
TEST_F(ObjectIdTest,  hard_dset )
{
  FileGuard file1(kFilePath_1);

  herr_t ret = H5Lcreate_hard(static_cast<hid_t>(file1.group1_handle), "dset1",
                              static_cast<hid_t>(file1.group2_handle), "dset2",
                              H5P_DEFAULT, H5P_DEFAULT);
  ASSERT_GE(ret,0);
  ObjectHandle dset2(H5Dopen(static_cast<hid_t>(file1.group2_handle), "dset2",
                             H5P_DEFAULT));

  ObjectId info1(file1.dataset_handle);
  ObjectId info2(dset2);

  EXPECT_NE(static_cast<hid_t>(file1.dataset_handle),
            static_cast<hid_t>(dset2));
  EXPECT_EQ(info1.file_name(), info2.file_name());
  EXPECT_EQ(info1.file_number(), info2.file_number());
  EXPECT_EQ(info1.object_address(), info1.object_address());
}

// For h5 soft links (to group):
//   file_name, file_number and address are all equal
TEST_F(ObjectIdTest,  soft_group )
{
  FileGuard file1(kFilePath_1);

  herr_t ret = H5Lcreate_soft("/group1",
                              static_cast<hid_t>(file1.file_handle),
                              "/group3",
                              H5P_DEFAULT, H5P_DEFAULT);
  ASSERT_GE(ret,0);
  ObjectHandle group3(H5Gopen(static_cast<hid_t>(file1.file_handle),
                              "/group3", H5P_DEFAULT));

  ObjectId info1(file1.group1_handle);
  ObjectId info2(group3);

  EXPECT_NE(static_cast<hid_t>(file1.group1_handle),
            static_cast<hid_t>(group3));
  EXPECT_EQ(info1.file_name(), info2.file_name());
  EXPECT_EQ(info1.file_number(), info2.file_number());
  EXPECT_EQ(info1.object_address(), info1.object_address());
}

// For h5 soft links (to dataset):
//   file_name, file_number and address are all equal
TEST_F(ObjectIdTest,  soft_dset )
{
  FileGuard file1(kFilePath_1);

  herr_t ret = H5Lcreate_soft("/group1/dset1",
                              static_cast<hid_t>(file1.file_handle),
                              "/group2/dset2",
                              H5P_DEFAULT, H5P_DEFAULT);
  ASSERT_GE(ret,0);
  ObjectHandle dset2(H5Dopen(static_cast<hid_t>(file1.group2_handle),
                             "dset2", H5P_DEFAULT));

  ObjectId info1(file1.dataset_handle);
  ObjectId info2(dset2);

  EXPECT_NE(static_cast<hid_t>(file1.dataset_handle),
            static_cast<hid_t>(dset2));
  EXPECT_EQ(info1.file_name(), info2.file_name());
  EXPECT_EQ(info1.file_number(), info2.file_number());
  EXPECT_EQ(info1.object_address(), info1.object_address());
}

// If file copy is made:
//   only object addresses are equal
TEST_F(ObjectIdTest,  file_copy )
{
  //just to ensure everything gets destroyed after construction
  {
    FileGuard{kFilePath_1};
  }

  #ifdef WITH_BOOST
    fs::copy_file(kFilePath_1,kFilePath_2,
                  fs::copy_option::overwrite_if_exists);
  #else
    fs::copy_file(kFilePath_1,kFilePath_2,
                  fs::copy_options::overwrite_existing);
  #endif

  ObjectHandle file1(H5Fopen(kFilePath_1.string().data(),
                             H5F_ACC_RDONLY, H5P_DEFAULT));
  ObjectHandle file2(H5Fopen(kFilePath_2.string().data(),
                             H5F_ACC_RDONLY, H5P_DEFAULT));
  ObjectHandle group1(H5Gopen(static_cast<hid_t>(file1), "/group1", H5P_DEFAULT));
  ObjectHandle group2(H5Gopen(static_cast<hid_t>(file2), "/group1", H5P_DEFAULT));

  ObjectId info1(group1);
  ObjectId info2(group2);

  EXPECT_NE(static_cast<hid_t>(group1),
            static_cast<hid_t>(group2));
  EXPECT_NE(info1.file_name(), info2.file_name());
  EXPECT_NE(info1.file_number(), info2.file_number());
  EXPECT_EQ(info1.object_address(), info1.object_address());

}

// If 2 files are created with identical structure:
//   only object addresses are equal
TEST_F(ObjectIdTest,  file_copy2 )
{
  //just to ensure everything gets destroyed after construction
  {
    FileGuard{kFilePath_1};
    FileGuard{kFilePath_2};
  }

  ObjectHandle file1(H5Fopen(kFilePath_1.string().data(),
                             H5F_ACC_RDONLY, H5P_DEFAULT));
  ObjectHandle file2(H5Fopen(kFilePath_2.string().data(),
                             H5F_ACC_RDONLY, H5P_DEFAULT));
  ObjectHandle group1(H5Gopen(static_cast<hid_t>(file1), "/group1", H5P_DEFAULT));
  ObjectHandle group2(H5Gopen(static_cast<hid_t>(file2), "/group1", H5P_DEFAULT));

  ObjectId info1(group1);
  ObjectId info2(group2);

  EXPECT_NE(static_cast<hid_t>(group1),
            static_cast<hid_t>(group2));
  EXPECT_NE(info1.file_name(), info2.file_name());
  EXPECT_NE(info1.file_number(), info2.file_number());
  EXPECT_EQ(info1.object_address(), info1.object_address());
}

#ifndef _MSC_VER
// Symbolic link (in OS) is made FILE2 -> FILE1
//   only file_number and object_address are equal
//   file_name is not equal
TEST_F(ObjectIdTest,  symlink_id )
{
  {
    FileGuard{kFilePath_1};
  }

  // Symlink FILE2 -> FILE1
  fs::create_symlink(kFilePath_1,kFilePath_2);

  ObjectHandle file1(H5Fopen(kFilePath_1.string().data(), H5F_ACC_RDONLY, H5P_DEFAULT));
  ObjectHandle file2(H5Fopen(kFilePath_2.string().data(), H5F_ACC_RDONLY, H5P_DEFAULT));
  ObjectHandle group1(H5Gopen(static_cast<hid_t>(file1), "/group1", H5P_DEFAULT));
  ObjectHandle group2(H5Gopen(static_cast<hid_t>(file2), "/group1", H5P_DEFAULT));

  ObjectId info1(group1);
  ObjectId info2(group2);

  EXPECT_NE(static_cast<hid_t>(group1),
            static_cast<hid_t>(group2));
  EXPECT_NE(info1.file_name(), info2.file_name());
  EXPECT_EQ(info1.file_number(), info2.file_number());
  EXPECT_EQ(info1.object_address(), info1.object_address());

  EXPECT_EQ(fs::canonical(kFilePath_1),fs::canonical(kFilePath_2));
}
#endif

// If external link is made file2/group3 -> File1/group1
// All three parameters are equal
TEST_F(ObjectIdTest,  file_external_group )
{
  {
    FileGuard{kFilePath_1};
    FileGuard{kFilePath_2};
  }

  // Extlink file2/group3 -> file1/group1
  ObjectHandle file2(H5Fopen(kFilePath_2.string().data(), H5F_ACC_RDWR, H5P_DEFAULT));
  herr_t ret = H5Lcreate_external(kFilePath_1.string().data(), "/group1",
                                  static_cast<hid_t>(file2), "/group3",
                                  H5P_DEFAULT, H5P_DEFAULT);
  ASSERT_GE(ret,0);
  ObjectHandle group23(H5Gopen(static_cast<hid_t>(file2), "/group3", H5P_DEFAULT));

  // Original node
  ObjectHandle file1(H5Fopen(kFilePath_1.string().data(), H5F_ACC_RDONLY, H5P_DEFAULT));
  ObjectHandle group11(H5Gopen(static_cast<hid_t>(file1), "/group1", H5P_DEFAULT));

  ObjectId info11(group11);
  ObjectId info23(group23);

  EXPECT_NE(static_cast<hid_t>(group11),
            static_cast<hid_t>(group23));
  EXPECT_EQ(info11.file_number(), info23.file_number());
  EXPECT_EQ(info11.file_name(), info23.file_name());
  EXPECT_EQ(info11.object_address(), info23.object_address());
}

#ifndef _MSC_VER
// Symbolic link (in OS) is made FILE3 -> FILE1
// External link is made file2/group3 -> File3/group1
//   only file_number and object_address are equal
//   file_name is not equal
TEST_F(ObjectIdTest,  file_external_symlink )
{
  {
    FileGuard{kFilePath_1};
    FileGuard{kFilePath_2};
  }

  // Symlink FILE3 -> FILE1
  fs::create_symlink(kFilePath_1,kFilePath_3);

  // Extlink file2/group3 -> file3/group1
  ObjectHandle file2(H5Fopen(kFilePath_2.string().data(), H5F_ACC_RDWR, H5P_DEFAULT));
  herr_t ret = H5Lcreate_external(kFilePath_3.string().data(), "/group1",
                                  static_cast<hid_t>(file2), "/group3",
                                  H5P_DEFAULT, H5P_DEFAULT);
  ASSERT_GE(ret,0);
  ObjectHandle group23(H5Gopen(static_cast<hid_t>(file2), "/group3", H5P_DEFAULT));

  // Original node
  ObjectHandle file1(H5Fopen(kFilePath_1.string().data(), H5F_ACC_RDONLY, H5P_DEFAULT));
  ObjectHandle group11(H5Gopen(static_cast<hid_t>(file1), "/group1", H5P_DEFAULT));

  // Node in symlinked file
  ObjectHandle file3(H5Fopen(kFilePath_3.string().data(), H5F_ACC_RDONLY, H5P_DEFAULT));
  ObjectHandle group31(H5Gopen(static_cast<hid_t>(file3), "/group1", H5P_DEFAULT));

  ObjectId info11(group11);
  ObjectId info31(group31);
  ObjectId info23(group23);

  EXPECT_NE((static_cast<hid_t>(group11)),(static_cast<hid_t>(group31)));
  EXPECT_NE(static_cast<hid_t>(group11),static_cast<hid_t>(group23));
  EXPECT_NE(static_cast<hid_t>(group23),static_cast<hid_t>(group31));

  EXPECT_NE(info11.file_name(), info31.file_name());
  EXPECT_EQ(info31.file_name(), info23.file_name());
  EXPECT_NE(info11.file_name(), info23.file_name());

  EXPECT_EQ(info11.file_number(), info31.file_number());
  EXPECT_EQ(info11.file_number(), info23.file_number());
  EXPECT_EQ(info31.file_number(), info23.file_number());

  EXPECT_EQ(info11.object_address(), info31.object_address());
  EXPECT_EQ(info11.object_address(), info23.object_address());
  EXPECT_EQ(info31.object_address(), info23.object_address());
}
#endif

// If the same file is opened repeatedly:
//   file_name and object_address are equal
//   file_number is not equal
TEST_F(ObjectIdTest,  repeated_open )
{
  ObjectId id1;
  {
    FileGuard file(kFilePath_1);
    id1 = ObjectId(file.file_handle);
  }

  ObjectId id2;
  {
    FileGuard file(kFilePath_1);
    id2 = ObjectId(file.file_handle);
  }

  EXPECT_EQ(id1.file_name(), id2.file_name());
  EXPECT_NE(id1.file_number(), id2.file_number());
  EXPECT_EQ(id1.object_address(), id2.object_address());
}

// Sorting ObjectIds
TEST_F(ObjectIdTest,  comparison )
{
  ObjectId file1_id,file2_id,group1_id,group2_id;

  {
    FileGuard file1(kFilePath_1);
    FileGuard file2(kFilePath_2);

    file1_id = ObjectId(file1.file_handle);
    file2_id = ObjectId(file2.file_handle);
    group1_id = ObjectId(file2.group1_handle);
    group2_id = ObjectId(file2.group2_handle);
  }

  EXPECT_EQ(file1_id,file1_id);
  EXPECT_EQ(group1_id, group1_id);
  EXPECT_NE(file1_id,file2_id);
  EXPECT_NE(group1_id,group2_id);
  EXPECT_NE(file1_id,group1_id);
  EXPECT_NE(file1_id,group2_id);
  EXPECT_NE(file2_id,group1_id);
  EXPECT_NE(file2_id,group2_id);
  EXPECT_TRUE(file1_id < file2_id);
  EXPECT_FALSE(file1_id < file1_id);
  EXPECT_FALSE(file2_id < file1_id);
  EXPECT_FALSE(group2_id < group1_id);
  EXPECT_LT(group1_id, group2_id);
  EXPECT_LT(file1_id, group1_id);
  EXPECT_LT(file2_id, group1_id);
}


