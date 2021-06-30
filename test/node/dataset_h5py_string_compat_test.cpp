//
// (c) Copyright 2018 DESY,ESS
//               2021 Eugen Wintersberger <eugen.wintersberger@gmail.com>
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
// Created on: Feb 5, 2018
//
#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

#ifndef _MSC_VER
SCENARIO("testing h5py compatible string IO") {
  auto f = file::open("../h5py_test_data.h5", file::AccessFlags::READONLY);
  auto r = f.root();

  GIVEN("a dataset with a fixed size string") {
    node::Dataset dataset = r.nodes["fix_string_scalar"];
    AND_GIVEN("a fixed size string memory data type") {
      dataspace::Scalar memory_space;
      auto memory_type = datatype::String::fixed(20);
      memory_type.padding(datatype::StringPad::SPACEPAD);
      THEN("we can read the content from the dataset to a buffer") {
        std::string buffer;
        dataset.read(buffer, memory_type, memory_space, dataset.dataspace());
        REQUIRE(buffer == "hello from h5py     ");
      }
    }
  }

  using strings = std::vector<std::string>;
  GIVEN("a UTF8 string dataset") {
    node::Dataset dataset = r.nodes["utf8_string"];
    const std::string expected =
        "Hello UTF8! Pr"
        "\xc3"
        "\xb3"
        "ba "
        "\xe6"
        "\xb5"
        "\x8b";
    AND_GIVEN("a vector buffer") {
      strings buffer(dataset.dataspace().size());
      THEN("we can read this data back using") {
        auto datatype = dataset.datatype();
        auto dataspace = dataset.dataspace();
        dataset.read(buffer, datatype, dataspace);
        REQUIRE(buffer.size() == 1lu);
        REQUIRE(buffer[0] == expected);
      }
      THEN("we can read the data back without a special data type") {
        dataset.read(buffer);
        REQUIRE(buffer.size() == 1lu);
        REQUIRE(buffer[0] == expected);
      }
    }
  }

  GIVEN("given a dataset with an array of") {
    node::Dataset dataset = r.nodes["fix_string_array"];
    const strings expected{"hello               ", "world               ",
                           "this                ", "is                  ",
                           "a                   ", "test                "};
    AND_GIVEN("a fixed size string type") {
      datatype::String memory_type = datatype::String::fixed(20);
      memory_type.padding(datatype::StringPad::SPACEPAD);
      AND_GIVEN("a 2x3 simple dataspace") {
        dataspace::Simple memory_space{{2, 3}};
        THEN("we can read the data back to a buffer") {
          strings buffer(6);
          dataset.read(buffer, memory_type, memory_space, dataset.dataspace());
          REQUIRE(buffer == expected);
        }
      }
    }
  }
}
#endif
