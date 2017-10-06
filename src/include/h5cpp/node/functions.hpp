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
// Created on: Sep 14, 2017
//
#pragma once

#include "node.hpp"
#include "group.hpp"
#include "dataset.hpp"
#include "../path.hpp"
#include "../property/link_creation_list.hpp"
#include "../property/link_access_list.hpp"

namespace hdf5 {
namespace node {

//!
//! \brief copy a node object
//!
//! Copy a Node instance to a new location destination (which, for obvious reasons,
//! must be a group). If copy of the object appears below the new group with the
//! object name part of its original path. For instance
//!
//! * source path /detector/data
//! * destination path /recorded/detectors
//!
//! The copy will appear with the new path /recorded/detectors/data. From that
//! point of view copy behaves like a copy command on a file system. If an object
//! of same name already exists below the destination path an exception will be
//! thrown.
//! Copy operation should work also across file boundaries. In all cases the
//! source object as well as the destination group must exist.
//!
//! \param source the source object to copy
//! \param destination the destination group where the new copy will be stored
//! \throws std::runtime_error in case of a failure
//!
void copy(const Node &source, const Group &destination);

void copy(const Node &source, const Group &base, const Path &rel_path);

//!
//! \brief move an object
//!
//! Move the object reference by source to a new group determined by
//! `destination_group`. Technically this is just a link operation.
//! A new hard link is created below the destination and the original old
//! hard link is removed.
//!
//! The new name of the object is the same as it was before.
//!
//! \param source reference to the object to move
//! \param destination_group the new group where the object should be located
//!
//! \sa copy for the naming convention
//!
void move(const Node &source,const Group &destination_group,
          const property::LinkCreationList &lcpl = property::LinkCreationList(),
          const property::LinkAccessList &lapl = property::LinkAccessList());

void move(const Node &source,const Group &destination,const Path &rel_path,
          const property::LinkCreationList &lcpl = property::LinkCreationList(),
          const property::LinkAccessList &lapl = property::LinkAccessList());


//!
//! \brief remove an object from the file
//!
//! This function basically removes the link used to create the actual Node
//! instance. If there are more references (links) to this particular object
//! they remain active.
//! Additionally: removing an object entirely from an HDF5 file means removing
//! all links to this object and thus rendering it inaccessible. No storage
//! space in the file will be cleared. In order to reduce the size of the
//! file `h5repack` must be used which will simply not copy objects
//! which cannot be referenced.
//!
//! \throws std::runtime_error in case of a failure
//!
//! \param object the object which to remove
//!
//! \pre `object` must be a valid HDF5 object instance
//! \param lapl optional reference to a link access property list
//!
void remove(const Node &object,
            const property::LinkAccessList &lapl = property::LinkAccessList());

//!
//! \brief remove an object relative to a base group
//!
//! Remove the object or link determined by rel_path relative to a base group.
//! rel_path must be a relative path otherwise an exception is thrown.
//!
//! \throws std::runtime_error in case of a failure
//! \param base group relative to which the link or object resides
//! \param rel_path path relative to base determining the link or object to remove
//! \param lapl optional reference to a link access property list
//!
//! \sa remove(const Node &node)
//!
void remove(const Group &base,const Path &rel_path,
            const property::LinkAccessList &lapl = property::LinkAccessList());


//!
//! \brief Create a soft or external link
//!
//! Create a soft or external link to an object referenced by `target_base` and
//! `target_path` to `link_base` and `link_path`. A soft link will be created
//! if `target_base` and `target_path` reside in the same file. Otherwise
//! an external link is created.
//!
//! The target for the link is determined by `target_base` and `target_path`.
//! If the latter one is a relative path the target location is assumed
//! relative to `target_base`. If it is an absolute path, `target_base` is used
//! to retrieve the root group of the specific file.
//!
//!
//! \param target_base the base group for the target
//! \param target_path the path to the target (either relative or absolute)
//! \param link_base the base group for the link location
//! \param link_path path to the new link (either relative or absolute)
//! \param lcpl optional reference to a link creation property list
//! \param lapl optional reference to a link access property list
//!
void link(const Group &target_base,const Path &target_path,
          const Group &link_base,const Path &link_path,
          const property::LinkCreationList &lcpl = property::LinkCreationList(),
          const property::LinkAccessList &lapl = property::LinkAccessList());

//!
//! \brief Create an external link
//!
//! Create an external link to an object stored in a different file. The target
//! object is determined by the target file and an absolute path within this
//! file. The location of the link is given by a base group and a relative or
//! absolute path. If link_path is a relative path the new link will be
//! relative to the link_base group. Otherwise link_base is only used to
//! determine the root group (and thus the file within which the link is
//! placed).
//!
//! \throws std::runtime_error in case of a failure
//!
//! \param target_file the file where the link target is stored
//! \param target_path absolute path to the object which we want to reference
//!                    in the target file
//! \param link_base base group for the link
//! \param link_path absolute or relative path to the new link
//! \param lcpl optional reference to a link creation property list
//! \param lapl optional reference to a link access property list
//!
//! \pre `target_path` must be an absolute path
//! \pre `link_base` must be a valid HDF5 object
//!
void link(const boost::filesystem::path &target_file,
          const Path &target_path,
          const Group &link_base,
          const Path &link_path,
          const property::LinkCreationList &lcpl = property::LinkCreationList(),
          const property::LinkAccessList &lapl = property::LinkAccessList());


} // namespace node
} // namespace hdf5
