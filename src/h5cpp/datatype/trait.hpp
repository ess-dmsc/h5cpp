//
// (c) Copyright 2019 Eugen Wintersberger <eugen.wintersberger@gmail.com>
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
// Author: Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Sep 01, 2019
//
#pragma once

#include <h5cpp/datatype/datatype.hpp>
#include <h5cpp/datatype/integer.hpp>
#include <h5cpp/datatype/float.hpp>
#include <h5cpp/datatype/string.hpp>

#include <vector>
#include <array>
#include <string>
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
  class Trait
  {
    public:
      //!
      //! \brief subtype of Datatype which will be used
      //!
      using TypeClass = Datatype;

      //!
      //! \brief create the new type instance
      //!
      static TypeClass create (const T& = T ());
  };

template<>
class Trait<char> {
 public:
  using TypeClass = Integer;
  static TypeClass create(const char & = char()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_CHAR)));
  }
};

template<>
class Trait<unsigned char> {
 public:
  using Type = unsigned char;
  using TypeClass = Integer;
  static TypeClass create(const Type & = Type()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_UCHAR)));
  }
};

template<>
class Trait<signed char> {
 public:
  using Type = signed char;
  using TypeClass = Integer;
  static TypeClass create(const Type & = Type()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_SCHAR)));
  }
};

template<>
class Trait<short> {
 public:
  using Type = short;
  using TypeClass = Integer;
  static TypeClass create(const Type & = Type()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_SHORT)));
  }
};

template<>
class Trait<unsigned short> {
 public:
  using Type = unsigned short;
  using TypeClass = Integer;
  static TypeClass create(const Type & = Type()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_USHORT)));
  }
};

template<>
class Trait<int> {
 public:
  using TypeClass = Integer;
  static TypeClass create(const int & = int()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_INT)));
  }
};

template<>
class Trait<unsigned int> {
 public:
  using Type = unsigned int;
  using TypeClass = Integer;
  static TypeClass create(const Type & = Type()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_UINT)));
  }
};

template<>
class Trait<long> {
 public:
  using Type = long;
  using TypeClass = Integer;
  static TypeClass create(const Type & = Type()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_LONG)));
  }
};

template<>
class Trait<unsigned long> {
 public:
  using Type = unsigned long;
  using TypeClass = Integer;
  static TypeClass create(const Type & = Type()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_ULONG)));
  }
};

template<>
class Trait<long long> {
 public:
  using Type = long long;
  using TypeClass = Integer;
  static TypeClass create(const Type & = Type()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_LLONG)));
  }
};

template<>
class Trait<unsigned long long> {
 public:
  using Type = unsigned long long;
  using TypeClass = Integer;
  static TypeClass create(const Type & = Type()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_ULLONG)));
  }
};

template<>
class Trait<float> {
 public:
  using TypeClass = Float;
  static TypeClass create(const float & = float()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_FLOAT)));
  }
};

template<>
class Trait<double> {
 public:
  using TypeClass = Float;
  static TypeClass create(const double & = double()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_DOUBLE)));
  }
};

template<>
class Trait<long double> {
 public:
  using Type = long double;
  using TypeClass = Float;
  static TypeClass create(const Type & = Type()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_LDOUBLE)));
  }
};

template<>
class Trait<std::string> {
 public:
  using TypeClass = String;
  static TypeClass create(const std::string & = std::string()) {
    return datatype::String::variable();
  }
};

template<typename T>
class Trait<std::vector<T>> {
 public:
  using Type = std::vector<T>;
  using TypeClass = typename Trait<T>::TypeClass;
  static TypeClass create(const Type & = Type()) {
    return Trait<typename std::remove_const<T>::type>::create();
  }
};

template<typename T, size_t N>
class Trait<std::array<T, N>> {
 public:
  using Type = std::array<T, N>;
  using TypeClass = typename Trait<T>::TypeClass;
  static TypeClass create(const Type & = Type()) {
    return Trait<typename std::remove_const<T>::type>::create();
  }
};

template<typename CharT>
class Trait<std::basic_string<CharT>>
{
  private:

  public:
    using Type = std::basic_string<CharT>;
    using TypeClass = String;

    static TypeClass create (const Type& = Type ())
    {
      static_assert(std::is_same<CharT, char>::value, "Only support 8Bit characters");

      String type = String::variable ();
      type.encoding (CharacterEncoding::UTF8);
      return type;

    }

};

template<>
  class Trait<bool>
  {
    public:
      using Type = bool;
      using TypeClass = Integer;

      static TypeClass create (const Type& = Type ())
      {
        return Integer (ObjectHandle (H5Tcopy (H5T_NATIVE_HBOOL)));
      }
  };

} // namespace datatype
} // namespace hdf5
