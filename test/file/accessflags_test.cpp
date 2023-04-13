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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Sep 8, 2017
//
#include <h5cpp/file/types.hpp>
#ifdef H5CPP_CATCH2_V2
#include <catch2/catch.hpp>
#else
#include <catch2/catch_all.hpp>
#endif
#include <sstream>

using namespace hdf5;

static file::AccessFlagsBase to_int(file::AccessFlags flag)
{
  return static_cast<file::AccessFlagsBase>(flag);
}

SCENARIO("test file access or operator")
{
  using file::AccessFlags;
  using file::AccessFlagsBase;
  GIVEN("READWRITE")
  {
    AND_GIVEN("TRUNCATE")
    {
      THEN("we get H5F_ACC_RDWR | H5F_ACC_TRUNC")
      {
        REQUIRE(static_cast<AccessFlagsBase>(file::AccessFlags::ReadWrite | file::AccessFlags::Truncate) == (H5F_ACC_RDWR | H5F_ACC_TRUNC));
      }

      AND_GIVEN("EXCLUSIVE")
      {
        THEN("we get ")
        {
          REQUIRE(static_cast<AccessFlagsBase>(file::AccessFlags::ReadWrite | file::AccessFlags::Truncate |
                  file::AccessFlags::Exclusive) ==
                      (H5F_ACC_RDWR |
                  H5F_ACC_TRUNC | H5F_ACC_EXCL));
        }
      }
    }
  }
  GIVEN("EXCLUSIVE")
  {
    AND_GIVEN("READONLY")
    {
      THEN("we get H5F_ACC_EXCL | H5F_ACC_RDONLY")
      {
        REQUIRE(static_cast<AccessFlagsBase>(file::AccessFlags::Exclusive | file::AccessFlags::ReadOnly) == (H5F_ACC_EXCL | H5F_ACC_RDONLY));
      }
    }
  }
}

SCENARIO("Testing OR and AND operator combinations")
{
  using file::AccessFlagsBase;
  REQUIRE(static_cast<AccessFlagsBase>((file::AccessFlags::ReadWrite | file::AccessFlags::Truncate) &
                file::AccessFlags::ReadWrite) ==
            H5F_ACC_RDWR);
  REQUIRE(static_cast<AccessFlagsBase>(file::AccessFlags::Truncate &
                (file::AccessFlags::ReadWrite | file::AccessFlags::Truncate)) ==
            H5F_ACC_TRUNC);
  REQUIRE(static_cast<AccessFlagsBase>((file::AccessFlags::ReadWrite | file::AccessFlags::Truncate) &
                (file::AccessFlags::ReadWrite | file::AccessFlags::Exclusive)) ==
            H5F_ACC_RDWR);
}

SCENARIO("Test access flags values")
{
  REQUIRE(static_cast<file::AccessFlagsBase>(file::AccessFlags::Exclusive) ==
          H5F_ACC_EXCL);
  REQUIRE(static_cast<file::AccessFlagsBase>(file::AccessFlags::ReadOnly) ==
          H5F_ACC_RDONLY);
  REQUIRE(static_cast<file::AccessFlagsBase>(file::AccessFlags::ReadWrite) ==
          H5F_ACC_RDWR);
  REQUIRE(static_cast<file::AccessFlagsBase>(file::AccessFlags::Truncate) ==
          H5F_ACC_TRUNC);
#if H5_VERSION_GE(1, 10, 0)
  REQUIRE(static_cast<file::AccessFlagsBase>(file::AccessFlags::SWMRWrite) ==
          H5F_ACC_SWMR_WRITE);
  REQUIRE(static_cast<file::AccessFlagsBase>(file::AccessFlags::SWMRRead) ==
          H5F_ACC_SWMR_READ);
#endif
}

SCENARIO("file access flags output", "[h5cpp,file]")
{
  std::stringstream stream;

  GIVEN("AccessFlags::Exclusive")
  {
    WHEN("written to output stream")
    {
      stream << file::AccessFlags::Exclusive;
      REQUIRE(stream.str() == "EXCLUSIVE");
    }

    WHEN("converted to integer")
    {
      REQUIRE(to_int(file::AccessFlags::Exclusive) == H5F_ACC_EXCL);
    }
  }

  GIVEN("AccessFalgs::ReadOnly")
  {
    WHEN("written to output stream")
    {
      stream << file::AccessFlags::ReadOnly;
      REQUIRE(stream.str() == "READONLY");
    }

    WHEN("converted to integer")
    {
      REQUIRE(to_int(file::AccessFlags::ReadOnly) == H5F_ACC_RDONLY);
    }
  }

  GIVEN("AccessFlags::ReadWrite")
  {
    WHEN("output")
    {
      stream << file::AccessFlags::ReadWrite;
      REQUIRE(stream.str() == "READWRITE");
    }

    WHEN("converted to integer")
    {
      REQUIRE(to_int(file::AccessFlags::ReadWrite) == H5F_ACC_RDWR);
    }
  }

  GIVEN("AccessFlags::Truncate")
  {
    WHEN("output")
    {
      stream << file::AccessFlags::Truncate;
      REQUIRE(stream.str() == "TRUNCATE");
    }

    WHEN("converted to integer")
    {
      REQUIRE(to_int(file::AccessFlags::Truncate) == H5F_ACC_TRUNC);
    }
  }
#if H5_VERSION_GE(1, 10, 0)
  GIVEN("AccessFlags::SWMRWrite")
  {
    WHEN("written to stream")
    {
      stream << file::AccessFlags::SWMRWrite;
      REQUIRE(stream.str() == "SWMR WRITE");
    }

    WHEN("converted to integer")
    {
      REQUIRE(to_int(file::AccessFlags::SWMRWrite) == H5F_ACC_SWMR_WRITE);
    }
  }

  GIVEN("AccessFlags::SWMRRead")
  {
    WHEN("written to output stream")
    {
      stream << file::AccessFlags::SWMRRead;
      REQUIRE(stream.str() == "SWMR READ");
    }

    WHEN("converted to integer")
    {
      REQUIRE(to_int(file::AccessFlags::SWMRRead) == H5F_ACC_SWMR_READ);
    }
  }
#endif
}
