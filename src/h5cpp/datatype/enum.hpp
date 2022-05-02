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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Martin Shetty <martin.shetty@esss.se>
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: May 14, 2018
//
#pragma once

#include <h5cpp/datatype/datatype.hpp>
#include <h5cpp/datatype/factory.hpp>
#include <h5cpp/error/error.hpp>
#include <sstream>

namespace hdf5
{
namespace datatype
{

//!
//! \brief compound data type
//!
//! An enum data type which can be used to save enum values along
//! with metadata describing their meaning.
//!
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif
class DLL_EXPORT Enum : public Datatype
{
 public:
  //!
  //! \brief default constructor
  //!
  Enum() = default;

  //!
  //! \brief construct from handle
  //!
  explicit Enum(ObjectHandle&& handle);

  //!
  //! \brief construct from generic datatype
  //!
  explicit Enum(const Datatype& type);

  //!
  //! \brief named constructor (with underlying type deduction)
  //!
  template<typename T>
  static Enum create(const T&);

  //!
  //! \brief insert enum value definition (with underlying type deduction)
  //!
  template<typename T>
  void insert(const std::string& name, const T& data) const;

  //!
  //! \brief return the total number of enum values
  //!
  size_t number_of_values() const;

  //!
  //! \brief get value name
  //!
  std::string name(size_t index) const;

  //!
  //! \brief get value at index (with underlying type deduction)
  //!
  template<typename T>
  T value(size_t index) const;

  //!
  //! \brief get value by name (with underlying type deduction)
  //!
  template<typename T>
  T value(const std::string& name) const;

  // The following functions are low level

  //!
  //! \brief insert enum value definition
  //!
  template<typename T>
  void insert_underlying(const std::string& name, const T& data) const;

  //!
  //! \brief named constructor from underlying datatype
  //!
  static Enum create_underlying(const Datatype& base_type);

  //!
  //! \brief get value at index
  //!
  template<typename T>
  void underlying_value(size_t index, T& data) const;

  //!
  //! \brief get value by name
  //!
  template<typename T>
  void underlying_value(const std::string& name, T& data) const;

 private:
  template<typename T>
  void check_type(const T& data) const;

};
#ifdef __clang__
#pragma clang diagnostic pop
#endif

template<typename T>
void Enum::check_type(const T& data) const
{
  (void) data; //  < var unused, only for type inference
  hdf5::datatype::DatatypeHolder mem_type_holder;
  if (mem_type_holder.get<T>() != super())
  {
    std::stringstream ss;
    ss << "Attempt to insert enum value of mismatching type";
    throw (std::runtime_error(ss.str()));
  }
}

template<typename T>
Enum Enum::create(const T&)
{
  return create_underlying(datatype::create<typename std::underlying_type<T>::type>());
}


template<typename T>
void Enum::insert_underlying(const std::string& name, const T& data) const
{
  check_type(data);

  if (0 > H5Tenum_insert(static_cast<hid_t>(*this), name.c_str(), &data))
  {
    std::stringstream ss;
    ss << "Could not insert Enum value " << name << "=" << data;
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

template<typename T>
void Enum::insert(const std::string& name, const T& data) const
{
  auto data2 = static_cast<typename std::underlying_type<T>::type>(data);
  insert_underlying(name, data2);
}

template<typename T>
void Enum::underlying_value(size_t index, T& data) const
{
  check_type(data);

  if (0 > H5Tget_member_value(static_cast<hid_t>(*this), static_cast<uint32_t>(index), &data))
  {
    std::stringstream ss;
    ss << "Could not retrieve Enum value at idx=" << index;
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

template<typename T>
void Enum::underlying_value(const std::string& name, T& data) const
{
  check_type(data);

  if (0 > H5Tenum_valueof(static_cast<hid_t>(*this), name.c_str(), &data))
  {
    std::stringstream ss;
    ss << "Could not retrieve Enum value with name=" << name;
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

template<typename T>
T Enum::value(size_t index) const
{
  typename std::underlying_type<T>::type t;
  underlying_value(index, t);
  return static_cast<T>(t);
}

template<typename T>
T Enum::value(const std::string& name) const
{
  typename std::underlying_type<T>::type t;
  underlying_value(name, t);
  return static_cast<T>(t);
}


} // namespace datatype
} // namespace hdf5
