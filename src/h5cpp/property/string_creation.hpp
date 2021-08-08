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
#pragma once

#include <h5cpp/property/property_list.hpp>
#include <h5cpp/datatype/types.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace property {

class DLL_EXPORT StringCreationList : public List {
 public:
  //!
  //! \brief constructor
  //!
  StringCreationList();

  //!
  //! \brief destructor
  //!
  virtual ~StringCreationList() override;

  explicit StringCreationList(ObjectHandle &&handle);

  //!
  //! \brief get character encoding
  //! @return current character encoding
  //! \sa character_encoding
  datatype::CharacterEncoding character_encoding() const;

  //!
  //! \brief set character encoding
  //! @param encoding the required character encoding
  //! \sa character_encoding
  void character_encoding(datatype::CharacterEncoding encoding) const;

 protected:
  StringCreationList(const Class &plist_class);
};

}
}
