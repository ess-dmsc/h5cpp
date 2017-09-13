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

#include "../object_handle.hpp"
#include "../path.hpp"
#include "types.hpp"
#include "../windows.hpp"
#include "../object_id.hpp"

namespace hdf5 {
namespace node {

class DLL_EXPORT Node
{
  public:
    //!
    //! \brief constructor
    //!
    //! \param handle rvalue reference to a handle instance
    //! \param path the path to the node
    //!
    Node(ObjectHandle &&handle,const Path &path);

    //!
    //! \brief default constructor
    //!
    //! We use the default implementation here
    //!
    Node() = default;

    //!
    //! \brief copy constructor
    //!
    //! We use the default implementation
    //!
    Node(const Node &) = default;

    //!
    //! \brief destructor
    //!
    //! Must be virtual as we want to derive child classes
    //! from here.
    //!
    virtual ~Node();

    //!
    //! \brief return the path to the node
    //!
    //! The path returned by this function is the one used to
    //! access the object. Thus ambiguities with links to the same
    //! object can be avoided.
    //!
    //! \return path instance
    //!
    Path path() const;

    //!
    //! \brief return the node type
    //!
    Type type() const;

    ObjectId id() const;

    explicit operator hid_t() const
    {
      return static_cast<hid_t>(handle_);
    }

    bool is_valid() const;


  private:
    ObjectHandle handle_;
    Path path_;
};

} // namespace node
} // namespace hdf5
