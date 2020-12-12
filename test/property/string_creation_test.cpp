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
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 18, 2017
//

#include <catch2/catch.hpp>
#include <h5cpp/property/string_creation.hpp>
#include "../utilities.hpp"
#include "utilities.hpp"

namespace pl = hdf5::property;
namespace type = hdf5::datatype;

SCENARIO("constructing an instance of StringCreationList") {
  GIVEN("a default constructed instance") {
    pl::StringCreationList scl;
    THEN("this instance has the following configuration") {
      REQUIRE(scl.get_class() == pl::kStringCreate);
      REQUIRE(scl.character_encoding() == type::CharacterEncoding::ASCII);
    }
    WHEN("closing this instance") {
      close(scl);
      THEN("accesing all methods must fail") {
        REQUIRE_THROWS_AS(scl.character_encoding(), std::runtime_error);
        REQUIRE_THROWS_AS(
            scl.character_encoding(type::CharacterEncoding::ASCII),
            std::runtime_error);
      }
    }
  }
  GIVEN("a handle to a string creation property list") {
    auto handle = handle_from_class(pl::kStringCreate);
    THEN("we can construct an instance from this") {
      REQUIRE_NOTHROW(pl::StringCreationList{std::move(handle)});
    }
  }
  GIVEN("a handle to a group creation property list") {
    auto handle = handle_from_class(pl::kGroupCreate);
    THEN("then construction must fail") {
      REQUIRE_THROWS_AS(pl::StringCreationList{std::move(handle)},
                        std::runtime_error);
    }
  }
}
SCENARIO("setting the character encoding on a StringCreationList") { 
  pl::StringCreationList scl;
  GIVEN("all possible encodings") { 
    auto enc = GENERATE(type::CharacterEncoding::UTF8, type::CharacterEncoding::ASCII);
    WHEN("we set the encoding") { 
      scl.character_encoding(enc);
      AND_THEN("read it back")  {
        REQUIRE(scl.character_encoding() == enc);
      }
    }
  }
}