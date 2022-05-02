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
//! - \c char, \c unsigned char, \c singed char
//! - \c double
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

  //!
  //! \brief reference to const static type instance
  //!
  const static TypeClass & get(const T & = T());
};

template<>
class TypeTrait<char> {
 public:
  using Type = char;
  using TypeClass = Integer;
  static TypeClass create(const Type & = Type()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_CHAR)));
  }
  const static TypeClass & get(const Type & = Type()) {
    const static TypeClass & cref_ = create();
    return cref_;
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
  const static TypeClass & get(const Type & = Type()) {
    const static TypeClass & cref_ = create();
    return cref_;
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
  const static TypeClass & get(const Type & = Type()) {
    const static TypeClass & cref_ = create();
    return cref_;
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
  const static TypeClass & get(const Type & = Type()) {
    const static TypeClass & cref_ = create();
    return cref_;
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
  const static TypeClass & get(const Type & = Type()) {
    const static TypeClass & cref_ = create();
    return cref_;
  }
};

template<>
class TypeTrait<int> {
 public:
  using Type = int;
  using TypeClass = Integer;
  static TypeClass create(const Type & = Type()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_INT)));
  }
  const static TypeClass & get(const Type & = Type()) {
    const static TypeClass & cref_ = create();
    return cref_;
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
  const static TypeClass & get(const Type & = Type()) {
    const static TypeClass & cref_ = create();
    return cref_;
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
  const static TypeClass & get(const Type & = Type()) {
    const static TypeClass & cref_ = create();
    return cref_;
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
  const static TypeClass & get(const Type & = Type()) {
    const static TypeClass & cref_ = create();
    return cref_;
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
  const static TypeClass & get(const Type & = Type()) {
    const static TypeClass & cref_ = create();
    return cref_;
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
  const static TypeClass & get(const Type & = Type()) {
    const static TypeClass & cref_ = create();
    return cref_;
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
  const static TypeClass & get(const Type & = Type()) {
    const static TypeClass & cref_ = create();
    return cref_;
  }
};

template<>
class TypeTrait<float> {
 public:
  using Type = float;
  using TypeClass = Float;
  static TypeClass create(const Type & = Type()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_FLOAT)));
  }
  const static TypeClass & get(const Type & = Type()) {
    const static TypeClass & cref_ = create();
    return cref_;
  }
};

template<>
class TypeTrait<double> {
 public:
  using Type = double;
  using TypeClass = Float;
  static TypeClass create(const Type & = Type()) {
    return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_DOUBLE)));
  }
  const static TypeClass & get(const Type & = Type()) {
    const static TypeClass & cref_ = create();
    return cref_;
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
  const static TypeClass & get(const Type & = Type()) {
    const static TypeClass & cref_ = create();
    return cref_;
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
  const static TypeClass & get(const Type & = Type()) {
    const static TypeClass & cref_ = create();
    return cref_;
  }
};


} // namespace datatype
} // namespace hdf5
