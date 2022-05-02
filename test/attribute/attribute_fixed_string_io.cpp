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
//       Eugen Wintersberger <eugen.wintersberger@desy.de>
//       Jan Kotanski <jan.kotanski@desy.de>
// Created on: Oct 25, 2017
//
#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>
#include <h5cpp/contrib/stl/string.hpp>
#include <string>
#include <vector>

using namespace hdf5;

SCENARIO("Working with attributes and fixed UTF8 strings") {
  auto h5file =
      file::create("attribute_fixed_string_IO.h5", file::AccessFlags::Truncate);
  auto root_group = h5file.root();
  auto simple_space = dataspace::Simple{{2, 3}};
  auto scalar_space = dataspace::Scalar();
  auto string_type = datatype::String::fixed(5);
  string_type.encoding(datatype::CharacterEncoding::UTF8);
  string_type.padding(datatype::StringPad::NullTerm);

  GIVEN("an attribute with a scalar dataspace") {
    auto a = root_group.attributes.create("strattr", string_type, scalar_space);

    AND_GIVEN("an instance of a standard string of correct size") {
      std::string write = "hello";
      THEN("we can write a string to it") {
        REQUIRE_NOTHROW(a.write(write, string_type));
        AND_THEN("read it with the data type used to create the attribute") {
          std::string read;
          REQUIRE_NOTHROW(a.read(read, string_type));
          REQUIRE(write == read);
        }

        AND_GIVEN("a custom string type") {
          auto read_type = datatype::String::fixed(20);
          read_type.encoding(datatype::CharacterEncoding::UTF8);
          read_type.padding(datatype::StringPad::NullPad);
          THEN("we can read the data using this type") {
            std::string read;
            REQUIRE_NOTHROW(a.read(read, read_type));
            // need to remove trailing \0 from the string
            read.erase(std::remove(read.begin(), read.end(), '\0'), read.end());

            REQUIRE(write == read);
          }
        }
      }
    }

    AND_GIVEN("an instance of a smaller string") {
      std::string write = "hell";
      THEN("we have to resize the string to the appropriate size") {
        write.resize(5);
        AND_THEN("we can write it to the attribute") {
          REQUIRE_NOTHROW(a.write(write, string_type));
          AND_THEN("read it with the attribte datatype") {
            std::string read;
            REQUIRE_NOTHROW(a.read(read, a.datatype()));
            REQUIRE_THAT(write, Catch::Matchers::Equals(read));
          }
          AND_THEN("read it with the default datatype") {
            std::string read;
            REQUIRE_NOTHROW(a.read(read));
            REQUIRE_THAT(write, Catch::Matchers::Equals(read));
          }
        }
      }
    }
  }

  GIVEN("an attribute with a 2x3 simple dataspace") {
    auto a = root_group.attributes.create("strattr", string_type, simple_space);
    AND_GIVEN("a vector with 6 strings") {
      std::vector<std::string> write{"AAAAA", "BBBBB", "CCCCC",
                                     "DDDDD", "EEEEE", "FFFFF"};
      THEN("we can write this data to the attribute") {
        REQUIRE_NOTHROW(a.write(write, string_type));
        AND_THEN("read it to a vector of proper size") {
          std::vector<std::string> read(write.size());
          REQUIRE_NOTHROW(a.read(read, string_type));
          REQUIRE_THAT(write, Catch::Matchers::Equals(read));
        }
      }
    }
  }

  GIVEN("an attribute with a simple dataspace of size 1") {
    auto a = root_group.attributes.create("simple5", string_type,
                                          dataspace::Simple({1}));
    AND_GIVEN("a string of size 4") {
      std::string write = "hell";
      THEN("we have to resize the string") {
        write.resize(5);
        AND_THEN("write it to the attribute") {
          REQUIRE_NOTHROW(a.write(write, string_type));
          AND_THEN("we can read it back using the attribute datatype") {
            std::string read;
            REQUIRE_NOTHROW(a.read(read, a.datatype()));
            REQUIRE(write == read);
          }
          AND_THEN("read the data with the default datatype") {
            std::string read;
            REQUIRE_NOTHROW(a.read(read));
            REQUIRE(write == read);
          }
        }
      }
    }
  }

  GIVEN("an attribute with a simple dataspace of size 4") {
    using strings = std::vector<std::string>;
    auto a = root_group.attributes.create("simple20x", string_type,
                                          hdf5::dataspace::Simple({4}));
    AND_GIVEN("a vector of strings of wrong size") {
      auto orig = strings{"hllo", "ho1", "h", "ho33"};
      THEN("we have to fix the size of the strings") {
        strings write;
        std::transform(std::begin(orig), std::end(orig),
                       std::back_inserter(write), [](const std::string& s) {
                         std::string str(s);
                         str.resize(5);
                         return str;
                       });
        AND_THEN("we can write the data to the attribute") {
          REQUIRE_NOTHROW(a.write(write, string_type));
          AND_THEN("read it back using the attribute type") {
            strings read(4);
            REQUIRE_NOTHROW(a.read(read, a.datatype()));
            REQUIRE_THAT(write, Catch::Matchers::Equals(read));
          }
          AND_THEN("read it back using the default type") {
            strings read(4);
            REQUIRE_NOTHROW(a.read(read));
            REQUIRE_THAT(write, Catch::Matchers::Equals(read));
          }
        }
      }
    }
  }
}
