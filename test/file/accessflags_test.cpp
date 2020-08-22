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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Sep 8, 2017
//
#include <h5cpp/file/types.hpp>
#include <catch2/catch.hpp>
#include <sstream>

using namespace hdf5;

file::AccessFlagsBase to_int(file::AccessFlags flag) {
  return static_cast<file::AccessFlagsBase>(flag);
}

SCENARIO("file access flags output", "[h5cpp,file]") {
  std::stringstream stream;

  GIVEN("AccessFlags::EXCLUSIVE") {
    WHEN("written to output stream") {
      stream << file::AccessFlags::EXCLUSIVE;
      REQUIRE(stream.str() == "EXCLUSIVE");
    }

    WHEN("converted to integer") {
      REQUIRE(to_int(file::AccessFlags::EXCLUSIVE) == H5F_ACC_EXCL);
    }
  }

  GIVEN("AccessFalgs::READONLY") {
    WHEN("written to output stream") {
      stream << file::AccessFlags::READONLY;
      REQUIRE(stream.str() == "READONLY");
    }

    WHEN("converted to integer") {
      REQUIRE(to_int(file::AccessFlags::READONLY) == H5F_ACC_RDONLY);
    }
  }

  GIVEN("AccessFlags::READWRITE") {
    WHEN("output") {
      stream << file::AccessFlags::READWRITE;
      REQUIRE(stream.str() == "READWRITE");
    }

    WHEN("converted to integer") {
      REQUIRE(to_int(file::AccessFlags::READWRITE) == H5F_ACC_RDWR);
    }
  }

  GIVEN("AccessFlags::TRUNCATE") {
    WHEN("output") {
      stream << file::AccessFlags::TRUNCATE;
      REQUIRE(stream.str() == "TRUNCATE");
    }

    WHEN("converted to integer") {
      REQUIRE(to_int(file::AccessFlags::TRUNCATE) == H5F_ACC_TRUNC);
    }
  }
#if H5_VERSION_GE(1, 10, 0)
  GIVEN("AccessFlags::SWMR_WRITE") {
    WHEN("written to stream") {
      stream << file::AccessFlags::SWMR_WRITE;
      REQUIRE(stream.str() == "SWMR WRITE");
    }

    WHEN("converted to integer") {
      REQUIRE(to_int(file::AccessFlags::SWMR_WRITE) == H5F_ACC_SWMR_WRITE);
    }
  }

  GIVEN("AccessFlags::SWMR_READ") {
    WHEN("written to output stream") {
      stream << file::AccessFlags::SWMR_READ;
      REQUIRE(stream.str() == "SWMR READ");
    }

    WHEN("converted to integer") {
      REQUIRE(to_int(file::AccessFlags::SWMR_READ) == H5F_ACC_SWMR_READ);
    }
  }
#endif
}
