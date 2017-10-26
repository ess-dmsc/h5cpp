//
// (c) Copyright 2017 DESY,ESS
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
// Author: Martin Shetty <martin.shetty@esss.se>
// Created on: Oct 11, 2017
//

#include <stdexcept>
#include <h5cpp/datatype/string.hpp>

namespace hdf5 {
namespace datatype {

String::String(ObjectHandle &&handle):
    Datatype(std::move(handle))
{}

String::String(const Datatype &type):
    Datatype(type)
{}

String String::variable()
{
  String ret = ObjectHandle(H5Tcopy(H5T_C_S1));
  if(H5Tset_size(static_cast<hid_t>(ret),H5T_VARIABLE)<0)
  {
    throw std::runtime_error("Failure to set the datatype size!");
  }
  return ret;
}

String String::fixed(size_t size)
{
  String ret = ObjectHandle(H5Tcopy(H5T_C_S1));
  H5Tset_size(static_cast<hid_t>(ret),size+1);
  return ret;
}

bool String::is_variable_length() const
{
  htri_t ret = H5Tis_variable_str( static_cast<hid_t>(*this) );
  if (0 > ret)
  {
    throw std::runtime_error("String: Failure to determine if string is variable-length");
  }
  return (0 != ret);
}

CharacterEncoding String::encoding() const
{
  H5T_cset_t ret = H5Tget_cset( static_cast<hid_t>(*this) );
  if (0 > ret)
  {
    throw std::runtime_error("String: Failure to determine character encoding");
  }
  return static_cast<CharacterEncoding>(ret);
}

void String::set_encoding(CharacterEncoding cset)
{
  if (0 > H5Tset_cset( static_cast<hid_t>(*this),
                       static_cast<H5T_cset_t>(cset) ))
    throw std::runtime_error("String: Failure to set character encoding");
}

StringPad String::padding() const
{
  H5T_str_t ret = H5Tget_strpad( static_cast<hid_t>(*this) );
  if (H5T_STR_ERROR == ret)
  {
    throw std::runtime_error("String: Failure to determine string padding");
  }
  return static_cast<StringPad>(ret);
}

void String::set_padding(StringPad strpad)
{
  if (0 > H5Tset_strpad( static_cast<hid_t>(*this),
                         static_cast<H5T_str_t>(strpad) ))
    throw std::runtime_error("String: Failure to set string padding");
}

size_t String::size() const
{
  if (is_variable_length())
    return H5T_VARIABLE;
  auto ret = Datatype::size();
  if (ret > 0)
    return ret - 1; // padding
  return 0;
}

void String::set_size(size_t size) const
{
  if (!is_variable_length())
    Datatype::set_size(size + 1); // padding
}



} // namespace datatype
} // namespace hdf5
