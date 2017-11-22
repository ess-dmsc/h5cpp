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

#include <h5cpp/node/node.hpp>
#include <h5cpp/node/group.hpp>
#include <h5cpp/node/dataset.hpp>
#include <h5cpp/core/path.hpp>
#include <h5cpp/property/link_creation.hpp>
#include <h5cpp/property/link_access.hpp>
#include <h5cpp/property/object_copy.hpp>
#include <h5cpp/core/windows.hpp>

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
//! \param ocpl optional reference to a object copy property list
//! \param lcpl optional reference to a link creation property list
//! \throws std::runtime_error in case of a failure
//!
DLL_EXPORT void copy(const Node &source, const Group &destination,
                     const property::ObjectCopyList &ocpl = property::ObjectCopyList(),
                     const property::LinkCreationList &lcpl = property::LinkCreationList());

DLL_EXPORT void copy(const Node &source, const Group &base, const Path &rel_path,
                     const property::ObjectCopyList &ocpl = property::ObjectCopyList(),
                     const property::LinkCreationList &lcpl = property::LinkCreationList());

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
//! \param lcpl optional reference to a link creation property list
//! \param lapl optional reference to a link access property list
//! \throws std::runtime_error in case of a failure
//!
//! \sa copy for the naming convention
//!
DLL_EXPORT void move(const Node &source,
                     const Group &destination_base,
                     const property::LinkCreationList &lcpl = property::LinkCreationList(),
                     const property::LinkAccessList &lapl = property::LinkAccessList());

DLL_EXPORT void move(const Node &source,
                     const Group &destination_base,
                     const Path &destination_path,
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
DLL_EXPORT void remove(const Node &object,
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
DLL_EXPORT void remove(const Group &base,const Path &rel_path,
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
//! \param target the target node (could also be path here?)
//! \param link_base the base group for the link location
//! \param link_path path to the new link (either relative or absolute)
//! \param lcpl optional reference to a link creation property list
//! \param lapl optional reference to a link access property list
//!
DLL_EXPORT void link(const Node &target,
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
DLL_EXPORT void link(const boost::filesystem::path &target_file,
                     const Path &target_path,
                     const Group &link_base,
                     const Path &link_path,
                     const property::LinkCreationList &lcpl = property::LinkCreationList(),
                     const property::LinkAccessList &lapl = property::LinkAccessList());


//!
//! \brief get a node
//!
//! Get a node from a base group.
//!
//! \throws std::runtime_error in case of a failure
//! \param base reference to the base group
//! \param node_path reference to the path of the node
//! \return new node instance
DLL_EXPORT Node get_node(const Group &base,
                         const Path &node_path,
                         const property::LinkAccessList &lapl=
                             property::LinkAccessList());

//!
//! \brief get a group
//!
//! This is more or less a convenience function for get_node. It actually
//! returns a Group instance if the node referenced by group_path is a group,
//! otherwise an exception will be thrown.
//! Use this function whenever you want to work with a Group only temporarily
//!
//! For instance
//! \code
//! Group root = file.root();
//! if(get_group(root,"run_01/sensors").nodes.size()!=0)
//! {
//!
//! }
//! \endcode
//!
//! \throws std::runtime_error in case of a failure
//! \param base reference to the base group
//! \param group_path reference to the path of the group
//! \return new Group instance
//! \sa get_node
//! \sa get_dataset
DLL_EXPORT Group get_group(const Group &base,
                           const Path &group_path,
                           const property::LinkAccessList &lapl =
                               property::LinkAccessList());
//!
//! \brief get a dataset
//!
//! This is more or less a convenience function for get_node. It actually
//! returns a Dataset instance if the node referenced by dataset_path is a
//! dataset, otherwise an exception will be thrown.
//! Use this function whenever you want to work with a Dataset only temporarily
//!
//! For instance
//! \code
//! Group root = file.root();
//! Dataspace space = get_dataset(root,"run_01/sensors/temperature").dataspace();
//! \endcode
//!
//! \throws std::runtime_error in case of a failure
//! \param base reference to the base group
//! \param group_path reference to the path of the group
//! \return new Group instance
//! \sa get_node
//! \sa get_dataset
DLL_EXPORT Dataset get_dataset(const Group &base,
                               const Path &dataset_path,
                               const property::LinkAccessList &lapl =
                                   property::LinkAccessList());


//!
//! \brief predicate function returning true if node is a group
//!
//! This predicate function is used to filter group nodes. A typical
//! application would be for instance
//!
//! \code
//! std::vector<Group> groups;
//! std::copy_if(root.nodes.begin(),root.nodes.end(),std::back_inserter(groups),is_group);
//! \endcode
//!
//! or whenever you want to partition a vector
//! \code
//! std::vector<Node> nodes;
//! std::copy(root.nodes.begin(),root.nodes.end(),std::back_inserter(nodes));
//! auto first_dset = std::partition_by(nodes.begin(),nodes.end(),is_group);
//! \endcode
//!
//! \throws std::runtime_error in case of a failure
//! \param node reference to the node
//! \return true if the node is a group, false otherwise
//!
DLL_EXPORT bool is_group(const Node &node);

//!
//! \brief predicate function returning true if a node is a dataset
//!
//! This predicate function is used to filter dataset nodes. A typical
//! application would be for instance
//!
//! \code
//! std::vector<Dataset> datasets;
//! std::copy_if(root.nodes.begin(),root.nodes.end(),std::back_inserter(datasets),is_dataset);
//! \endcode
//!
//! or whenever you want to partition a vector
//! \code
//! std::vector<Nodes> nodes;
//! std::copy(root.nodes.begin(),root.nodes.end(),std::back_inserter(nodes));
//! auto first_group = std::partition_by(nodes.begin(),nodes.end(),is_dataset);
//! \endcode
//!
//! \throws std::runtime_error in case of a failure
//! \param node reference to the node
//! \return true if the node is a dataset, false otherwise
//!
DLL_EXPORT bool is_dataset(const Node &node);

} // namespace node
} // namespace hdf5
