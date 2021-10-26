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
//   Eugen Wintersberger <eugen.wintersberger@gmail.com>
//   Martin Shetty <martin.shetty@esss.se>
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Aug 28, 2017
//

#include <catch2/catch.hpp>
#include <h5cpp/datatype/datatype.hpp>
#include <h5cpp/datatype/type_trait.hpp>
#include <tuple>

namespace ds = hdf5::datatype;

namespace {
template <typename T>
auto dt(T&& t) -> decltype(std::get<0>(t)) {
  return std::get<0>(t);
}

template <typename T>
auto cl(T&& t) -> decltype(std::get<1>(t)) {
  return std::get<1>(t);
}

template <typename T>
hid_t hid(T&& t) {
  return std::get<2>(t);
}

template <typename T> ds::Datatype create() {
  return ds::TypeTrait<T>::create();
}
template <typename T> ds::Datatype cref() {
  return ds::TypeTrait<T>::create();
}
}  // namespace

SCENARIO("tesing standard type straits", "[datatype][numeric]") {
  using ptype = std::tuple<ds::Datatype, ds::Class, hid_t>;
  auto param = GENERATE(table<ds::Datatype, ds::Class, hid_t>(
      {ptype{create<char>(), ds::Class::INTEGER, H5T_NATIVE_CHAR},
       ptype{create<unsigned char>(), ds::Class::INTEGER, H5T_NATIVE_UCHAR},
       ptype{create<signed char>(), ds::Class::INTEGER, H5T_NATIVE_SCHAR},
       ptype{create<short>(), ds::Class::INTEGER, H5T_NATIVE_SHORT},
       ptype{create<unsigned short>(), ds::Class::INTEGER, H5T_NATIVE_USHORT},
       ptype{create<int>(), ds::Class::INTEGER, H5T_NATIVE_INT},
       ptype{create<unsigned int>(), ds::Class::INTEGER, H5T_NATIVE_UINT},
       ptype{create<long>(), ds::Class::INTEGER, H5T_NATIVE_LONG},
       ptype{create<unsigned long>(), ds::Class::INTEGER, H5T_NATIVE_ULONG},
       ptype{create<long long>(), ds::Class::INTEGER, H5T_NATIVE_LLONG},
       ptype{create<unsigned long long>(), ds::Class::INTEGER, H5T_NATIVE_ULLONG},
       ptype{create<float>(), ds::Class::FLOAT, H5T_NATIVE_FLOAT},
       ptype{create<double>(), ds::Class::FLOAT, H5T_NATIVE_DOUBLE},
       ptype{create<long double>(), ds::Class::FLOAT, H5T_NATIVE_LDOUBLE},
       ptype{create<bool>(), ds::Class::INTEGER, H5T_NATIVE_HBOOL}
       }));

  GIVEN("an HDF5 datat type") {
    THEN("the type class is") { REQUIRE(dt(param).get_class() == cl(param)); }
    THEN("the types are equivalent") {
      REQUIRE(H5Tequal(static_cast<hid_t>(dt(param)), hid(param)));
    }
  }
}

SCENARIO("tesing standard type straits with cref", "[datatype][numeric]") {
  using ptype = std::tuple<ds::Datatype, ds::Class, hid_t>;
  auto param = GENERATE(table<ds::Datatype, ds::Class, hid_t>(
      {ptype{cref<char>(), ds::Class::INTEGER, H5T_NATIVE_CHAR},
       ptype{cref<unsigned char>(), ds::Class::INTEGER, H5T_NATIVE_UCHAR},
       ptype{cref<signed char>(), ds::Class::INTEGER, H5T_NATIVE_SCHAR},
       ptype{cref<short>(), ds::Class::INTEGER, H5T_NATIVE_SHORT},
       ptype{cref<unsigned short>(), ds::Class::INTEGER, H5T_NATIVE_USHORT},
       ptype{cref<int>(), ds::Class::INTEGER, H5T_NATIVE_INT},
       ptype{cref<unsigned int>(), ds::Class::INTEGER, H5T_NATIVE_UINT},
       ptype{cref<long>(), ds::Class::INTEGER, H5T_NATIVE_LONG},
       ptype{cref<unsigned long>(), ds::Class::INTEGER, H5T_NATIVE_ULONG},
       ptype{cref<long long>(), ds::Class::INTEGER, H5T_NATIVE_LLONG},
       ptype{cref<unsigned long long>(), ds::Class::INTEGER, H5T_NATIVE_ULLONG},
       ptype{cref<float>(), ds::Class::FLOAT, H5T_NATIVE_FLOAT},
       ptype{cref<double>(), ds::Class::FLOAT, H5T_NATIVE_DOUBLE},
       ptype{cref<long double>(), ds::Class::FLOAT, H5T_NATIVE_LDOUBLE},
       ptype{cref<bool>(), ds::Class::INTEGER, H5T_NATIVE_HBOOL}
       }));

  GIVEN("an HDF5 datat type") {
    THEN("the type class is") { REQUIRE(dt(param).get_class() == cl(param)); }
    THEN("the types are equivalent") {
      REQUIRE(H5Tequal(static_cast<hid_t>(dt(param)), hid(param)));
    }
  }
}
