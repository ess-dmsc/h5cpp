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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Aug 18, 2017
//

#include <type_traits>
#include <stdexcept>
#include <h5cpp/property/string_creation_list.hpp>

namespace hdf5 {
namespace property {


StringCreationList::StringCreationList():
    List(kStringCreate)
{}

StringCreationList::~StringCreationList()
{}

type::CharacterEncoding StringCreationList::character_encoding() const
{
   H5T_cset_t encoding;
   if(H5Pget_char_encoding(static_cast<hid_t>(*this),&encoding)<0)
   {
     throw std::runtime_error("Failure retrieving character encoding!");
   }
   return static_cast<type::CharacterEncoding>(encoding);
}

void StringCreationList::character_encoding(type::CharacterEncoding encoding) const
{
  if(H5Pset_char_encoding(static_cast<hid_t>(*this),static_cast<H5T_cset_t>(encoding))<0)
  {
    throw std::runtime_error("Failure setting character encoding!");
  }
}

StringCreationList::StringCreationList(const Class &plist_class):
    List(plist_class)
{}


} // namespace property
} // namespace hdf5
