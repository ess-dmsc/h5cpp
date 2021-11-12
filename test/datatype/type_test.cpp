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
// Author:
//   Martin Shetty <martin.shetty@esss.se>
//   Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Feb 03, 2018
//

#include <catch2/catch.hpp>
#include <h5cpp/datatype/types.hpp>
#include <sstream>
#include <tuple>

using namespace hdf5;
using namespace hdf5::datatype;

namespace {
template <typename T>
auto value(T&& e) -> decltype(std::get<0>(e)) {
  return std::get<0>(e);
}

template <typename T>
auto str(T&& e) -> decltype(std::get<1>(e)) {
  return std::get<1>(e);
}
}  // namespace

SCENARIO("Enumeration stream IO") {
  std::stringstream stream;
  GIVEN("type class enumerations") {
    using ptype = std::tuple<Class, std::string>;
    auto param = GENERATE(table<Class, std::string>(
        {ptype{Class::None, "NONE"}, ptype{Class::Integer, "INTEGER"},
         ptype{Class::Float, "FLOAT"}, ptype{Class::Time, "TIME"},
         ptype{Class::String, "STRING"}, ptype{Class::BitField, "BITFIELD"},
         ptype{Class::Opaque, "OPAQUE"}, ptype{Class::Compound, "COMPOUND"},
         ptype{Class::Reference, "REFERENCE"}, ptype{Class::Enum, "ENUM"},
         ptype{Class::VarLength, "VARLENGTH"}, ptype{Class::Array, "ARRAY"}}));
    WHEN("writting the type class to the stream") {
      stream << value(param);
      THEN("result will be") { REQUIRE(stream.str() == str(param)); }
    }
  }

  GIVEN("write order enumeration") {
    using ptype = std::tuple<Order, std::string>;
    auto param = GENERATE(table<Order, std::string>(
        {ptype{Order::BE, "BE"}, ptype{Order::LE, "LE"}}));
    WHEN("writing the order enumeration to the stream") {
      stream << value(param);
      THEN("the output will be") { REQUIRE(stream.str() == str(param)); }
    }
  }

  GIVEN("write the sign enumeration") {
    using ptype = std::tuple<Sign, std::string>;
    auto param = GENERATE(table<Sign, std::string>(
        {ptype{Sign::Twos_Complement, "TWOS COMPLEMENT"},
         ptype{Sign::Unsigned, "UNSIGNED"}}));
    WHEN("writing the sign to the stream") {
      stream << value(param);
      THEN("the result will be") { REQUIRE(stream.str() == str(param)); }
    }
  }

  GIVEN("write the Norm enumeration") {
    using ptype = std::tuple<Norm, std::string>;
    auto param = GENERATE(table<Norm, std::string>(
        {ptype{Norm::Implied, "IMPLIED"}, ptype{Norm::MSBSet, "MSBSET"},
         ptype{Norm::None, "NONE"}}));
    WHEN("writing the norm to the stream") {
      stream << value(param);
      THEN("the restult will be") { REQUIRE(stream.str() == str(param)); }
    }
  }

  GIVEN("write Pad enumeration") {
    using ptype = std::tuple<Pad, std::string>;
    auto param = GENERATE(table<Pad, std::string>(
        {ptype{Pad::Background, "BACKGROUND"}, ptype{Pad::One, "ONE"},
         ptype{Pad::Zero, "ZERO"}}));
    WHEN("writing the pad to the stream") {
      stream << value(param);
      THEN("the restult will be") { REQUIRE(stream.str() == str(param)); }
    }
  }

  GIVEN("wirting the string padding to the stream") {
    using ptype = std::tuple<StringPad, std::string>;
    auto param = GENERATE(table<StringPad, std::string>(
        {ptype{StringPad::NullPad, "NULLPAD"},
         ptype{StringPad::NullTerm, "NULLTERM"},
         ptype{StringPad::SpacePad, "SPACEPAD"}}));
    WHEN("writing the string padding to the stream") {
      stream << value(param);
      THEN("the restult will be") { REQUIRE(stream.str() == str(param)); }
    }
  }

  GIVEN("writing the direction to the stream") {
    using ptype = std::tuple<Direction, std::string>;
    auto param = GENERATE(
        table<Direction, std::string>({ptype{Direction::Ascend, "ASCEND"},
                                       ptype{Direction::Descend, "DESCEND"}}));
    WHEN("writing the direction to the stream") {
      stream << value(param);
      THEN("the restult will be") { REQUIRE(stream.str() == str(param)); }
    }
  }

  GIVEN("writing the character encoding to the stream") {
    using ptype = std::tuple<CharacterEncoding, std::string>;
    auto param = GENERATE(table<CharacterEncoding, std::string>(
        {ptype{CharacterEncoding::ASCII, "ASCII"},
         ptype{CharacterEncoding::UTF8, "UTF8"}}));
    WHEN("writing the character encoding to the stream") {
      stream << value(param);
      THEN("the restult will be") { REQUIRE(stream.str() == str(param)); }
    }
  }
}
