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
#include <fstream>

#include <catch2/catch.hpp>
#include <h5cpp/core/filesystem.hpp>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/node/group.hpp>
#include <h5cpp/contrib/stl/string.hpp>
#include <h5cpp/core/utilities.hpp>

using namespace hdf5;

using Bytes = std::vector<unsigned char>;

/**
 * @brief read the content of a file to a byte buffer
 * 
 * This utility function reads the contents of a file, determined by filename, 
 * as raw uninterpreted bytes to a buffer.
 * 
 * @param filename path to the file to read
 * @return Bytes buffer with uninterpreted bytes
 */
static Bytes file_to_bytes(const std::string &filename)
{
  std::ifstream fin(filename, std::ios::binary);
  return Bytes(std::istreambuf_iterator<char>(fin), {});
}

/**
 * @brief write uninterpreted bytes to a file
 * 
 * This function 
 * 
 * @param filename path to the file to write
 * @param bytes the payload which should be written to a file
 */
static void bytes_to_file(const std::string &filename, const Bytes &bytes)
{
  std::ofstream fout(filename, std::ios::out | std::ios::binary);
  fout.write(reinterpret_cast<const char *>(bytes.data()), unsigned2signed<ssize_t>(bytes.size()));
  fout.close();
}

SCENARIO("reading a file from a memory buffer")
{
  std::string hdf5_version = "1.0.0";
  std::string filename{"test_image_from.h5"};

  //create the file which we would like to read from a memory buffer
  {
    auto f = file::create(filename, file::AccessFlags::Truncate);
    f.root()
        .attributes
        .create("HDF5_version", datatype::create<std::string>(),
                dataspace::Scalar{})
        .write(hdf5_version);
  }

  GIVEN("an existing open HDF5 file")
  {
    auto f = file::open(filename);
    THEN("we can store this to buffer")
    {
      Bytes buffer(signed2unsigned<size_t>(f.buffer_size()));
      REQUIRE(f.to_buffer(buffer) == static_cast<size_t>(f.buffer_size()));
      AND_THEN("write this to a file")
      {
        bytes_to_file("test.h5", buffer);
        AND_THEN("we can read this file back with the standard HDF5 library")
        {
          auto f2 = file::open("test.h5");
          auto a = f2.root().attributes["HDF5_version"];
          std::string attr;
          a.read(attr);
          REQUIRE(attr == hdf5_version);
        }
        fs::remove("test.h5");
      }
    }
  } // close all nexus_file objects

  GIVEN("a memory buffer with the content of the file")
  {
    auto ibuffer = file_to_bytes(filename);
    THEN("we can create a file instance from this bytes")
    {
      auto f = file::from_buffer(ibuffer);
      auto root = f.root();
      AND_THEN("we can read the attribute back")
      {
        REQUIRE(root.attributes.exists("HDF5_version"));
        auto a = root.attributes["HDF5_version"];
        std::string st;
        a.read(st);
        REQUIRE(st == hdf5_version);
      }
    }
  }

  GIVEN("an open file hander to an HDF5 file")
  {
    auto f = file::open(filename);
    THEN("we can write this file to a buffer")
    {
      Bytes buffer(signed2unsigned<size_t>(f.buffer_size()));
      f.to_buffer(buffer);
      AND_THEN("open it again with from_buffer")
      {
        auto f2 = file::from_buffer(buffer);
        std::string value;
        f2.root().attributes["HDF5_version"].read(value);
        REQUIRE(value == hdf5_version);
      }
      AND_THEN("we cannot create a new instance without copying")
      {
        REQUIRE_THROWS_AS(file::from_buffer(buffer, file::ImageFlags::DontCopy), std::runtime_error);
      }
      WHEN("copy construct a const buffer from the original")
      {
        const Bytes cbuffer = buffer;
        THEN("we cannot create a read write file from this")
        {
          REQUIRE_THROWS_AS(file::from_buffer(cbuffer,
                                              file::ImageFlags::DontCopy |
                                                  file::ImageFlags::DontRelease |
                                                  file::ImageFlags::ReadWrite),
                            std::runtime_error);
        }
        THEN("we can create a read only file")
        {
          auto file2 = file::from_buffer(cbuffer,
                                         file::ImageFlags::DontCopy |
                                             file::ImageFlags::DontRelease);
          AND_THEN("we can read back the HDF5 version")
          {
            auto r2 = file2.root();

            auto a = r2.attributes["HDF5_version"];
            std::string st;
            a.read(st);
            REQUIRE(st == hdf5_version);
          }
        }
      }
    }
  }

  fs::remove(filename);
}
