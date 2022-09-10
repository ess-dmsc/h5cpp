
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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Martin Shetty <martin.shetty@esss.se>
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Oct 6, 2017
//

#include <catch2/catch.hpp>
#include <complex>
#include <cstdint>
#include <h5cpp/hdf5.hpp>
#include <h5cpp/contrib/stl/complex.hpp>

using namespace hdf5;
using namespace hdf5::datatype;

struct complex_struct {
  double real;
  double imag;
};

class Pixel {
 public:
  Pixel() {}
  Pixel(std::uint8_t red, std::uint8_t green, std::uint8_t blue)
      : red_(red), green_(green), blue_(blue) {}

  std::uint8_t red_{0};
  std::uint8_t green_{0};
  std::uint8_t blue_{0};
};

namespace hdf5 {
namespace datatype {

template <typename BT>
struct complex_t {
  BT real;
  BT imag;
};

template <>
class TypeTrait<Pixel> {
 public:
  using TypeClass = Compound;

  static TypeClass create(const Pixel& = Pixel()) {
    auto type = datatype::Compound::create(sizeof(Pixel));
    type.insert("red", 0, datatype::create<std::uint8_t>());
    type.insert("green", 1, datatype::create<std::uint8_t>());
    type.insert("blue", 2, datatype::create<std::uint8_t>());
    return type;
  }
  const static TypeClass & get(const Pixel& = Pixel())
  {
    const static TypeClass & cref_ = create();
    return cref_;
  }
};

}  // namespace datatype
}  // namespace hdf5

SCENARIO("Compount type construction") {
  GIVEN("a default constructed compount type") {
    datatype::Compound type;
    THEN("the resulting type is invalid") { REQUIRE_FALSE(type.is_valid()); }
    THEN("it is of typeclass NONE") {
      REQUIRE(type.get_class() == datatype::Class::None);
    }
    THEN("cannot retrieve fields") {
      REQUIRE_THROWS_AS(type.number_of_fields(), std::runtime_error);
    }
    THEN("insertion of a new element fails") {
      REQUIRE_THROWS_AS(type.insert("x", HOFFSET(complex_struct, real),
                                    datatype::create<double>()),
                        std::runtime_error);
    }
    THEN("obtaining a field index fails") {
      REQUIRE_THROWS_AS(type.field_index("hello"), std::runtime_error);
    }
    THEN("obtaining the field name fails") {
      REQUIRE_THROWS_AS(type.field_name(0), std::runtime_error);
    }
    THEN("accessing a fields class fails") {
      REQUIRE_THROWS_AS(type.field_class(0), std::runtime_error);
    }
    THEN("accessing a field fails") {
      REQUIRE_THROWS_AS(type[0], std::runtime_error);
    }
    THEN("packing will fails") {
      REQUIRE_THROWS_AS(type.pack(), std::runtime_error);
    }
  }

  GIVEN("a double type") {
    auto ft = datatype::create<double>();
    THEN("we cannot construct a compount from this") {
      REQUIRE_THROWS_AS((datatype::Compound(ft)), std::runtime_error);
    }
  }
  WHEN("the size of the compount type is 0") {
    THEN("the construction fails") {
      REQUIRE_THROWS_AS((datatype::Compound::create(0)), std::runtime_error);
    }
  }
}

SCENARIO("Creating a pixel datatype using the trait") {
  GIVEN("a pixel type") {
    auto type = datatype::create<Pixel>();
    THEN("the compound type") { REQUIRE(type.size() == 3ul); }
    THEN("the type contains an INTEGER") {
      REQUIRE(type.has_class(datatype::Class::Integer));
    }
    THEN("the type does not contain a FLOAT") {
      REQUIRE_FALSE(type.has_class(datatype::Class::Float));
    }
  }
}

SCENARIO("Creating a pixel datatype using the trait with cref") {
  GIVEN("a pixel type") {
    auto & type = datatype::get<Pixel>();
    THEN("the compound type") { REQUIRE(type.size() == 3ul); }
    THEN("the type contains an INTEGER") {
      REQUIRE(type.has_class(datatype::Class::Integer));
    }
    THEN("the type does not contain a FLOAT") {
      REQUIRE_FALSE(type.has_class(datatype::Class::Float));
    }
  }
}

SCENARIO("creating compound data type for a complex number type") {
  GIVEN("a compount type of the size of the complex structure") {
    auto type = Compound::create(sizeof(complex_struct));
    THEN("the initial number of fields is 0") {
      REQUIRE(type.number_of_fields() == 0ul);
    }
    AND_WHEN("we add the first field") {
      REQUIRE_NOTHROW(type.insert("real", HOFFSET(complex_struct, real),
                                  datatype::create<double>()));
      AND_WHEN("we add the second field") {
        REQUIRE_NOTHROW(type.insert("imag", HOFFSET(complex_struct, imag),
                                    datatype::create<double>()));
        THEN("the number of fields is 2") {
          REQUIRE(type.number_of_fields() == 2ul);
        }
        THEN("the compound type will contain a field of float type") {
          REQUIRE(type.has_class(datatype::Class::Float));
        }
        THEN("the compound type will contain no interger field") {
          REQUIRE_FALSE(type.has_class(datatype::Class::Integer));
        }
        THEN("the real field has index 0") {
          REQUIRE(type.field_index("real") == 0ul);
        }
        THEN("the imag field has index 1") {
          REQUIRE(type.field_index("imag") == 1ul);
        }
        THEN("the name of field 0 is 'real'") {
          REQUIRE(type.field_name(0) == "real");
        }
        THEN("the name of field 1 is 'imag'") {
          REQUIRE(type.field_name(1) == "imag");
        }
        THEN("the type class of field 0 is FLOAT") {
          REQUIRE(type.field_class(0) == datatype::Class::Float);
        }
        THEN("the type class of field 'real' is FLOAT") {
          REQUIRE(type.field_class("real") == datatype::Class::Float);
        }
        THEN("the offset of the first field is 0") {
          REQUIRE(type.field_offset(0) == 0ul);
        }
        THEN("the offset of the field with name 'real' is 0") {
          REQUIRE(type.field_offset("real") == 0ul);
        }
        AND_GIVEN("a double datat type") {
          auto t = datatype::create<double>();
          THEN("the type of field 0 is the same") { REQUIRE(type[0] == t); }
          THEN("the type of name 'real' is the same") {
            REQUIRE(type["real"] == t);
          }
        }
        THEN("we can pack the type") { REQUIRE_NOTHROW(type.pack()); }
      }
    }
  }
}

SCENARIO("testing IO with complex value") {
  auto f = file::create("compound_test.h5", file::AccessFlags::Truncate);
  auto root = f.root();

  GIVEN("a complex attribute") {
    using complex_type = std::complex<double>;
    auto a = root.attributes.create<complex_type>("hello");
    AND_GIVEN("a complex number") {
      complex_type write_value{1., 3.};
      THEN("we can write a value") {
        a.write(write_value);
        AND_WHEN("we read the numbers back") {
          complex_type read_value{0., 0.};
          a.read(read_value);
          THEN("They must match the original values") {
            REQUIRE(write_value.real() == Approx(read_value.real()).epsilon(1e-12));
            REQUIRE(write_value.imag() == Approx(read_value.imag()).epsilon(1e-12));
          }
        }
      }
    }
  }

  GIVEN("pixel attribute") {
    auto a = root.attributes.create<Pixel>("pixel");
    AND_GIVEN("a pixel value") {
      Pixel write_pixel(1, 2, 3);
      THEN("we can write the pixel value to the attribute") {
        a.write(write_pixel);
        AND_WHEN("reading the number back") {
          Pixel read_pixel(0, 0, 0);
          a.read(read_pixel);
          THEN("the values should match") {
            REQUIRE(write_pixel.red_ == read_pixel.red_);
            REQUIRE(write_pixel.green_ == read_pixel.green_);
            REQUIRE(write_pixel.blue_ == read_pixel.blue_);
          }
        }
      }
    }
  }
}

