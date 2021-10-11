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
// Author: Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 24, 2017
//
#pragma once

#include <h5cpp/core/object_handle.hpp>
#include <h5cpp/core/path.hpp>
#include <h5cpp/node/types.hpp>
#include <h5cpp/node/link.hpp>
#include <h5cpp/core/windows.hpp>
#include <h5cpp/core/object_id.hpp>
#include <h5cpp/attribute/attribute_manager.hpp>

namespace hdf5 {
namespace node {

class DLL_EXPORT Node
{
  public:
    //!
    //! \brief constructor
    //!
    //! \param handle rvalue reference to a handle instance
    //! \param link the path to the node
    //!
    Node(ObjectHandle &&handle,const Link &link);

    //!
    //! \brief default constructor
    //!
    //! In order to store
    //! objects in a container like a std::vector they must be default
    //! constructible. A default constructed object cannot be used
    //! for anything. Use the is_valid() function to check whether or
    //! not a Node instance refers to a valid HDF5 object or not.
    //!
    //! \sa is_valid()
    //!
    Node();

    //!
    //! \brief copy constructor
    //!
    //! We use the default implementation
    //!
    Node(const Node &);

    //!
    //! \brief copy assignment
    //!
    Node &operator=(const Node &node);

    //!
    //! \brief destructor
    //!
    //! Must be virtual as we want to derive child classes
    //! from here.
    //!
    virtual ~Node();


    //!
    //! \brief return the node type
    //!
    NodeType type() const;

    //!
    //! \brief get unique ID
    //!
    //! Return the unique ID of an object. This identifier must not be confused
    //! with an HDF5 handle (called `hid_t` in the C-API. This ID identifies
    //! an object uniquely within a program context.
    //!
    //! \return instance of ObjectId
    //!
    ObjectId id() const;

    explicit operator hid_t() const
    {
      return static_cast<hid_t>(handle_);
    }

    //!
    //! \brief true if an object is valid
    //!
    //!
    //! \sa Node()
    //!
    bool is_valid() const;

    //!
    //! @brief close the node
    //!
    //! Closes the node object and renders the node instance as invalid.
    //!
    void close();

    //!
    //! \brief return link to object
    //!
    //! This returns the link which was used to access the node.
    //!
    const Link &link() const;

    //!
    //! \brief access to the attribute manager
    //!
    attribute::AttributeManager attributes;

  private:
    ObjectHandle handle_; //!< access handle to the object
    Link link_;           //!< stores the link to the object
};

DLL_EXPORT bool operator==(const Node &lhs, const Node &rhs);
DLL_EXPORT bool operator!=(const Node &lhs, const Node &rhs);

} // namespace node
} // namespace hdf5
