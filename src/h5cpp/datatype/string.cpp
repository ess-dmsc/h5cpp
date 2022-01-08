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
// Author: Martin Shetty <martin.shetty@esss.se>
// Created on: Oct 11, 2017
//

#include <h5cpp/datatype/string.hpp>
#include <h5cpp/error/error.hpp>
#include <sstream>

namespace hdf5 {
namespace datatype {

String::String(ObjectHandle &&handle) :
    Datatype(std::move(handle))
{}

String::String(const Datatype &type) :
    Datatype(type)
{
  if (get_class() != Class::String)
  {
    std::stringstream ss;
    ss << "Cannot create datatype::String from " << get_class();
    throw std::runtime_error(ss.str());
  }
}

String String::variable()
{
  // We assume no H5 errors are possible here
  String ret = ObjectHandle(H5Tcopy(H5T_C_S1));
  H5Tset_size(static_cast<hid_t>(ret), kVariable);
  return ret;
}

String String::fixed(size_t size)
{

  if(size==0)
  {
    std::stringstream ss;
    ss<<"String size of 0 is not supported!";
    throw std::runtime_error(ss.str());
  }

  // We assume no H5 errors are possible here
  String ret = ObjectHandle(H5Tcopy(H5T_C_S1));
  H5Tset_size(static_cast<hid_t>(ret), size );
  return ret;
}

bool String::is_variable_length() const
{
  htri_t ret = H5Tis_variable_str(static_cast<hid_t>(*this));
  if (0 > ret)
  {
    std::stringstream ss;
    ss<<"Could not determine if String is variable-length";
    error::Singleton::instance().throw_with_stack(ss.str());
  }
  return (0 != ret);
}

CharacterEncoding String::encoding() const
{
  H5T_cset_t ret = H5Tget_cset(static_cast<hid_t>(*this));
  if (0 > ret)
  {
    std::stringstream ss;
    ss<<"Could not determine String character encoding";
    error::Singleton::instance().throw_with_stack(ss.str());
  }
  return static_cast<CharacterEncoding>(ret);
}

void String::encoding(CharacterEncoding cset)
{
  if (0 > H5Tset_cset(static_cast<hid_t>(*this),static_cast<H5T_cset_t>(cset)))
  {
    std::stringstream ss;
    ss << "Could not set String character encoding to " << cset;
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

StringPad String::padding() const
{
  H5T_str_t ret = H5Tget_strpad(static_cast<hid_t>(*this));
  if (H5T_STR_ERROR == ret)
  {
    std::stringstream ss;
    ss<<"Could not determine String padding";
    error::Singleton::instance().throw_with_stack(ss.str());
  }
  return static_cast<StringPad>(ret);
}

void String::padding(StringPad strpad)
{
  if (0 > H5Tset_strpad(static_cast<hid_t>(*this),
                        static_cast<H5T_str_t>(strpad)))
  {
    std::stringstream ss;
    ss << "Could not set String padding to " << strpad;
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

size_t String::size() const
{
  if (is_variable_length())
    return kVariable;

  return Datatype::size();
}

void String::size(size_t size) const
{
  if (is_variable_length())
  {
    std::stringstream ss;
    ss << "Could not set size ("
       << size
       << ") for variable-size String datatype";
    throw std::runtime_error(ss.str());
  }

  if(size==0)
  {
    std::stringstream ss;
    ss<<"A string of size 0 is not supported!";
    throw std::runtime_error(ss.str());
  }
  Datatype::size(size); // padding
}

} // namespace datatype
} // namespace hdf5
