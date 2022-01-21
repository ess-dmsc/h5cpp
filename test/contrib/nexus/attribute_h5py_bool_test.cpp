//
// (c) Copyright 2018 DESY,ESS
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
// Author: Jan Kotanski <jan,kotanski@desy.de>
// Created on: Jul 2, 2018
//
#include <catch2/catch.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

namespace { 
static datatype::EBool read_ebool(const attribute::Attribute& attr) {
  datatype::EBool buffer;
  attr.read(buffer);
  return buffer;
}
}


SCENARIO("Reading bool attributes written by h5py") {
  auto h5py_file =
      file::open("./../../h5py_test_boolattr.h5", file::AccessFlags::ReadOnly);
  auto root_group = h5py_file.root();

  // ==========================================================================
  // testing reading the bool data from an attribute with a scalar dataspace
  // ==========================================================================
  GIVEN("a boolean attribute with a scalar dataspace") {
    AND_GIVEN("it has the value true") {
      auto attr = root_group.attributes["bool_scalar_true"];
      THEN("read") {
        REQUIRE(static_cast<bool>(read_ebool(attr)) == true);
        REQUIRE(read_ebool(attr) == datatype::EBool::True);
        REQUIRE(read_ebool(attr) == 1);
      }

      AND_THEN("the data type should be an enumeration type") {
        REQUIRE(attr.datatype().get_class() == datatype::Class::Enum);
        REQUIRE(datatype::is_bool(datatype::Enum(attr.datatype())));
      }
    }

    AND_GIVEN("it hast the value false") {
      auto attr = root_group.attributes["bool_scalar_false"];
      THEN("read as bool") {
        REQUIRE(static_cast<bool>(read_ebool(attr)) == false);
        REQUIRE(read_ebool(attr) == datatype::EBool::False);
        REQUIRE(read_ebool(attr) == 0);
      }
    }
  }

  // ==========================================================================
  // test reading the bool data from an attribute with a simple dataspace
  // of size 1
  // ==========================================================================
  GIVEN("a boolean attribute with a simple dataspace") {
    AND_GIVEN("it has the value true") {
      auto attr = root_group.attributes["bool_simple_true"];
      THEN("read") {
        REQUIRE(static_cast<bool>(read_ebool(attr)) == true);
        REQUIRE(read_ebool(attr) == datatype::EBool::True);
        REQUIRE(read_ebool(attr) == 1);
      }

      AND_THEN("the data type should be an enumeration type") {
        REQUIRE(attr.datatype().get_class() == datatype::Class::Enum);
        REQUIRE(datatype::is_bool(datatype::Enum(attr.datatype())));
      }
    }

    AND_GIVEN("it has the value false") {
      auto attr = root_group.attributes["bool_simple_false"];
      THEN("read") { 
        REQUIRE(static_cast<bool>(read_ebool(attr)) == false);
        REQUIRE(read_ebool(attr) == datatype::EBool::False);
	REQUIRE(read_ebool(attr) == 0); }
    }
  }

  // ==========================================================================
  // test reading the bool data from an attribute with a simple dataspace
  // of size 4
  // ==========================================================================
  GIVEN("a boolean array attribute") {
    using uchars = std::vector<unsigned char>;
    using ebools = std::vector<datatype::EBool>; 
    auto ref_uchar = uchars{0, 1, 1, 0};


    auto attr = root_group.attributes["bool_array"];

    THEN("we get 0 1 1 0") {
      uchars buffer(4);
      attr.read(buffer);
      REQUIRE_THAT(buffer, Catch::Matchers::Equals(ref_uchar));
    }

    THEN("we can read as ebool") { 
      ebools buffer(4);
      attr.read(buffer);
    }

    AND_THEN("we get for the data type") {
      REQUIRE(attr.datatype().get_class() == datatype::Class::Enum);
      REQUIRE(attr.datatype().size() == 1);
    }
  }
}
