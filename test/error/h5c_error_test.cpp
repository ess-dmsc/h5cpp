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
// Created on: May 5, 2018
//

#include <catch2/catch.hpp>
#include "../h5cpp_test_helpers.hpp"

using namespace hdf5;

SCENARIO("testing h5cerror") {
  GIVEN("an empty stack") {
    auto stack = error::Singleton::instance().extract_stack();
    REQUIRE(stack.empty());
  }
  GIVEN("an error occuring") {
    provoke_h5_error();
    THEN("we can extract the error stack") {
      auto stack = error::Singleton::instance().extract_stack();
      AND_THEN("there should be some content in the stack") {
        REQUIRE(stack.contents().size() == 2u);
        AND_THEN("we can read this content") {
          for (auto d : stack.contents()) {
            REQUIRE(d.description.size() > 2u);
            REQUIRE(d.function.find("H5") != std::string::npos);
          }
        }
      }
      GIVEN("a stream string instance") {
        std::stringstream ss;
        AND_THEN("we can write this to the stream") {
          ss << stack.what();
          for (auto d : stack.contents()) {
            std::stringstream ss2;
            ss2 << d;
            REQUIRE(ss.str().find(ss2.str()) != std::string::npos);
          }
        }
      }
    }
  }
}
