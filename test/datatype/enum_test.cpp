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
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: May 14, 2018
//
#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>

enum WeakFruit : uint16_t { Apple = 0, Pear = 1, Orange = 2 };
enum class StrongFruit : uint16_t { Pineapple = 0, Jackfruit = 1, Durian = 2 };
enum FakeBool : int8_t { True = 0, False = 1 };

namespace hdf5 {
namespace datatype {

template <>
class TypeTrait<WeakFruit> {
 public:
  using TypeClass = Enum;

  static TypeClass create(const WeakFruit& = WeakFruit()) {
    auto type = datatype::Enum::create(WeakFruit());
    type.insert("Apple", WeakFruit::Apple);
    type.insert("Pear", WeakFruit::Pear);
    type.insert("Orange", WeakFruit::Orange);
    return type;
  }
  const static TypeClass & get(const WeakFruit& = WeakFruit())
  {
    const static TypeClass & cref_ = create();
    return cref_;
  }
};

template <>
class TypeTrait<StrongFruit> {
 public:
  using TypeClass = Enum;

  static TypeClass create(const StrongFruit& = StrongFruit()) {
    auto type = datatype::Enum::create(StrongFruit());
    type.insert("Pineapple", StrongFruit::Pineapple);
    type.insert("Jackfruit", StrongFruit::Jackfruit);
    type.insert("Durian", StrongFruit::Durian);
    return type;
  }
  const static TypeClass & get(const StrongFruit& = StrongFruit())
  {
    const static TypeClass & cref_ = create();
    return cref_;
  }
};

template <>
class TypeTrait<FakeBool> {
 public:
  using TypeClass = Enum;

  static TypeClass create(const FakeBool& = FakeBool()) {
    auto type = datatype::Enum::create(FakeBool());
    type.insert("TRUE", FakeBool::True);
    type.insert("FALSE", FakeBool::False);
    return type;
  }
  const static TypeClass & get(const FakeBool& = FakeBool())
  {
    const static TypeClass & cref_ = create();
    return cref_;
  }
};

}  // namespace datatype
}  // namespace hdf5

using namespace hdf5;

SCENARIO("Construction of an enumeration type") {
  GIVEN("a default constructed enumeration type") {
    datatype::Enum type;
    THEN("the type is invalid") { REQUIRE_FALSE(type.is_valid()); }
    THEN("the class is NONE") {
      REQUIRE(type.get_class() == datatype::Class::None);
    }
    THEN("requesting number of values fails") {
      REQUIRE_THROWS_AS(type.number_of_values(), std::runtime_error);
    }
    THEN("cannot retrieve a name") {
      REQUIRE_THROWS_AS(type.name(0), std::runtime_error);
    }
  }

  GIVEN("a double base type") {
    auto ft = datatype::create<double>();
    THEN("the enumeration construction fails") {
      REQUIRE_THROWS_AS((datatype::Enum(ft)), std::runtime_error);
    }
  }

  GIVEN("a default generic type") {
    datatype::Datatype dt;
    THEN("enumeration construction must fail") {
      REQUIRE_THROWS_AS(datatype::Enum::create_underlying(dt),
                        std::runtime_error);
    }
  }

  GIVEN("an integer base type") {
    auto base_type = datatype::create<int>();
    THEN("an enumeration type can be constructed") {
      auto type = datatype::Enum::create_underlying(base_type);
      AND_THEN("the type is valid") { REQUIRE(type.is_valid()); }
      AND_THEN("the type is of class ENUM") {
        REQUIRE(type.get_class() == datatype::Class::Enum);
      }
      AND_THEN("the number of values is 0") {
        REQUIRE(type.number_of_values() == 0u);
      }
    }
  }
}

SCENARIO("inserting a value to an enumeration") {
  GIVEN("an integer based enumeration type") {
    auto type = datatype::Enum::create_underlying(datatype::create<int>());
    AND_GIVEN("a value 1") {
      int val = 1;
      THEN("we can insert this into the enumeration type") {
        type.insert_underlying("val1", val);
        AND_WHEN("we try to add the same value a second time, it fails") {
          REQUIRE_THROWS_AS(type.insert_underlying("val2", val),
                            std::runtime_error);
        }
        AND_THEN("the number of values would be 1") {
          REQUIRE(type.number_of_values() == 1u);
        }
        AND_THEN("we can get the name of the first element") {
          REQUIRE(type.name(0) == "val1");
        }
        AND_THEN("we fail to retrieve a name for a value not existing") {
          REQUIRE_THROWS_AS(type.name(1), std::runtime_error);
        }
        AND_THEN("the value can be retrieved") {
          int readback = 0;
          type.underlying_value(0, readback);
          REQUIRE(val == readback);
          AND_THEN("we fail to read for a non existing value") {
            REQUIRE_THROWS_AS(type.underlying_value(1, readback),
                              std::runtime_error);
          }
        }
        WHEN("we try to retrieve the value to the wrong type") {
          double readback = 0.0;
          THEN("we fail") {
            REQUIRE_THROWS_AS(type.underlying_value(0, readback),
                              std::runtime_error);
          }
        }
      }
    }
    AND_GIVEN("given a double value") {
      double val = 2.0;
      THEN("trying to insert this value fails") {
        REQUIRE_THROWS_AS(type.insert_underlying("val2", val),
                          std::runtime_error);
      }
    }
  }
}

/*
TEST_F(Enum, GetValueByName) {
  auto type = datatype::Enum::create_underlying(datatype::create<int>());
  type.insert_underlying("val1", (int)1);

  int val2;
  type.underlying_value("val1", val2);
  EXPECT_EQ(val2, 1);

  EXPECT_THROW(type.underlying_value("val2", val2), std::runtime_error);
  double val3;
  EXPECT_THROW(type.underlying_value("val1", val3), std::runtime_error);
}
*/

SCENARIO("Custom enumeration trait construction") {
  GIVEN("the weak enumeration type") {
    auto type = datatype::create<WeakFruit>();
    THEN("we can read the names by index") {
      REQUIRE(type.name(0) == "Apple");
      REQUIRE(type.name(1) == "Pear");
      REQUIRE(type.name(2) == "Orange");
    }
    THEN("we can read the values by index") {
      REQUIRE(type.value<WeakFruit>(0) == WeakFruit::Apple);
      REQUIRE(type.value<WeakFruit>(1) == WeakFruit::Pear);
      REQUIRE(type.value<WeakFruit>(2) == WeakFruit::Orange);
    }
  }

  GIVEN("the strong enumeration") {
    auto type = datatype::create<StrongFruit>();
    THEN("we can read the names by index") {
      REQUIRE(type.name(0) == "Pineapple");
      REQUIRE(type.name(1) == "Jackfruit");
      REQUIRE(type.name(2) == "Durian");
    }
    THEN("we can read the values by index") {
      REQUIRE(type.value<StrongFruit>(0) == StrongFruit::Pineapple);
      REQUIRE(type.value<StrongFruit>(1) == StrongFruit::Jackfruit);
      REQUIRE(type.value<StrongFruit>(2) == StrongFruit::Durian);
    }
  }

}

SCENARIO("Custom enumeration trait construction with cref") {
  GIVEN("the weak enumeration type") {
    auto type = datatype::Enum(datatype::get<WeakFruit>());
    THEN("we can read the names by index") {
      REQUIRE(type.name(0) == "Apple");
      REQUIRE(type.name(1) == "Pear");
      REQUIRE(type.name(2) == "Orange");
    }
    THEN("we can read the values by index") {
      REQUIRE(type.value<WeakFruit>(0) == WeakFruit::Apple);
      REQUIRE(type.value<WeakFruit>(1) == WeakFruit::Pear);
      REQUIRE(type.value<WeakFruit>(2) == WeakFruit::Orange);
    }
  }

  GIVEN("the strong enumeration") {
    auto type = datatype::Enum(datatype::get<StrongFruit>());
    THEN("we can read the names by index") {
      REQUIRE(type.name(0) == "Pineapple");
      REQUIRE(type.name(1) == "Jackfruit");
      REQUIRE(type.name(2) == "Durian");
    }
    THEN("we can read the values by index") {
      REQUIRE(type.value<StrongFruit>(0) == StrongFruit::Pineapple);
      REQUIRE(type.value<StrongFruit>(1) == StrongFruit::Jackfruit);
      REQUIRE(type.value<StrongFruit>(2) == StrongFruit::Durian);
    }
  }

}

SCENARIO("weak enumeration IO") {
  auto file = file::create("weak_enum_io.h5", file::AccessFlags::Truncate);
  auto root = file.root();
  GIVEN("create an enumeration attribute") {
    auto a = root.attributes.create<WeakFruit>("fruit");
    AND_GIVEN("an enumeration value") {
      WeakFruit write_fruit = WeakFruit::Apple;
      THEN("we can write this value") {
        a.write(write_fruit);
        AND_WHEN("we read the value back") {
          WeakFruit read_fruit = WeakFruit::Orange;
          a.read(read_fruit);
          THEN("the values must match") { REQUIRE(write_fruit == read_fruit); }
        }
      }
    }
  }
}

SCENARIO("strong enumeration IO") {
  auto file = file::create("string_enum_io.h5", file::AccessFlags::Truncate);
  auto root = file.root();
  GIVEN("create an enumeration attribute") {
    auto a = root.attributes.create<StrongFruit>("fruit");
    AND_GIVEN("an enumeration value") {
      auto write_fruit = StrongFruit::Pineapple;
      THEN("we can write this value to the attribute") {
        a.write(write_fruit);
        AND_WHEN("read the value back") {
          auto read_fruit = StrongFruit::Durian;
          a.read(read_fruit);
          THEN("the values should match") {
            REQUIRE(write_fruit == read_fruit);
          }
        }
      }
    }
  }
}


/*

TEST_F(Enum, test_fake_bool) {
  auto type = datatype::create<FakeBool>();
  EXPECT_EQ(type.name(1), "FALSE");
  EXPECT_EQ(type.value<FakeBool>(1), FakeBool::False);
  EXPECT_EQ(type.name(0), "TRUE");
  EXPECT_EQ(type.value<FakeBool>(0), FakeBool::True);
  EXPECT_EQ(datatype::is_bool(type), false);
}
*/
