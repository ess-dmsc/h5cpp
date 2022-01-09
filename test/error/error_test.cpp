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
// Created on: Oct 25, 2017
//

#include <catch2/catch.hpp>
#include <string>
#include "../h5cpp_test_helpers.hpp"

#include <cstring>

using namespace hdf5;
#define bufsize 7000

class ErrorTestCase {
 public:
  ErrorTestCase() {
    fflush(stderr);
    std::memset(buf, 0, bufsize);
    setvbuf(stderr, buf, _IOFBF, bufsize);
    error::Singleton::instance().auto_print(false);
  }

  ~ErrorTestCase() {
    // return stderr to normal function
    setvbuf(stderr, nullptr, _IONBF, bufsize);
  }

  std::string extract_string() {
    // extract redirected stderr text
    ss.str(std::string());
    ss << buf;
    return ss.str();
  }

 protected:
  std::stringstream ss;
  char buf[bufsize];
};

TEST_CASE_METHOD(ErrorTestCase,
                 "switching auto printing on",
                 "[h5cpp][error]") {
  error::Singleton::instance().auto_print(true);
  REQUIRE(error::Singleton::instance().auto_print());
  AND_THEN("provoke an error") {
    provoke_h5_error();
    REQUIRE_FALSE(extract_string().empty());
    REQUIRE_THROWS_AS(provoke_h5cpp_exception(), std::runtime_error);
  }
}

TEST_CASE_METHOD(ErrorTestCase,
                 "switching auto printing off",
                 "[h5cpp][error]") {
  REQUIRE_FALSE(error::Singleton::instance().auto_print());
  provoke_h5_error();
  REQUIRE(extract_string().empty());
  REQUIRE_THROWS_AS(provoke_h5cpp_exception(), std::runtime_error);
}

TEST_CASE_METHOD(ErrorTestCase, "testing stack extraction", "[h5cpp][error]") {
  provoke_h5_error();
  auto stack = error::Singleton::instance().extract_stack();
  REQUIRE(stack.contents().size() == 2u);
}

TEST_CASE_METHOD(ErrorTestCase,
                 "testing the clear stack method",
                 "[h5cpp][error]") {
  provoke_h5_error();
  error::Singleton::instance().clear_stack();
  auto stack = error::Singleton::instance().extract_stack();
  REQUIRE(stack.empty());

  error::Singleton::instance().clear_stack();
  error::Singleton::instance().clear_stack();
}

SCENARIO("testing error sequence behavior","[hdf5][error]") { 
  WHEN("an error occurs") { 
    provoke_h5_error();
    THEN("we can extract the error stack once") { 
      auto stack = error::Singleton::instance().extract_stack();
      AND_THEN("the size of the stack will be 2") { 
        REQUIRE(stack.contents().size() == 2ul);
      }
      AND_WHEN("we extrac the stack again") { 
        stack = error::Singleton::instance().extract_stack();
        THEN("the resulting stack wil be empty") { 
          REQUIRE(stack.empty());
        }
      }
    }
  }
}
TEST_CASE_METHOD(ErrorTestCase, "testing sequential", "[h5cpp][error]") {

  provoke_h5_error();
  REQUIRE(error::Singleton::instance().extract_stack().contents().size() ==
            2ul);
  REQUIRE(error::Singleton::instance().extract_stack().empty());

  provoke_h5_error();
  REQUIRE(error::Singleton::instance().extract_stack().contents().size() ==
            2ul);
  REQUIRE(error::Singleton::instance().extract_stack().empty());
}

TEST_CASE_METHOD(ErrorTestCase, "testing exception generation printing on", "[h5cpp][error]") { 
  error::Singleton::instance().auto_print(true);
  try {
    provoke_h5cpp_exception();
  } catch (std::exception& e) {
    auto message = error::print_nested(e);
    REQUIRE(message == "ObjectHandle: could not get reference counter\n");
  }
}

TEST_CASE_METHOD(ErrorTestCase, "testing exception generation printing off", "[h5cpp][error]") { 
  try {
    provoke_h5cpp_exception();
  } catch (std::exception& e) {
    auto message = error::print_nested(e);
    REQUIRE(message.size() > 20ul);
#ifdef _MSC_ER
    TEST_COUT << "\n" << message;
#endif
  }
}
