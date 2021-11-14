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

#include <sstream>
#include <h5cpp/datatype/enum.hpp>
#include <h5cpp/error/error.hpp>

namespace hdf5
{
namespace datatype
{

Enum::Enum(ObjectHandle&& handle) :
    Datatype(std::move(handle)) {}

Enum::Enum(const Datatype& type) :
    Datatype(type)
{
  if (get_class() != Class::Enum)
  {
    std::stringstream ss;
    ss << "Cannot create Enum datatype from " << get_class();
    throw std::runtime_error(ss.str());
  }
}

Enum Enum::create_underlying(const Datatype& base_type)
{
  hid_t ret = H5Tenum_create(static_cast<hid_t>(base_type));
  if (ret < 0)
  {
    std::stringstream ss;
    ss << "Could not create Enum of base type =" << base_type.get_class();
    error::Singleton::instance().throw_with_stack(ss.str());
  }
  return Enum(ObjectHandle(ret));
}

// implementation same as for Compound
size_t Enum::number_of_values() const
{
  int n = H5Tget_nmembers(static_cast<hid_t>(*this));
  if (n < 0)
  {
    error::Singleton::instance().throw_with_stack("Could not retrieve number of values for enum data type!");
  }
  return static_cast<size_t>(n);
}

// implementation same as for Compound
std::string Enum::name(size_t index) const
{
  char *buffer = H5Tget_member_name(static_cast<hid_t>(*this), static_cast<uint32_t>(index));
  if (buffer == nullptr) {
    std::stringstream ss;
    ss << "Failure to obtain name of value [" << index << "] in enum data type!";
    error::Singleton::instance().throw_with_stack(ss.str());
  }
  std::string name(buffer);

  if (H5free_memory(buffer) < 0) {
    std::stringstream ss;
    ss << "Failure freeing memory for name buffer of field [" << index << "]"
       << " in enum data type!";
    error::Singleton::instance().throw_with_stack(ss.str());
  }
  return name;
}


} // namespace datatype
} // namespace hdf5
