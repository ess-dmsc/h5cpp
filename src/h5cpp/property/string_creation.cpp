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
// Created on: Aug 18, 2017
//

#include <type_traits>
#include <h5cpp/property/string_creation.hpp>
#include <h5cpp/error/error.hpp>
#include <sstream>

namespace hdf5 {
namespace property {

StringCreationList::StringCreationList() :
    List(kStringCreate) {}

StringCreationList::~StringCreationList() {}

StringCreationList::StringCreationList(ObjectHandle &&handle) :
    List(std::move(handle)) {
  if ((get_class() != kStringCreate) &&
      (get_class() != kLinkCreate) &&
      (get_class() != kAttributeCreate)) {
    std::stringstream ss;
    ss << "Cannot create property::StringCreationList from " << get_class();
    throw std::runtime_error(ss.str());
  }
}

datatype::CharacterEncoding StringCreationList::character_encoding() const {
  H5T_cset_t encoding;
  if (H5Pget_char_encoding(static_cast<hid_t>(*this), &encoding) < 0) {
    error::Singleton::instance().throw_with_stack("Failure retrieving character encoding!");
  }
  return static_cast<datatype::CharacterEncoding>(encoding);
}

void StringCreationList::character_encoding(datatype::CharacterEncoding encoding) const {
  if (H5Pset_char_encoding(static_cast<hid_t>(*this), static_cast<H5T_cset_t>(encoding)) < 0) {
    error::Singleton::instance().throw_with_stack("Failure setting character encoding!");
  }
}

StringCreationList::StringCreationList(const Class &plist_class) :
    List(plist_class) {}

} // namespace property
} // namespace hdf5
