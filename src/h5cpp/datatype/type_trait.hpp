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
// Authors: Eugen Wintersberger <eugen.wintersberger@desy.de>
//          Sebastian Koenig <skoenig@ncsu.edu>
//          Jan Kotanski <jan.kotanski@desy.de>
// Created on: Aug 28, 2017
//
#pragma once

#include <h5cpp/datatype/datatype.hpp>
#include <h5cpp/datatype/integer.hpp>
#include <h5cpp/datatype/float.hpp>
#include <h5cpp/datatype/string.hpp>
#include <h5cpp/datatype/compound.hpp>

#include <vector>
#include <array>
#include <string>
#include <complex>
#include <type_traits>

namespace hdf5 {
namespace datatype {

//!
//! \brief trait to create HDF5 datatypes
//!
//! This trait provides a static function which creates a new HDF5 data type
//! for a particular C++ type.
//!
//! Specializations for this template exist for the following native types
//!
//! \list \c char, \c unsigned char, \c singed char
//! \list \c double
//!
//! \tparam T type for which to create a new HDF5 data type
template<typename T>
class TypeTrait {
 public:
  //!
  //! \brief subtype of Datatype which will be used
  //!
  using TypeClass = Datatype;

  //!
  //! \brief create the new type instance
  //!
  static TypeClass create(const T & = T());
};

template<>
class TypeTrait<char> {
 public:
  using TypeClass = Integer;
  static TypeClass create(const char & = char()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_CHAR)));
  }
};

template<>
class TypeTrait<unsigned char> {
 public:
  using Type = unsigned char;
  using TypeClass = Integer;
  static TypeClass create(const Type & = Type()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_UCHAR)));
  }
};

template<>
class TypeTrait<signed char> {
 public:
  using Type = signed char;
  using TypeClass = Integer;
  static TypeClass create(const Type & = Type()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_SCHAR)));
  }
};

template<>
class TypeTrait<short> {
 public:
  using Type = short;
  using TypeClass = Integer;
  static TypeClass create(const Type & = Type()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_SHORT)));
  }
};

template<>
class TypeTrait<unsigned short> {
 public:
  using Type = unsigned short;
  using TypeClass = Integer;
  static TypeClass create(const Type & = Type()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_USHORT)));
  }
};

template<>
class TypeTrait<int> {
 public:
  using TypeClass = Integer;
  static TypeClass create(const int & = int()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_INT)));
  }
};

template<>
class TypeTrait<unsigned int> {
 public:
  using Type = unsigned int;
  using TypeClass = Integer;
  static TypeClass create(const Type & = Type()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_UINT)));
  }
};

template<>
class TypeTrait<long> {
 public:
  using Type = long;
  using TypeClass = Integer;
  static TypeClass create(const Type & = Type()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_LONG)));
  }
};

template<>
class TypeTrait<unsigned long> {
 public:
  using Type = unsigned long;
  using TypeClass = Integer;
  static TypeClass create(const Type & = Type()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_ULONG)));
  }
};

template<>
class TypeTrait<long long> {
 public:
  using Type = long long;
  using TypeClass = Integer;
  static TypeClass create(const Type & = Type()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_LLONG)));
  }
};

template<>
class TypeTrait<unsigned long long> {
 public:
  using Type = unsigned long long;
  using TypeClass = Integer;
  static TypeClass create(const Type & = Type()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_ULLONG)));
  }
};

template<>
class TypeTrait<datatype::float16_t> {
 public:
  using Type = datatype::float16_t;
  using TypeClass = Float;
  static TypeClass create(const Type & = Type()) {
    auto type = TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_FLOAT)));
    type.fields(15, 10, 5, 0, 10);
    type.size(2);
    type.ebias(15);
    return type;
  }
};

template<>
class TypeTrait<float> {
 public:
  using TypeClass = Float;
  static TypeClass create(const float & = float()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_FLOAT)));
  }
};

template<>
class TypeTrait<double> {
 public:
  using TypeClass = Float;
  static TypeClass create(const double & = double()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_DOUBLE)));
  }
};

template<>
class TypeTrait<long double> {
 public:
  using Type = long double;
  using TypeClass = Float;
  static TypeClass create(const Type & = Type()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_LDOUBLE)));
  }
};

template<>
class TypeTrait<std::string> {
 public:
  using TypeClass = String;
  static TypeClass create(const std::string & = std::string()) {
    return datatype::String::variable();
  }
};

template<typename T>
class TypeTrait<std::vector<T>> {
 public:
  using Type = std::vector<T>;
  using TypeClass = typename TypeTrait<T>::TypeClass;
  static TypeClass create(const Type & = Type()) {
    return TypeTrait<typename std::remove_const<T>::type>::create();
  }
};

template<typename T, size_t N>
class TypeTrait<std::array<T, N>> {
 public:
  using Type = std::array<T, N>;
  using TypeClass = typename TypeTrait<T>::TypeClass;
  static TypeClass create(const Type & = Type()) {
    return TypeTrait<typename std::remove_const<T>::type>::create();
  }
};

template<typename CharT>
class TypeTrait<std::basic_string<CharT>> {
 private:

 public:
  using Type = std::basic_string<CharT>;
  using TypeClass = String;

  static TypeClass create(const Type & = Type()) {
    static_assert(std::is_same<CharT, char>::value, "Only support 8Bit characters");

    String type = String::variable();
    type.encoding(CharacterEncoding::UTF8);
    return type;

  }

};

template<>
class TypeTrait<bool> {
 public:
  using Type = bool;
  using TypeClass = Integer;

  static TypeClass create(const Type & = Type()) {
    return Integer(ObjectHandle(H5Tcopy(H5T_NATIVE_HBOOL)));
  }
};

template<typename T>
class TypeTrait<std::complex<T>>
{
  private:
    using element_type = TypeTrait<T>;

  public:
    using Type = std::complex<T>;
    using TypeClass = Compound;

    static TypeClass create(const Type & = Type())
    {
      datatype::Compound type = datatype::Compound::create(
        sizeof(std::complex<T>));

      type.insert("real", 0, element_type::create(T()));
      type.insert("imag", alignof(T), element_type::create(T()));

      return type;
    }
};

} // namespace datatype
} // namespace hdf5
