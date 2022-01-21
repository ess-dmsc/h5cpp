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
// Created on: Oct 25, 2017
//
#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>
#include <string>
#include <vector>
#include <h5cpp/contrib/stl/string.hpp>

using namespace hdf5;

using strings = std::vector<std::string>;

SCENARIO("variable string attribute IO") {
  auto file =
      file::create("AttributeFixedStringIO.h5", file::AccessFlags::Truncate);
  auto root_group = file.root();
  auto simple_space = dataspace::Simple{{6}};
  auto scalar_space = dataspace::Scalar();
  auto string_type = datatype::create<std::string>();

  GIVEN("a scalar attribute") {
    auto space = dataspace::Scalar();
    auto attr = root_group.attributes.create("scalar", string_type, space);
    AND_GIVEN("a string of arbitrary length") {
      std::string write = "hello";
      THEN("we can write the string to the attribute") {
        REQUIRE_NOTHROW(attr.write(write));
        std::string read;
        AND_THEN("read the attribute using the default datatype") {
          REQUIRE_NOTHROW(attr.read(read));
          REQUIRE(write == read);
        }
        AND_THEN("read the attribute using the attributes datatype") {
          REQUIRE_NOTHROW(attr.read(read, attr.datatype()));
          REQUIRE(write == read);
        }
      }
    }
    THEN("we can write a const char string to the attribute") {
      REQUIRE_NOTHROW(attr.write("A short notice"));
      AND_THEN("read it again") {
        std::string expect = "A short notice";
        std::string read;
        REQUIRE_NOTHROW(attr.read(read));
        REQUIRE_THAT(expect, Catch::Matchers::Equals(read));
      }
    }
  }

  GIVEN("an attribute for 6 elements") {
    auto space = dataspace::Simple({6});
    auto attr = root_group.attributes.create("vector", string_type, space);
    AND_GIVEN("a vector of strings of arbitrary but equal length") {
      strings write{"AAAA", "BBB", "CCCCCCCC", "DDDD", "EEEEE", "FFFFF"};
      THEN("write the vector to the attribute") {
        REQUIRE_NOTHROW(attr.write(write));
        strings read(write.size());
        AND_THEN("read a vector from the attribute") {
          REQUIRE_NOTHROW(attr.read(read));
          REQUIRE_THAT(write, Catch::Matchers::Equals(read));
        }
        AND_THEN("read the vector with the attributs datatype") { 
          REQUIRE_NOTHROW(attr.read(read,attr.datatype()));
          REQUIRE_THAT(write, Catch::Matchers::Equals(read));
        }
      }
    }
  }

  GIVEN("an attribute with a simple dataspace of size 1") {
    auto a = root_group.attributes.create("simple5", string_type,
                                          dataspace::Simple({1}));
    AND_GIVEN("a string of arbitrary length") {
      std::string write = "hell";
      THEN("we can write this string") {
        REQUIRE_NOTHROW(a.write(write, string_type));
        AND_GIVEN("an empty string buffer") {
          std::string read;
          AND_THEN("we can read the string using the attribute datatype") {
            REQUIRE_NOTHROW(a.read(read, a.datatype()));
            REQUIRE(write == read);
          }
          AND_THEN("read the attribute using the default datatype") {
            REQUIRE_NOTHROW(a.read(read));
            REQUIRE(write == read);
          }
        }
      }
    }
  }
}
