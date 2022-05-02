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
//       Eugen Wintersberger <eugen.wintersberger@desy.de>
//       Jan Kotanski <jan.kotanski@desy.de>
// Created on: Oct 5, 2017
//
#include <array>
#include <catch2/catch.hpp>
#include <cstdint>
#include <h5cpp/hdf5.hpp>
#include <vector>
#include <h5cpp/contrib/stl/vector.hpp>
#include <h5cpp/contrib/stl/array.hpp>

using namespace hdf5;

SCENARIO("multidimensional attribute IO") {
  auto h5file = file::create("attribute_test_multidim_io.h5",
                             file::AccessFlags::Truncate);
  auto root = h5file.root();

  GIVEN("a 3 dimensional attribute for unsigned int 8") {
    auto a = root.attributes.create<std::uint8_t>("data", {3});

    AND_GIVEN("a 3 element vector") {
      using uint8_vector = std::vector<uint8_t>;
      uint8_vector write_data{1, 2, 3};
      THEN("writing this data should work") {
        REQUIRE_NOTHROW(a.write(write_data));
        AND_THEN("reading the data back should reproduce the data") {
          auto read_data = uint8_vector(write_data.size());
          REQUIRE_NOTHROW(a.read(read_data));
          REQUIRE_THAT(write_data, Catch::Matchers::Equals(read_data));
        }
      }
    }

    AND_GIVEN("a 3 element array") { 
      using uint8_array = std::array<std::uint8_t, 3>;
      uint8_array write_data{3, 4, 5};
      THEN("writing this data should work") { 
        REQUIRE_NOTHROW(a.write(write_data));
        AND_THEN("reading the data back should yield {3,4,5}") { 
          uint8_array read_data;
          REQUIRE_NOTHROW(a.read(read_data));
          REQUIRE(write_data[0] == read_data[0]);
          REQUIRE(write_data[1] == read_data[1]);
          REQUIRE(write_data[2] == read_data[2]);
        }
      }
    }
  }

  GIVEN("an integer attribute with 4 elements") {
    auto a = root.attributes.create<int>("data", {4});
    AND_GIVEN("an initializer list with 4 elements") { 
      THEN("the write operation should work") {
        a.write({1, 2, 3, 4});
        AND_THEN("we can read the data to a vectror") { 
          std::vector<int> read(4);
          REQUIRE_NOTHROW(a.read(read));
          REQUIRE_THAT((std::vector<int>{1, 2, 3, 4}), Catch::Matchers::Equals(read));
        }
      }
    }
  }

  GIVEN("a float attribute for 4 elements") { 
    auto type = datatype::create<float>();
    auto space = dataspace::Simple({4});
    auto a = root.attributes.create("float",type,space);

    AND_GIVEN("a 4 element float vector") { 
      using float_vector = std::vector<float>;
      float_vector fvec_data = {1.2f, -0.23f, 34.4f, 5.5f};
      THEN("writing the data should work") { 
        REQUIRE_NOTHROW(a.write(fvec_data,  type));
        auto read = float_vector(4);
        AND_THEN("reading it with the custom data type") {
          a.read(read, type);
          REQUIRE_THAT(fvec_data, Catch::Matchers::Equals(read));
        }
        AND_THEN("reading with the native type") { 
          a.read(read, a.datatype());
          REQUIRE_THAT(fvec_data, Catch::Matchers::Equals(read));
        }
      }
    }
  }
}
