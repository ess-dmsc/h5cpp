//
// (c) Copyright 2017 DESY,ESS
//               2020 Eugen Wintersberger <eugen.wintersberger@gmail.com>
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
// Author: Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Oct 25, 2017
//
#include <catch2/catch.hpp>
#include <h5cpp/contrib/stl/string.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

SCENARIO("testing variable length string IO") {
  auto f = hdf5::file::create("DatasetVariableStringIO.h5",
                              hdf5::file::AccessFlags::Truncate);
  auto string_type = hdf5::datatype::create<std::string>();
  hdf5::dataspace::Scalar scalar_space;
  hdf5::dataspace::Simple simple_space({7});
  hdf5::property::DatasetTransferList dtpl;

  GIVEN("a scalar dataset") {
    node::Dataset dataset(f.root(), "scalar", string_type, scalar_space);
    THEN("we can write a single string value to it") {
      std::string value = "hello";
      dataset.write(value);
      AND_THEN("read it back") {
        std::string readback;
        dataset.read(readback);
        REQUIRE(readback == value);
      }
    }
    THEN("we can write a string from a char pointer") {
      dataset.write("this is a test");
      AND_THEN("read this back") {
        std::string readback;
        dataset.read(readback);
        REQUIRE(readback == "this is a test");
      }
    }
  }

  using strings = std::vector<std::string>;
  GIVEN("a vector dataset") {
    node::Dataset dataset(f.root(), "vector", string_type, simple_space);
    THEN("we can write a vector of strings") {
      strings write{"hello", "world", "this", "is", "an", "arbitrary", "text"};
      dataset.write(write);
      AND_THEN("read it back") {
        strings read(write.size());
        dataset.read(read);
        REQUIRE_THAT(write, Catch::Matchers::Equals(read));
      }
      AND_THEN("we can read single values back with hyperslabs") {
        std::string buffer;
        dataset.read(buffer, dataspace::Hyperslab{{0}, {1}});
        REQUIRE(buffer == "hello");
        dataset.read(buffer, dataspace::Hyperslab{{1}, {1}});
        REQUIRE(buffer == "world");
        dataset.read(buffer, dataspace::Hyperslab{{6}, {1}});
        REQUIRE(buffer == "text");
      }
      AND_THEN("we can read a multi-element selection back") {
        dataspace::Hyperslab selection{{0}, {3}, {2}};
        strings read(3);
        dataset.read(read, selection);
        REQUIRE_THAT(read,
                     Catch::Matchers::Equals(strings{"hello", "this", "an"}));
      }
    }
  }
}
