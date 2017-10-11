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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Sep 14, 2017
//
#pragma once

#include "../datatype/datatype.hpp"
#include "../dataspace/dataspace.hpp"
#include "../datatype/factory.hpp"
#include "../dataspace/type_trait.hpp"
#include "../object_handle.hpp"
#include "../windows.hpp"

namespace hdf5 {
namespace attribute {

class DLL_EXPORT Attribute
{
  public:
    //!
    //! \brief constructor
    //!
    //! \param handle rvalue reference to the attributes handle
    //!
    Attribute(ObjectHandle &&handle);

    //!
    //! \brief default constructor
    //!
    //! Uses default compiler implementation.
    //!
    Attribute() = default;

    //!
    //! \brief copy assignment operator
    //!
    //! Uses default compiler implementation.
    //!
    Attribute(const Attribute &) = default;

    //!
    //! \brief return the data type of the attribute
    //!
    //! Returns a copy of the datatype used to create the attribute.
    //!
    datatype::Datatype datatype() const;

    //!
    //! \brief return the dataspace of the attribute
    //!
    //! Returns the dataspace used to create the attribute.
    //!
    dataspace::Dataspace dataspace() const;

    //!
    //! \brief return the name of the attribute
    //!
    std::string name() const;

    //!
    //! \brief check if object is valid
    //!
    bool is_valid() const;

    template<typename T>
    void write(const T& data) const;

    template<typename T>
    void write(const T& data,const datatype::Datatype &mem_type) const;

    template<typename T>
    void read(T &data) const;

    template<typename T>
    void read(T &data,const datatype::Datatype &mem_type) const;

  private:
    ObjectHandle handle_;
};

template<typename T>
void Attribute::write(const T &data,const datatype::Datatype &mem_type) const
{

}

template<typename T>
void Attribute::write(const T &data) const
{
  auto type = datatype::create<T>();
  auto space = dataspace::create(data);
  const void *ptr = dataspace::cptr(data);

  if(H5Awrite(static_cast<hid_t>(handle_),static_cast<hid_t>(type),ptr)<0)
  {
    throw std::runtime_error("Failure to write data to attribute!");
  }

}

template<typename T>
void Attribute::read(T &data) const
{
  auto type = datatype::create<T>();
  auto space = dataspace::create(data);
  void *ptr = dataspace::ptr(data);

  if(H5Aread(static_cast<hid_t>(handle_),static_cast<hid_t>(type),ptr)<0)
  {
    throw std::runtime_error("Failure to read data from attribute!");
  }
}

template<typename T>
void Attribute::read(T &data,const datatype::Datatype &mem_type) const
{

}



} // namespace attribute
} // namespace hdf5
