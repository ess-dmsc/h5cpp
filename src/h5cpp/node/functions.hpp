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
//! \brief copy node object
//!
//! Copy `source` object to a new `relative_path` under `base` Group. If an object
//! of same name already exists an exception will be thrown.
//!
//! The copy operation should also work across file boundaries. In all cases the
//! source object as well as the destination group must exist.
//!
//! \param source object to be copied
//! \param base the destination base group where the new copy will be stored
//! \param relative_path the destination relative path under the base group
//! \param ocpl optional object copy property list
//! \param lcpl optional link creation property list
//! \throws std::runtime_error in case of a failure
//!
DLL_EXPORT void copy(const Node &source,
                     const Group &base,
                     const Path &relative_path,
                     const property::ObjectCopyList &ocpl = property::ObjectCopyList(),
                     const property::LinkCreationList &lcpl = property::LinkCreationList());

//!
//! \brief copy node object
//!
//! Copy `source` object to a new location under `destination` Group using the original object's
//! name. For instance, if we have
//!
//! * source path /detector/data
//! * destination path /recorded/detectors
//!
//! then the copy will appear as /recorded/detectors/data. If an object
//! of same name already exists an exception will be thrown.
//!
//! The copy operation should also work across file boundaries. In all cases the
//! source object as well as the destination group must exist.
//!
//! \param source object to be copied
//! \param destination the destination group where the new copy will be stored
//! \param ocpl optional object copy property list
//! \param lcpl optional link creation property list
//! \throws std::runtime_error in case of a failure
//!
DLL_EXPORT void copy(const Node &source,
                     const Group &destination,
                     const property::ObjectCopyList &ocpl = property::ObjectCopyList(),
                     const property::LinkCreationList &lcpl = property::LinkCreationList());

//!
//! \brief move node object
//!
//! Move `source` object to a new `relative_path` under `base` Group. If an object
//! of same name already exists an exception will be thrown. In all cases the
//! source object as well as the destination group must exist.
//!
//! \param source object to be moved
//! \param base the destination base group where the object will be moved
//! \param relative_path the destination relative path under the base group
//! \param lcpl optional link creation property list
//! \param lapl optional link access property list
//! \throws std::runtime_error in case of a failure
//!
DLL_EXPORT void move(const Node &source,
                     const Group &base,
                     const Path &relative_path,
                     const property::LinkCreationList &lcpl = property::LinkCreationList(),
                     const property::LinkAccessList &lapl = property::LinkAccessList());

//!
//! \brief move node object
//!
//! Move `source` object to a new location under `destination` Group using the original
//! object's name. For instance, if we have
//!
//! * source path /detector/data
//! * destination path /recorded/detectors
//!
//! then the moved object will appear as /recorded/detectors/data. If an object
//! of same name already exists an exception will be thrown. In all cases the
//! source object as well as the destination group must exist.
//!
//! \param source object to be moved
//! \param destination the new group where the object should be located
//! \param lcpl optional link creation property list
//! \param lapl optional link access property list
//! \throws std::runtime_error in case of a failure
//!
DLL_EXPORT void move(const Node &source,
                     const Group &destination,
                     const property::LinkCreationList &lcpl = property::LinkCreationList(),
                     const property::LinkAccessList &lapl = property::LinkAccessList());

//!
//! \brief remove node from group
//!
//! Removes link at `object_path` within the `base` Group. If there are more
//! references (links) to this particular object, they remain active.
//! Additionally: removing an object entirely from an HDF5 file means removing
//! all links to this object and thus rendering it inaccessible. No storage
//! space in the file will be cleared. In order to reduce the size of the
//! file `h5repack` must be used which will simply not copy objects
//! which cannot be referenced.
//!
//! \throws std::runtime_error in case of a failure
//! \param base group relative to which the link or object resides
//! \param object_path path relative to base determining the link or object to remove
//! \param lapl optional link access property list
//!
DLL_EXPORT void remove(const Group &base,
                       const Path &object_path,
                       const property::LinkAccessList &lapl = property::LinkAccessList());

//!
//! \brief remove node from group
//!
//! Removes link to `object` from parent Group via which it was accessed.
//!
//! \throws std::runtime_error in case of a failure
//!
//! \param object the object which to remove
//!
//! \pre `object` must be a valid HDF5 object instance
//! \param lapl optional link access property list
//!
//! \sa remove(const Node &base, const Path &object_path)
//!
DLL_EXPORT void remove(const Node &object,
                       const property::LinkAccessList &lapl = property::LinkAccessList());

//!
//! \brief Create a soft or external link
//!
//! Create a link from `link_path` under `link_base` to object at `target_path` under
//! `target_base`. A soft link will be created if `link_base` and `target_base` reside
//! in the same file. Otherwise an external link is created.
//!
//! The target for the link is determined by `target_base` and `target_path`.
//! If the latter one is a relative path the target location is assumed
//! relative to `target_base`. If it is an absolute path, `target_base` is used
//! to retrieve the root group of the specific file.
//!
//! \param target the target node (could also be path here?)
//! \param link_base the base group for the link location
//! \param link_path path to the new link (either relative or absolute)
//! \param lcpl optional link creation property list
//! \param lapl optional link access property list
//!
DLL_EXPORT void link(const Node &target,
                     const Group &link_base,
                     const Path &link_path,
                     const property::LinkCreationList &lcpl = property::LinkCreationList(),
                     const property::LinkAccessList &lapl = property::LinkAccessList());


//!
//! \brief Create a soft link
//!
//! Create a link from `link_path` under `link_base` to object at `target_path`. The object
//! at `target_path` need not already exist at this time.
//!
//! If the `target_path` is a relative path the target location is assumed
//! relative to `link_base`. If absolute, the path is assumed to be on the same file as
//! `link_base`.
//!
//! \param target_path the target node (could also be path here?)
//! \param link_base the base group for the link location
//! \param link_path path to the new link (either relative or absolute)
//! \param lcpl optional link creation property list
//! \param lapl optional link access property list
//!
DLL_EXPORT void link(const Path &target_path,
                     const Group &link_base,
                     const Path &link_path,
                     const property::LinkCreationList &lcpl = property::LinkCreationList(),
                     const property::LinkAccessList &lapl = property::LinkAccessList());

//!
//! \brief Create an external link
//!
//! Create an external link to an object stored in a different file. The target
//! object is determined by the target file and an absolute path within this
//! file. The location of the link is given by a base group and a relative or
//! absolute path. If link_path is a relative path the new link will be
//! relative to `link_base`. Otherwise `link_base` is only used to
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
//! \param lcpl optional link creation property list
//! \param lapl optional link access property list
//!
//! \pre `target_path` must be an absolute path
//! \pre `link_base` must be a valid HDF5 object
//!
DLL_EXPORT void link(const fs::path &target_file,
                     const Path &target_path,
                     const Group &link_base,
                     const Path &link_path,
                     const property::LinkCreationList &lcpl = property::LinkCreationList(),
                     const property::LinkAccessList &lapl = property::LinkAccessList());

//!
//! \brief get node
//!
//! Get a node from a base group.
//!
//! \throws std::runtime_error in case of a failure
//! \param base reference to the base group
//! \param node_path reference to the path of the node
//! \param lapl optional link access property list
//! \return new node instance
//!
DLL_EXPORT Node get_node(const Group &base,
                         const Path &node_path,
                         const property::LinkAccessList &lapl = property::LinkAccessList());


//!
//! \brief get real base of path
//!
//! Helper function to facilitate a number of convenience functions in the wrapper.
//! Gets the most proximate parent Group of `path`. If `path` is absolute, `base` will only
//! be used to obtain the root node of the file. If the parent node does not exist or is not
//! a Group, an exception will be thrown.
//!
//! \throws std::runtime_error in case of a failure
//! \param base base group for link
//! \param path path of desired node
//! \param lapl optional link access property list
//! \return most recent parent Group of path
//!
DLL_EXPORT Group get_real_base(const Group &base, const Path &path,
                               const property::LinkAccessList &lapl = property::LinkAccessList());

//!
//! \brief get group
//!
//! A convenience function for get_node. Returns a Group instance if the node referenced
//! by `path` is a group, otherwise throws an exception.
//! Use this function whenever you want to work with a Group temporarily.
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
//! \param base base group
//! \param path path to group
//! \param lapl optional link access property list
//! \return new Group instance
//! \sa get_node
//! \sa get_dataset
//!
DLL_EXPORT Group get_group(const Group &base,
                           const Path &path,
                           const property::LinkAccessList &lapl = property::LinkAccessList());
//!
//! \brief get dataset
//!
//! A convenience function for get_node. Returns a Dataset instance if the node referenced
//! by `path` is a dataset, otherwise throws an exception.
//! Use this function whenever you want to work with a Dataset temporarily.
//!
//! For instance
//! \code
//! Group root = file.root();
//! Dataspace space = get_dataset(root,"run_01/sensors/temperature").dataspace();
//! \endcode
//!
//! \throws std::runtime_error in case of a failure
//! \param base base group
//! \param path path to dataset
//! \param lapl optional link access property list
//! \return new Group instance
//! \sa get_node
//! \sa get_dataset
//!
DLL_EXPORT Dataset get_dataset(const Group &base,
                               const Path &path,
                               const property::LinkAccessList &lapl = property::LinkAccessList());


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
