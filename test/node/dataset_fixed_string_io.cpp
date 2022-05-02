//
// (c) Copyright 2017 DESY,ESS
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
// Created on: Oct 24, 2017
//
#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

using strings = std::vector<std::string>;

SCENARIO("testing fixed string IO") {
  auto f = hdf5::file::create("DatasetFixedStringIO.h5",
                              file::AccessFlags::Truncate);
  auto string_type = datatype::String::fixed(5);
  dataspace::Scalar scalar_space;
  dataspace::Simple simple_space{{2, 3}};
  property::DatasetTransferList dtpl;

  string_type.encoding(hdf5::datatype::CharacterEncoding::UTF8);
  string_type.padding(hdf5::datatype::StringPad::NullTerm);

  GIVEN("a scalar dataset of a fixed string type") {
    node::Dataset dataset(f.root(), "data", string_type, scalar_space);
    AND_GIVEN("a string value") {
      std::string value = "hello";
      THEN("we can write the value to the dataset with explicit DTPL") {
        dataset.write(value, string_type, scalar_space, scalar_space, dtpl);
        AND_THEN("read the value back") {
          std::string buffer;
          dataset.read(buffer, string_type, scalar_space, scalar_space, dtpl);
          REQUIRE(value == buffer);
        }
      }
      THEN("we can write the value with implicit DTPL") {
        dataset.write(value, string_type, scalar_space);
        AND_THEN("read the value back") {
          std::string buffer;
          dataset.read(buffer, string_type, scalar_space);
          REQUIRE(value == buffer);
        }
      }
    }
  }

  GIVEN("an array dataset") {
    node::Dataset dataset(f.root(), "data", string_type, simple_space);
    AND_GIVEN("a vector fo strings") {
      strings write{"AAAAA", "BBBBB", "CCCCC", "DDDDD", "EEEEE", "FFFFF"};
      THEN("we can write this vector with explicit DTPL") {
        dataset.write(write, string_type, simple_space, simple_space, dtpl);
        AND_THEN("we can read this vector back") {
          strings buffer;
          dataset.read(buffer, string_type, simple_space, simple_space, dtpl);
          REQUIRE(buffer.size() == write.size());
          REQUIRE_THAT(write, Catch::Matchers::Equals(buffer));
        }
        GIVEN("a 10 characters fixed length string type") {
          auto read_type = datatype::String::fixed(10);
          read_type.padding(datatype::StringPad::SpacePad);
          read_type.encoding(datatype::CharacterEncoding::UTF8);
          std::string buffer;
          THEN("we can read the first element with a hyperslab") {
            dataset.read(buffer, read_type, scalar_space,
                         dataspace::Hyperslab{{0, 0}, {1, 1}});
            REQUIRE(buffer == "AAAAA     ");
          }
          THEN("we can read the last element with a hyperslab") {
            dataset.read(buffer, read_type, scalar_space,
                         dataspace::Hyperslab{{1, 2}, {1, 1}});
            REQUIRE(buffer == "FFFFF     ");
          }
        }
        GIVEN("a 6 character fixed length string type") {
          auto read_type = datatype::String::fixed(6);
          read_type.padding(datatype::StringPad::SpacePad);
          read_type.encoding(datatype::CharacterEncoding::UTF8);
          strings buffer(4);
          AND_GIVEN("a 4 element hyperslab selection") {
            dataspace::Hyperslab selection{{0, 0}, {2, 1}, {1, 2}, {1, 2}};
            THEN("we can read those 4 elements") {
              dataset.read(buffer, read_type, dataspace::Simple{{4}}, selection);
              strings expected{"AAAAA ", "CCCCC ", "DDDDD ", "FFFFF "};
              REQUIRE_THAT(buffer, Catch::Matchers::Equals(expected));
            }
          }
        }
      }
    }
  }
}
