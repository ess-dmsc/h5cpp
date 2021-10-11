//
// (c) Copyright 2017 DESY,ESS
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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Sep 8, 2017
//
#include <catch2/catch.hpp>
#include <h5cpp/file/types.hpp>
#include <sstream>

using namespace hdf5;

SCENARIO("testing the Scope enumeration", "[h5cpp, file]") {
  std::stringstream stream;

  GIVEN("Scope::GLOBAL") {
    WHEN("written to outpt stream") {
      stream << file::Scope::GLOBAL;
      REQUIRE(stream.str() == "GLOBAL");
    }

    WHEN("converted to integer") {
      REQUIRE(static_cast<file::ScopeBase>(file::Scope::LOCAL) ==
              H5F_SCOPE_LOCAL);
    }
  }

  GIVEN("Scope::LOCAL") {
    WHEN("written to output stream") {
      stream << file::Scope::LOCAL;
      REQUIRE(stream.str() == "LOCAL");
    }

    WHEN("converted to integer") {
      REQUIRE(static_cast<file::ScopeBase>(file::Scope::GLOBAL) ==
              H5F_SCOPE_GLOBAL);
    }
  }
}
