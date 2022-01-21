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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@gmail.com>
//   Jan Kotanski <jan.kotanski@desy.de>
//
// Created on: Oct 11, 2017
//
#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>
#include <h5cpp/contrib/stl/string.hpp>

using namespace hdf5;

SCENARIO("writing and reading with selections") {
  const std::string filename = "writing_and_reading_with_selections.h5";
  auto f = file::create(filename, file::AccessFlags::Truncate);
  property::LinkCreationList lcpl;
  property::DatasetCreationList dcpl;
  dcpl.layout(property::DatasetLayout::Chunked);
  dcpl.chunk({1024});

  auto dataspace =
      [](size_t size) {
        return dataspace::Simple{{size}, {dataspace::Simple::unlimited}};
      };

  GIVEN("an empty dataset") {
    node::Dataset dset(f.root(), "data", datatype::create<int>(), dataspace(0),
                       lcpl, dcpl);
    AND_GIVEN("a hyperslab selection") {
      dataspace::Hyperslab slab{{0}, {1}, {1}, {1}};
      THEN("we cann append new values to the dataset") {
        int write=0, read=0;
        for (size_t index = 0; index < 100; ++index, write = static_cast<int>(index), read = 0) {
          node::resize_by(dset, 0, 1);
          slab.offset(0, index);
          dset.write(write, slab);
          dset.read(read, slab);
          REQUIRE(write == read);
        }
      }
    }
  }

  GIVEN("a dataset of size 10") {
    using Catch::Matchers::Equals;
    node::Dataset dset(f.root(), "data", datatype::create<int>(), dataspace(10),
                       lcpl, dcpl);
    AND_GIVEN("input data") {
      std::vector<int> write{6, 7, 8, 9, 10};
      AND_GIVEN("a point selection") {
        dataspace::Points points({{1}, {2}, {3}, {4}, {5}});
        THEN("we can write this data with the selection") {
          dset.write(write, points);
          AND_THEN("we can read the entire stuff back") {
            std::vector<int> read(10);
            std::vector<int> expected{0, 6, 7, 8, 9, 10, 0, 0, 0, 0};
            dset.read(read);
            REQUIRE_THAT(read, Equals(expected));
          }
          AND_THEN("we can read a few points back") { 
            std::vector<int> read(3);
            std::vector<int> expected{6,7,8};
            dataspace::Points read_points({{1},{2},{3}});
            dset.read(read, read_points);
            REQUIRE_THAT(read, Equals(expected));
          }
        }
      }
    }
  }
}


using int_vector = std::vector<int>;
using string_vector = std::vector<std::string>;
using double_vector = std::vector<double>;

SCENARIO("reading from empty datasets") {
  using Catch::Matchers::Equals;
  const std::string filename = "reading_from_empty_datasets.h5";
  auto f = file::create(filename, file::AccessFlags::Truncate);
  auto r = f.root();
  dataspace::Simple space{{0}, {dataspace::Simple::unlimited}};
  property::LinkCreationList lcpl;
  property::DatasetCreationList dcpl;
  dcpl.chunk({1});

  GIVEN("an empty integer dataset") {
    node::Dataset dset(r, "data", datatype::create<int>(), space, lcpl, dcpl);

    WHEN("reading from this dataset") {
      int_vector read;
      REQUIRE_NOTHROW(dset.read(read));
      THEN("it must be equal to an empty vector") {
        int_vector expected;
        REQUIRE_THAT(read, Equals(expected));
      }
    }
  }

  GIVEN("an empty variable length string dataset") {
    node::Dataset dset(r, "data", datatype::create<std::string>(), space, lcpl,
                       dcpl);
    WHEN("reading  from this dataset") {
      string_vector read;
      REQUIRE_NOTHROW(dset.read(read));
      THEN("it must be equal to an empty string vector") {
        string_vector expected;
        REQUIRE_THAT(read, Equals(expected));
      }
    }
  }

  GIVEN("an empty fixed length string dataset") {
    node::Dataset dset(r, "data", datatype::String::fixed(5), space, lcpl,
                       dcpl);
    WHEN("reading from this dataset") {
      string_vector read;
      REQUIRE_NOTHROW(dset.read(read));
      THEN("it must be equal to an empty value") {
        string_vector expected;
        REQUIRE_THAT(read, Equals(expected));
      }
    }
  }

  GIVEN("an empty double dataset") {
    node::Dataset dset(r, "data", datatype::create<double>(), space, lcpl,
                       dcpl);
    WHEN("reading from this dataset") {
      double_vector read;
      REQUIRE_NOTHROW(dset.read(read));
      THEN("it must be equal to an empty value") {
        double_vector expected;
        REQUIRE_THAT(read, Equals(expected));
      }
    }
  }
}
