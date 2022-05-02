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
// Author: Eugen Wintersberger <eugen.wintersberger@gmail.com>
//
// Created on: Sep 11, 2017
//

#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

SCENARIO("testing node::Type stream output") {
  using node::Type;
  std::stringstream ss;
  using r = std::tuple<Type, std::string, H5O_type_t>;
  auto d = GENERATE(table<Type, std::string, H5O_type_t>(
      {r{Type::Dataset, "DATASET", H5O_TYPE_DATASET},
       r{Type::Datatype, "DATATYPE", H5O_TYPE_NAMED_DATATYPE},
       r{Type::Group, "GROUP", H5O_TYPE_GROUP},
       r{Type::Unknown, "UNKNOWN", H5O_TYPE_UNKNOWN}}));
  WHEN("writing the enumeration to the stream") {
    ss << std::get<0>(d);
    THEN("the output should be") { REQUIRE(ss.str() == std::get<1>(d)); }
  }
  WHEN("converting the value to an integer") {
    REQUIRE(static_cast<H5O_type_t>(std::get<0>(d)) == std::get<2>(d));
  }
}

SCENARIO("testing node::NodeType stream output") {
  using node::NodeType;
  using r = std::tuple<NodeType, std::string, H5O_type_t>;
  auto d = GENERATE(table<NodeType, std::string, H5O_type_t>(
      {r{NodeType::Dataset, "DATASET", H5O_TYPE_DATASET},
       r{NodeType::Datatype, "DATATYPE", H5O_TYPE_NAMED_DATATYPE},
       r{NodeType::Group, "GROUP", H5O_TYPE_GROUP},
       r{NodeType::Unknown, "UNKNOWN", H5O_TYPE_UNKNOWN}}));
  std::stringstream ss;
  WHEN("writing the enumeration to the stream") {
    ss << std::get<0>(d);
    THEN("the output should be") { REQUIRE(ss.str() == std::get<1>(d)); }
  }
  WHEN("converting the value to an integer") {
    REQUIRE(static_cast<H5O_type_t>(std::get<0>(d)) == std::get<2>(d));
  }
}
