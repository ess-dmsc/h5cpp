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
// Author:
//   Martin Shetty <martin.shetty@esss.se>
//   Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Feb 03, 2018
//
#include <catch2/catch.hpp>
#include <h5cpp/dataspace/type.hpp>
#include <sstream>

using namespace hdf5;
using namespace hdf5::dataspace;

SCENARIO("Writing the dataspace type to a stream") {
  std::stringstream stream;

  WHEN("writing SCALAR to an output stream") {
    stream << Type::Scalar;
    THEN("the stream must contain") { REQUIRE(stream.str() == "SCALAR"); }
  }
  WHEN("writing SIMPLE to an output stream") {
    stream << Type::Simple;
    THEN("the stream must contain") { REQUIRE(stream.str() == "SIMPLE"); }
  }
  WHEN("writing NODATA to an output stream") {
    stream << Type::NoData;
    THEN("the stream must contain") { REQUIRE(stream.str() == "NODATA"); }
  }
}

SCENARIO("Writing the selection type to a stream") {
  std::stringstream stream;
  WHEN("writing NONE to the stream") {
    stream << SelectionType::None;
    THEN("the stream must contain") { REQUIRE(stream.str() == "NONE"); }
  }

  WHEN("writing POINTS to the stream") {
    stream << SelectionType::Points;
    THEN("the stream must contain") { REQUIRE(stream.str() == "POINTS"); }
  }

  WHEN("writing HYPERSLAB to the stream") {
    stream << SelectionType::Hyperslab;
    THEN("the stream must contain") { REQUIRE(stream.str() == "HYPERSLAB"); }
  }

  WHEN("writing ALL to the stream") {
    stream << SelectionType::All;
    THEN("the stream must contain") { REQUIRE(stream.str() == "ALL"); }
  }
}

SCENARIO("Writing the selection operation to a stream") {
  std::stringstream stream;

  WHEN("writing SET to the stream") {
    stream << SelectionOperation::Set;
    THEN("the stream must contain") { REQUIRE(stream.str() == "SET"); }
  }

  WHEN("writing OR to the stream") {
    stream << SelectionOperation::Or;
    THEN("the stream must contain") { REQUIRE(stream.str() == "OR"); }
  }

  WHEN("writing AND to the stream") {
    stream << SelectionOperation::And;
    THEN("the stream must contain") { REQUIRE(stream.str() == "AND"); }
  }

  WHEN("writing XOR to the stream") {
    stream << SelectionOperation::XOr;
    THEN("the stream must contain") { REQUIRE(stream.str() == "XOR"); }
  }

  WHEN("writing NOTB to the stream") {
    stream << SelectionOperation::NotB;
    THEN("the stream must contain") { REQUIRE(stream.str() == "NOTB"); }
  }

  WHEN("writing NOTA to the stream") {
    stream << SelectionOperation::NotA;
    THEN("the stream must contain") { REQUIRE(stream.str() == "NOTA"); }
  }

  WHEN("writing APPEND to the stream") {
    stream << SelectionOperation::Append;
    THEN("the stream must contain") { REQUIRE(stream.str() == "APPEND"); }
  }

  WHEN("writing PREPEND to the stream") {
    stream << SelectionOperation::Prepend;
    THEN("the stream mus contain") { REQUIRE(stream.str() == "PREPEND");}
  }
}
