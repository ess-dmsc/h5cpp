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
//   Jan Kotanski <jan.kotanski@desy.de>
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

TEMPLATE_TEST_CASE("testing",
                   "[datatype][numeric][lfoat]",
                   float,
                   double,
                   long double) {
  GIVEN("a datatype instance") {
    auto t = datatype::create<TestType>();
    THEN("the factory function should return a Float instance") {
      REQUIRE((std::is_same<decltype(t), datatype::Float>::value));
    }
    THEN("the type class should be FLOAT") {
      REQUIRE(t.get_class() == datatype::Class::FLOAT);
    }
    THEN("the size should be") { REQUIRE(t.size() == sizeof(TestType)); }

    AND_GIVEN("a reference to the generic Datatype") {
      datatype::Datatype& generic_type = t;
      THEN("we can create a new instance") {
        datatype::Float new_type(generic_type);
        AND_THEN("we this should be a FLOAT type as well") {
          REQUIRE(new_type.get_class() == datatype::Class::FLOAT);
        }
      }
    }
  }
}

TEMPLATE_TEST_CASE("testing with cref",
                   "[datatype][numeric][lfoat]",
                   float,
                   double,
                   long double) {
  GIVEN("a datatype instance") {
    auto & t = datatype::cref<TestType>();
    THEN("the factory function should return a const Float reference") {
      REQUIRE((std::is_same<decltype(t), const datatype::Float &>::value));
    }
    THEN("the type class should be FLOAT") {
      REQUIRE(t.get_class() == datatype::Class::FLOAT);
    }
    THEN("the size should be") { REQUIRE(t.size() == sizeof(TestType)); }

  }
}

TEMPLATE_TEST_CASE("testing byte order for floats",
                   "[datatype][numeric][float]",
                   datatype::float16_t,
                   float,
                   double,
                   long double) {
  GIVEN("an instance of the actual type") {
    auto t = datatype::create<TestType>();
    WHEN("we check the precision of the type") {
      REQUIRE((t.precision() == t.size() * 8lu || t.precision() == 80lu));
    }
    WHEN("checking the byte order it must be either") {
      REQUIRE((t.order() == datatype::Order::LE ||
               t.order() == datatype::Order::BE ||
               t.order() == datatype::Order::VAX));

      AND_THEN("we can set it to Big Endian") {
        t.order(datatype::Order::BE);
        REQUIRE(t.order() == datatype::Order::BE);
      }
      AND_THEN("we can set it to Little Endian") {
        t.order(datatype::Order::LE);
        REQUIRE(t.order() == datatype::Order::LE);
      }
    }
    WHEN("checking the offset of the type") {
      REQUIRE(t.offset() == 0lu);
      AND_THEN("we can set it to 1") {
        t.offset(1);
        REQUIRE(t.offset() == 1lu);
      }
      AND_THEN("we can set it to 2") {
        t.offset(2);
        REQUIRE(t.offset() == 2lu);
      }
    }

    WHEN("checking the padding we get") {
      using datatype::Pad;
      using r = std::vector<Pad>;
      REQUIRE_THAT(t.pad(), Catch::Matchers::Equals(r{Pad::ZERO, Pad::ZERO}));
      AND_THEN("we can set it to ZERO:ONE") {
        t.pad(Pad::ZERO, Pad::ONE);
        REQUIRE_THAT(t.pad(), Catch::Matchers::Equals(r{Pad::ZERO, Pad::ONE}));
      }
      AND_THEN("we can set it to ONE:BACKGROUND") {
        t.pad(Pad::ONE, Pad::BACKGROUND);
        REQUIRE_THAT(t.pad(),
                     Catch::Matchers::Equals(r{Pad::ONE, Pad::BACKGROUND}));
      }
    }

    WHEN("checking the inpad") {
      using datatype::Pad;
      REQUIRE(t.inpad() == Pad::ZERO);
      AND_THEN("set it to ONE") {
        t.inpad(Pad::ONE);
        REQUIRE(t.inpad() == Pad::ONE);
      }
      AND_THEN("set it to BACKGROUND") {
        t.inpad(Pad::BACKGROUND);
        REQUIRE(t.inpad() == Pad::BACKGROUND);
      }
    }

    WHEN("checking the norm") {
      using datatype::Norm;
      REQUIRE((t.norm() == Norm::IMPLIED || t.norm() == Norm::NONE));
      AND_THEN("set it to MSBSET") {
        t.norm(Norm::MSBSET);
        REQUIRE(t.norm() == Norm::MSBSET);
      }
      AND_THEN("set it to NONE") {
        t.norm(Norm::NONE);
        REQUIRE(t.norm() == Norm::NONE);
      }
    }

    WHEN("checking the EBIAS") {
      REQUIRE((t.ebias() == 2 * t.size() * t.size() * t.size() - 1 ||
               t.ebias() == 4 * t.size() * t.size() * t.size() - 1));
      AND_THEN("set it to 63") {
        t.ebias(63);
        REQUIRE(t.ebias() == 63lu);
      }
      AND_THEN("set it to 31") {
        t.ebias(31);
        REQUIRE(t.ebias() == 31lu);
      }
    }

    WHEN("checking fields") {
      using f = std::vector<size_t>;
      REQUIRE(t.fields().size() == 5lu);
      AND_THEN("set them to 15, 10,5, 0,10") {
        auto fields = f{15lu, 10lu, 5lu, 0lu, 10lu};
        t.fields(15lu, 10lu, 5lu, 0lu, 10lu);
        REQUIRE_THAT(t.fields(), Catch::Matchers::Equals(fields));
      }
      AND_THEN("set them to 14, 9, 5, 0, 9") {
        auto fields = f{15ul, 9ul, 5ul, 0ul, 9lu};
        t.fields(15lu, 9lu, 5lu, 0lu, 9lu);
        REQUIRE_THAT(t.fields(), Catch::Matchers::Equals(fields));
      }
    }
  }
}
TEMPLATE_TEST_CASE("testing byte order for floats with cref",
                   "[datatype][numeric][float]",
                   datatype::float16_t,
                   float,
                   double,
                   long double) {
  GIVEN("an instance of the actual type") {
    auto t = datatype::create<TestType>();
    WHEN("we check the precision of the type") {
      REQUIRE((t.precision() == t.size() * 8lu || t.precision() == 80lu));
    }
    WHEN("checking the byte order it must be either") {
      REQUIRE((t.order() == datatype::Order::LE ||
               t.order() == datatype::Order::BE ||
               t.order() == datatype::Order::VAX));

      AND_THEN("we can set it to Big Endian") {
        t.order(datatype::Order::BE);
        REQUIRE(t.order() == datatype::Order::BE);
      }
      AND_THEN("we can set it to Little Endian") {
        t.order(datatype::Order::LE);
        REQUIRE(t.order() == datatype::Order::LE);
      }
    }
    WHEN("checking the offset of the type") {
      REQUIRE(t.offset() == 0lu);
      AND_THEN("we can set it to 1") {
        t.offset(1);
        REQUIRE(t.offset() == 1lu);
      }
      AND_THEN("we can set it to 2") {
        t.offset(2);
        REQUIRE(t.offset() == 2lu);
      }
    }

    WHEN("checking the padding we get") {
      using datatype::Pad;
      using r = std::vector<Pad>;
      REQUIRE_THAT(t.pad(), Catch::Matchers::Equals(r{Pad::ZERO, Pad::ZERO}));
      AND_THEN("we can set it to ZERO:ONE") {
        t.pad(Pad::ZERO, Pad::ONE);
        REQUIRE_THAT(t.pad(), Catch::Matchers::Equals(r{Pad::ZERO, Pad::ONE}));
      }
      AND_THEN("we can set it to ONE:BACKGROUND") {
        t.pad(Pad::ONE, Pad::BACKGROUND);
        REQUIRE_THAT(t.pad(),
                     Catch::Matchers::Equals(r{Pad::ONE, Pad::BACKGROUND}));
      }
    }

    WHEN("checking the inpad") {
      using datatype::Pad;
      REQUIRE(t.inpad() == Pad::ZERO);
      AND_THEN("set it to ONE") {
        t.inpad(Pad::ONE);
        REQUIRE(t.inpad() == Pad::ONE);
      }
      AND_THEN("set it to BACKGROUND") {
        t.inpad(Pad::BACKGROUND);
        REQUIRE(t.inpad() == Pad::BACKGROUND);
      }
    }

    WHEN("checking the norm") {
      using datatype::Norm;
      REQUIRE((t.norm() == Norm::IMPLIED || t.norm() == Norm::NONE));
      AND_THEN("set it to MSBSET") {
        t.norm(Norm::MSBSET);
        REQUIRE(t.norm() == Norm::MSBSET);
      }
      AND_THEN("set it to NONE") {
        t.norm(Norm::NONE);
        REQUIRE(t.norm() == Norm::NONE);
      }
    }

    WHEN("checking the EBIAS") {
      REQUIRE((t.ebias() == 2 * t.size() * t.size() * t.size() - 1 ||
               t.ebias() == 4 * t.size() * t.size() * t.size() - 1));
      AND_THEN("set it to 63") {
        t.ebias(63);
        REQUIRE(t.ebias() == 63lu);
      }
      AND_THEN("set it to 31") {
        t.ebias(31);
        REQUIRE(t.ebias() == 31lu);
      }
    }

    WHEN("checking fields") {
      using f = std::vector<size_t>;
      REQUIRE(t.fields().size() == 5lu);
      AND_THEN("set them to 15, 10,5, 0,10") {
        auto fields = f{15lu, 10lu, 5lu, 0lu, 10lu};
        t.fields(15lu, 10lu, 5lu, 0lu, 10lu);
        REQUIRE_THAT(t.fields(), Catch::Matchers::Equals(fields));
      }
      AND_THEN("set them to 14, 9, 5, 0, 9") {
        auto fields = f{15ul, 9ul, 5ul, 0ul, 9lu};
        t.fields(15lu, 9lu, 5lu, 0lu, 9lu);
        REQUIRE_THAT(t.fields(), Catch::Matchers::Equals(fields));
      }
    }
  }
}
