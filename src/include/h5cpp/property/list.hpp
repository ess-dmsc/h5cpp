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
// Created on: Aug 15, 2017
//

#pragma once

#include <type_traits>

#include "../hdf5_capi.hpp"
#include "../object_handle.hpp"
#include "class.hpp"
#include "../windows.hpp"


namespace hdf5 {
namespace property{

class Class;



//!
//! \brief base class for property lists
//!
class DLL_EXPORT List
{
  public:
    //!
    //! \brief constructor
    //!
    //! @param plist_class
    //!
    explicit List(const Class &plist_class);

    //!
    //! \brief copy constructor
    //! @param plist
    //!
    List(const List &plist);

    //!
    //! \brief copy assignment
    //!
    List &operator=(const List &type);

    //!
    //! \brief destructor
    //!
    virtual ~List();

    List &operator=(List &&type) = default;
    List(List &&type) = default;

    //!
    //! \brief return property list class
    //!
    //! Return an instance of the property list class the list belongs to.
    //!
    //! \return class instance
    Class get_class() const;

    //!
    //! \brief conversion operator
    //!
    //! Use this operator to obtain the actual HDF5 handler to the list
    //! instance.
    //!
    explicit operator hid_t() const
    {
      return static_cast<hid_t>(handle_);
    }

  private:
    ObjectHandle handle_;

};

}  // namespace property
}  // namespace hdf5
