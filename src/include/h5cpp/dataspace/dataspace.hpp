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
// Created on: Aug 24, 2017
//
#pragma once

#include "type.hpp"
#include "../object_handle.hpp"


namespace hdf5 {
namespace dataspace {

class Dataspace
{
  public:

    void close();

    //!
    //! \brief number of elements in the dataspace
    //!
    virtual hssize_t size() const;

    explicit operator hid_t() const
    {
      return static_cast<hid_t>(handle_);
    }

    //!
    //! \brief get the type of the dataset
    //!
    Type type() const;

  protected:
    Dataspace(Type type);
  private:
    ObjectHandle handle_;

};

} // namespace dataspace
} // namespace hdf5
