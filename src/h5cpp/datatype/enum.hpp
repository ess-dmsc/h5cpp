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
  Enum(ObjectHandle&& handle);

  //!
  //! \brief construct from generic datatype
  //!
  Enum(const Datatype& type);

  //!
  //! \brief named constructor
  //!
  static Enum create(const Datatype& base_type);

  //!
  //! \brief return the total number of enum values
  //!
  size_t number_of_values() const;

  //!
  //! \brief insert enum value definition
  //!
  template<typename T>
  void insert(const std::string& name, const T& data) const;

  //!
  //! \brief get value name
  //!
  std::string name(size_t index) const;

  //!
  //! \brief get value at index
  //!
  template<typename T>
  void value(size_t index, T& data) const;

  //!
  //! \brief get value at index
  //!
  template<typename T>
  T value(size_t index) const;

  //!
  //! \brief get value by name
  //!
  template<typename T>
  void value(const std::string& name, T& data) const;

  //!
  //! \brief get value by name
  //!
  template<typename T>
  T value(const std::string& name) const;

  // TODO: Discuss H5Tenum_nameof with HDF group, no way of obtaining string size

 private:
  template<typename T>
  void check_type(const T& data) const;

};

template<typename T>
void Enum::check_type(const T& data) const
{
  auto mem_type = datatype::create<T>(data);
  if (mem_type != super())
  {
    std::stringstream ss;
    ss << "Attempt to insert enum value of mismatching type";
    throw (std::runtime_error(ss.str()));
  }
}

template<typename T>
void Enum::insert(const std::string& name, const T& data) const
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
void Enum::value(size_t index, T& data) const
{
  check_type(data);

  if (0 > H5Tget_member_value(static_cast<hid_t>(*this), index, &data))
  {
    std::stringstream ss;
    ss << "Could not retrieve Enum value at idx=" << index;
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

template<typename T>
void Enum::value(const std::string& name, T& data) const
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
  T t;
  value(index, t);
  return t;
}

template<typename T>
T Enum::value(const std::string& name) const
{
  T t;
  value(name, t);
  return t;
}


} // namespace datatype
} // namespace hdf5
