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
template <typename T> ds::Datatype get() {
  return ds::TypeTrait<T>::create();
}
}  // namespace

SCENARIO("tesing standard type straits", "[datatype][numeric]") {
  using ptype = std::tuple<ds::Datatype, ds::Class, hid_t>;
  auto param = GENERATE(table<ds::Datatype, ds::Class, hid_t>(
      {ptype{create<char>(), ds::Class::Integer, H5T_NATIVE_CHAR},
       ptype{create<unsigned char>(), ds::Class::Integer, H5T_NATIVE_UCHAR},
       ptype{create<signed char>(), ds::Class::Integer, H5T_NATIVE_SCHAR},
       ptype{create<short>(), ds::Class::Integer, H5T_NATIVE_SHORT},
       ptype{create<unsigned short>(), ds::Class::Integer, H5T_NATIVE_USHORT},
       ptype{create<int>(), ds::Class::Integer, H5T_NATIVE_INT},
       ptype{create<unsigned int>(), ds::Class::Integer, H5T_NATIVE_UINT},
       ptype{create<long>(), ds::Class::Integer, H5T_NATIVE_LONG},
       ptype{create<unsigned long>(), ds::Class::Integer, H5T_NATIVE_ULONG},
       ptype{create<long long>(), ds::Class::Integer, H5T_NATIVE_LLONG},
       ptype{create<unsigned long long>(), ds::Class::Integer, H5T_NATIVE_ULLONG},
       ptype{create<float>(), ds::Class::Float, H5T_NATIVE_FLOAT},
       ptype{create<double>(), ds::Class::Float, H5T_NATIVE_DOUBLE},
       ptype{create<long double>(), ds::Class::Float, H5T_NATIVE_LDOUBLE},
       ptype{create<bool>(), ds::Class::Integer, H5T_NATIVE_HBOOL}
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
      {ptype{get<char>(), ds::Class::Integer, H5T_NATIVE_CHAR},
       ptype{get<unsigned char>(), ds::Class::Integer, H5T_NATIVE_UCHAR},
       ptype{get<signed char>(), ds::Class::Integer, H5T_NATIVE_SCHAR},
       ptype{get<short>(), ds::Class::Integer, H5T_NATIVE_SHORT},
       ptype{get<unsigned short>(), ds::Class::Integer, H5T_NATIVE_USHORT},
       ptype{get<int>(), ds::Class::Integer, H5T_NATIVE_INT},
       ptype{get<unsigned int>(), ds::Class::Integer, H5T_NATIVE_UINT},
       ptype{get<long>(), ds::Class::Integer, H5T_NATIVE_LONG},
       ptype{get<unsigned long>(), ds::Class::Integer, H5T_NATIVE_ULONG},
       ptype{get<long long>(), ds::Class::Integer, H5T_NATIVE_LLONG},
       ptype{get<unsigned long long>(), ds::Class::Integer, H5T_NATIVE_ULLONG},
       ptype{get<float>(), ds::Class::Float, H5T_NATIVE_FLOAT},
       ptype{get<double>(), ds::Class::Float, H5T_NATIVE_DOUBLE},
       ptype{get<long double>(), ds::Class::Float, H5T_NATIVE_LDOUBLE},
       ptype{get<bool>(), ds::Class::Integer, H5T_NATIVE_HBOOL}
       }));

  GIVEN("an HDF5 datat type") {
    THEN("the type class is") { REQUIRE(dt(param).get_class() == cl(param)); }
    THEN("the types are equivalent") {
      REQUIRE(H5Tequal(static_cast<hid_t>(dt(param)), hid(param)));
    }
  }
}
