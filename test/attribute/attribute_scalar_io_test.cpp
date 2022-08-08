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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Oct 5, 2017
//
#include <catch2/catch.hpp>
#include <cstdint>
#include <h5cpp/hdf5.hpp>
#include <h5cpp/contrib/stl/stl.hpp>
#include <vector>

using namespace hdf5;

SCENARIO("scalar attribute IO", "[hdf5],[attribute]") {
  auto h5file =
      file::create("attribute_scalar_io_test.h5", file::AccessFlags::Truncate);
  auto root = h5file.root();

  GIVEN("scalar unsigned int 8 IO") {
    auto a = root.attributes.create<std::uint8_t>("data");
    std::uint8_t write_value = 12;
    std::uint8_t read_value = 0;
    a.write(write_value);
    a.read(read_value);
    REQUIRE(write_value == read_value);
  }

  GIVEN("scalar float32 attribute io") {
    auto a = root.attributes.create<float>("data");
    float write_value = 3.213e-2f;
    float read_value = 0.0;
    a.write(write_value);
    a.read(read_value);
    REQUIRE(write_value == Approx(read_value));
  }

  GIVEN("scalar vector attribute IO") {
    // this should work as the size of the vector is one
    auto a = root.attributes.create<std::uint8_t>("data");
    std::vector<std::uint8_t> write_data{42};
    std::vector<std::uint8_t> read_data(1);
    REQUIRE_NOTHROW(a.write(write_data));
    REQUIRE_NOTHROW(a.read(read_data));
    REQUIRE(write_data[0] == read_data[0]);
  }

  GIVEN("a scalar float attribute") {
    // this should work too - however, only the first element of the vector
    // is written and read.
    auto a = root.attributes.create<float>("data");

    AND_GIVEN("a 3 element vectgor with data for writing") {
      std::vector<float> write_data{1.2f, 3.4f};
      THEN("trying to write the data will fail") {
        REQUIRE_THROWS_AS(a.write(write_data), std::runtime_error);
      }
    }

    AND_GIVEN("a 3 element vector for reading") {
      std::vector<float> read_data(3);
      THEN("trying to read will fail") {
        REQUIRE_THROWS_AS(a.read(read_data), std::runtime_error);
      }
    }
  }

  GIVEN("a scalar bool attribute") {
    attribute::Attribute a = root.attributes.create<bool>("flag");
    AND_GIVEN("a true value for writing") {
      bool value = true;
      REQUIRE_NOTHROW(a.write(value)); 
      THEN("reading back") { 
        bool read_back = false;
        a.read(read_back);
        REQUIRE(value == read_back);
      }
    }
  }
}
