//
// (c) Copyright 2017 DESY,ESS
//               2020 Eugen Wintersberger <eugen.wintersberger@gmail.com>
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
// Author: Martin Shetty <martin.shetty@esss.se>
//         Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Oct 11, 2017
//

#include <catch2/catch.hpp>
#include <h5cpp/datatype/string.hpp>

using namespace hdf5;

SCENARIO("testing variable length strings") {
  GIVEN("an instance of a variable length string type") {
    auto t = datatype::String::variable();
    THEN("the instance if of type STRING") {
      REQUIRE(t.get_class() == datatype::Class::String);
    }
    THEN("the size of the type is H5T_VARIABLE") {
      REQUIRE(t.size() == size_t(H5T_VARIABLE));
    }
    THEN("the variable length flag is set") { REQUIRE(t.is_variable_length()); }

    THEN("we cannot set the size on a variable length type") {
      REQUIRE_THROWS_AS(t.size(5ul), std::runtime_error);
    }

    AND_GIVEN("that the type is closed") {
      ObjectHandle(static_cast<hid_t>(t)).close();
      THEN("we get an exception") {
        REQUIRE_THROWS_AS(t.is_variable_length(), std::runtime_error);
      }
    }
  }
}

SCENARIO("constructing a fixed length string") {
  GIVEN("a string type of size 3") {
    auto t = datatype::String::fixed(3);

    THEN("the type class will be STRING") {
      REQUIRE(t.get_class() == datatype::Class::String);
    }
    THEN("the variable length flag will be false") {
      REQUIRE_FALSE(t.is_variable_length());
    }
    THEN("the size size is 3") { REQUIRE(t.size() == 3ul); }

    AND_WHEN("we set the size to a new value") {
      t.size(5ul);
      THEN("the size is 5") { REQUIRE(t.size() == 5ul); }
    }

    AND_THEN("we cannot set the size to 0") {
      REQUIRE_THROWS_AS((t.size(0ul)), std::runtime_error);
    }
  }

  GIVEN("a string size of 0") {
    THEN("the string construction fails") {
      REQUIRE_THROWS_AS((datatype::String::fixed(0ul)), std::runtime_error);
    }
  }
}

SCENARIO("setting the encoding on a fixed length string") {
  auto encoding = GENERATE(datatype::CharacterEncoding::ASCII,
                           datatype::CharacterEncoding::UTF8);
  GIVEN("a fixed length string") {
    auto t = datatype::String::fixed(3);
    THEN("we can set the encoding") {
      t.encoding(encoding);
      AND_THEN("we get") { REQUIRE(t.encoding() == encoding); }
    }
  }
  GIVEN("a default constructed string type") {
    datatype::String t;
    THEN("accessing the encoding will fail") {
      REQUIRE_THROWS_AS(t.encoding(), std::runtime_error);
    }
    THEN("setting the encoding will fail") {
      REQUIRE_THROWS_AS(t.encoding(encoding), std::runtime_error);
    }
  }
}

SCENARIO("setting the string padding") {
  auto pad =
      GENERATE(datatype::StringPad::SpacePad, datatype::StringPad::NullTerm,
               datatype::StringPad::NullPad);
  GIVEN("a fixed string type ") {
    auto t = datatype::String::fixed(3);
    WHEN("we set the padding") {
      t.padding(pad);
      THEN("we get for the padding") { REQUIRE(t.padding() == pad); }
    }
  }
  GIVEN("a default constructed type") {
    datatype::String t;
    THEN("accessing the padding fails") { 
      REQUIRE_THROWS_AS(t.padding(), std::runtime_error);
    }
    THEN("setting the padding fails") { 
      REQUIRE_THROWS_AS(t.padding(pad), std::runtime_error);
    }
  } 
}
