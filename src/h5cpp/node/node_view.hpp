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
// Created on: Sep 11, 2017
//
#pragma once

#include <h5cpp/node/group_view.hpp>
#include <h5cpp/core/path.hpp>
#include <h5cpp/property/link_access.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace node {

class Node;
class NodeIterator;

class DLL_EXPORT NodeView : public GroupView
{
  public:
    using value_type = Node;
    using const_iterator = NodeIterator;

    NodeView() = delete;
    NodeView(const NodeView &) = default;
    NodeView(Group &node);
    ~NodeView() override;

    Node operator[](size_t index) const;


    //!
    //! \brief checks existence of a node
    //!
    //! The name must be a valid child name (not a path). This function checks
    //! whether a link of a particular name can be resolved into an object.
    //!
    //!
    bool exists(const std::string &name,
                const property::LinkAccessList &lapl = property::LinkAccessList()) const;



    //!
    //! \brief get object by name
    //!
    //! Here the index is the name of the child node. A name can
    //! contain any character but the '.', '..' and '/'.
    //! Thus, unlike in the C-API we cannot access object relative
    //! to the group a view belongs to but only its direct children.
    //! This emphasizes the notion of an associative container which is
    //! connected with a gruop.
    //!
    //! \throws std::runtime_error in case of a failure
    //! \param name the name of the child to access
    //! \return instance of Node
    //!
    Node operator[](const std::string &name) const;

    const_iterator begin() const;
    const_iterator end() const;



};

} // namespace node
} // namespace hdf5
