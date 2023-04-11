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
#define CATCH_CONFIG_MAIN
#include <sstream>
#include <catch2/catch.hpp>
#include "../h5cpp_test_helpers.hpp"
#include "../utilities.hpp"

using namespace hdf5;

SCENARIO("extracting error data") {
  provoke_h5_error();
  GIVEN("an error stack instance") {
    auto stack = error::Singleton::instance().extract_stack();
    THEN("there must be some content in the stack") {
      REQUIRE(stack.contents().size() > 0u);
      WHEN("we can extract this content") {
        auto d = stack.contents().front();
        THEN("we get") {
          REQUIRE(d.line > 10u);
          REQUIRE(d.function == "H5Iget_ref");
          REQUIRE(d.file.find("H5I.c") != std::string::npos);
          REQUIRE(d.description == "can't get ID ref count");
        }
        THEN("we can extract the error strings") {
          d.extract_strings();
#if H5_VERSION_GE(1,13,0)
          REQUIRE(d.major == "Object ID");
#else
          REQUIRE(d.major == "Object atom");
#endif
          REQUIRE(d.minor == "Can't get value");
        }
      }
    }
  }
}

SCENARIO("testing error stream output") {
  std::stringstream ss;
  GIVEN("an invalid object handle") {
    hdf5::ObjectHandle invalid_handle;
    WHEN("we try to get the reference from the handle") {
      H5Iget_ref(to_hid(invalid_handle));
      THEN("we provoke an error") {
        auto d =
            error::Singleton::instance().extract_stack().contents().front();
        AND_THEN("we can write this error stack to a stream") {
          ss << d;
          REQUIRE(ss.str().find(d.description) != std::string::npos);
        }
      }
    }
  }
}

// To ensure no-throw, C-string pointers must be null-initialized
// Talk to HDF5 group to see if they could make this happen
SCENARIO("testing illegal pointer initialization for error descriptors") { 
  H5E_error2_t descr;
  descr.file_name = nullptr;
  descr.func_name = nullptr;
  descr.desc = nullptr;
  REQUIRE_NOTHROW(error::Descriptor{descr});
  error::Descriptor f(descr);

  // This also generates errors on the error stack!!! Insane!
  REQUIRE_NOTHROW(f.extract_strings());

  error::Singleton::instance().clear_stack();
}
