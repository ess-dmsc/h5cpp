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
// Created on: Aug 23, 2017
//
#pragma once

#include <type_traits>
#include <h5cpp/datatype/datatype.hpp>
#include <h5cpp/windows.hpp>

namespace hdf5 {
namespace datatype {

//!
//! \brief HDF5 integer datatype
//!
class DLL_EXPORT Integer : public Datatype
{
  public:
    //!
    //! \brief Default constructor
    //!
    //! We need this for compatability with STL containers. However, we
    //! can use the compiler provided default version.
    //!
    Integer() = default;

    //!
    //! \brief Construct from object handle
    //!
    //! Construct a type from an object handle. The datatype takes full
    //! ownership of the handle whose lifetime is thus bound to the lifetime
    //! of the type.
    //!
    //! \param handle rvalue reference to a new object handle.
    //!
    Integer(ObjectHandle &&handle);

    //!
    //! \brief Copy construction from a Datatype instance
    //!
    //! This copy constructor creates an integer type from an instance of
    //! Datatype. The datatype has to satisfy two conditions
    //!
    //! \li it must be a valid object (is_valid() shoudld return true)
    //! \li it must reference an integer datatype.
    //!
    //! Failure to satify one of the above conditions will cause an
    //! exception.
    //!
    //! \throws std::runtime_error in case of any failure
    //!
    //! \param datatype reference to a Datatype instance
    //!
    Integer(const Datatype &datatype);

};


} // namespace datatype
} // namespace hdf5
