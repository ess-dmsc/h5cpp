//
// (c) Copyright 2017 DESY,ESS
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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 23, 2017
//

#include <catch2/catch.hpp>
#include <h5cpp/datatype/factory.hpp>
#include <h5cpp/datatype/float.hpp>

using namespace hdf5;


/*
TYPED_TEST(Float, Exceptions) {
  datatype::Datatype dtype;
  EXPECT_THROW((datatype::Float(dtype)), std::runtime_error);

  auto ft = datatype::create<int>();
  EXPECT_THROW((datatype::Float(ft)), std::runtime_error);
}*/


TEMPLATE_TEST_CASE("testing","[datatype][numeric][lfoat]", float, double, long double) {
  GIVEN("a datatype instance") { 
    auto t = datatype::create<TestType>();
    THEN("the factory function should return a Float instance") { 
      REQUIRE((std::is_same<decltype(t), datatype::Float>::value));
    }
    THEN("the type class should be FLOAT") { 
      REQUIRE(t.get_class() == datatype::Class::FLOAT);
    }
    THEN("the size should be") { 
      REQUIRE(t.size() == sizeof(TestType));
    }

    AND_GIVEN("a reference to the generic Datatype") { 
      datatype::Datatype &generic_type = t;
      THEN("we can create a new instance") { 
        datatype::Float new_type(generic_type);
        AND_THEN("we this should be a FLOAT type as well") { 
          REQUIRE(new_type.get_class() == datatype::Class::FLOAT);
        }
      }
    }
  }
}

