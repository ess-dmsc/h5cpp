//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5cpp.
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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Martin Shetty <martin.shetty@esss.se>
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Sep 10, 2017
//

#include <catch2/catch.hpp>
#include <h5cpp/core/filesystem.hpp>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/node/group.hpp>
#include <h5cpp/contrib/stl/stl.hpp>

using namespace hdf5;

SCENARIO("Creating files", "[h5cpp,file]") {
  GIVEN("a newly created file with default property lists") {
    const fs::path file_path("./test1_with_a_much_longer_file_name.h5");
    auto f = file::create(file_path);

    THEN("it must be in read/write mode ") {
      REQUIRE(f.intent() == file::AccessFlags::ReadWrite);
      REQUIRE(f.path() == file_path);
    }
    f.close();  // close the file here - we no longer need ti

    WHEN("tyring to create a new file of same name without trunctation") {
      THEN("the operation must fail with an exception") {
        REQUIRE_THROWS_AS(file::create(file_path), std::runtime_error);
      }
    }

    WHEN("trying to create a new file with truncation") {
      REQUIRE_NOTHROW(file::create(file_path, file::AccessFlags::Truncate));
    }
    fs::remove(file_path);
  }
}

#ifndef _MSC_VER
SCENARIO("Opening the same file", "[h5cpp,file]") {
  {
    file::create("test1.h5", file::AccessFlags::Truncate);
    fs::create_symlink("test1.h5", "test1_link.h5");
  }
  GIVEN("a single file") {
    auto f1 = file::open("test1.h5", file::AccessFlags::ReadOnly);
    THEN("opening the same file") {
      auto f2 = file::open("test1.h5", file::AccessFlags::ReadOnly);
      REQUIRE(f1.id() == f2.id());
    }
    THEN("opnening the symbolic link to the file yields") {
      auto f2 = file::open("test1_link.h5", file::AccessFlags::ReadOnly);
      REQUIRE(f1.id() == f2.id());
    }
  }
  fs::remove("test1.h5");
  fs::remove("test1_link.h5");
}
#endif

SCENARIO("Open multiple files in several modes", "[file,h5cpp]") {
  {
    auto nexus_file = file::create("testclose.h5", file::AccessFlags::Truncate);
    nexus_file.root()
        .attributes
        .create("HDF5_version", datatype::create<std::string>(),
                dataspace::Scalar())
        .write("1.0.0");
  }

  GIVEN("a file in read-only mode") {
    auto f1 = file::open("testclose.h5", hdf5::file::AccessFlags::ReadOnly);
    auto r1 = f1.root();
    // without this line works

    THEN("we can open a second file in read-only mode") {
      REQUIRE_NOTHROW(
          hdf5::file::open("testclose.h5", hdf5::file::AccessFlags::ReadOnly));
    }

    THEN("we cannot open a file in read write mode") {
      REQUIRE_THROWS_AS(
          hdf5::file::open("testclose.h5", hdf5::file::AccessFlags::ReadWrite),
          std::runtime_error);
    }

    // this behavior actually makes sense: we cannot alter a file while it
    // is open by someone else.

    WHEN("we close the file but keep the root group") {
      f1.close();
      THEN("creating a new read/write file will fail") {
        REQUIRE_THROWS_AS(hdf5::file::open("testclose.h5",
                                           hdf5::file::AccessFlags::ReadWrite),
                          std::runtime_error);
      }
    }

    WHEN("we also close the root group") {
      r1.close();
      f1.close();
      THEN("we are create create a new read/write file") {
        REQUIRE_NOTHROW(hdf5::file::open("testclose.h5",
                                         hdf5::file::AccessFlags::ReadWrite));
      }
    }
  }

  GIVEN("a file in read only mode with attributes") {
    auto f1 = file::open("testclose.h5", hdf5::file::AccessFlags::ReadOnly);
    auto r1 = f1.root();

    WHEN("opening the same file in a different block") {
      auto f2 =
          hdf5::file::open("testclose.h5", hdf5::file::AccessFlags::ReadOnly);
      auto r2 = f2.root();
      auto attr = r2.attributes[0];
    }

    r1.close();
    f1.close();

    REQUIRE_NOTHROW(
        hdf5::file::open("testclose.h5", hdf5::file::AccessFlags::ReadWrite));
  }
}
