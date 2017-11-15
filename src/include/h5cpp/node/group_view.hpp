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

#include <h5cpp/node/types.hpp>
#include <h5cpp/property/link_access.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace node {

// forward declaration
class Group;

//!
//! \brief base class for group views
//!
//! This is the base class for all views on a group. Views
//! provide an STL compliant read only interface to links and
//! nodes stored below a group.
class DLL_EXPORT GroupView
{
  public:
    GroupView() = delete;
    GroupView(const GroupView &)=default;

    //!
    //! \brief constructor
    //!
    //! \param parent_group reference to the parent group
    //!
    GroupView(Group &parent_group);
    virtual ~GroupView();

    //!
    //! \brief get number of links
    //!
    //! Return the number of links attached to a group.
    //!
    //! \return number of link
    //!
    size_t size() const;

    //!
    //! \brief return reference to the parent group
    //!
    //! Returns a reference to the group this very view belongs to.
    //!
    //! \return reference to group
    //!
    const Group& group() const noexcept
    {
      return group_;
    }
  private:

    Group &group_;

};

} // namespace node
} // namespace hdf5
