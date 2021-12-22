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

#include <h5cpp/node/node.hpp>
#include <h5cpp/node/link_view.hpp>
#include <h5cpp/node/node_view.hpp>
#include <h5cpp/node/dataset.hpp>
#include <h5cpp/core/iterator_config.hpp>
#include <h5cpp/property/link_creation.hpp>
#include <h5cpp/property/group_creation.hpp>
#include <h5cpp/property/group_access.hpp>
#include <h5cpp/property/dataset_creation.hpp>
#include <h5cpp/property/dataset_access.hpp>
#include <h5cpp/property/object_copy.hpp>
#include <h5cpp/dataspace/dataspace.hpp>
#include <h5cpp/datatype/datatype.hpp>


namespace hdf5 {
namespace node {

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif
class DLL_EXPORT Group : public Node
{
  public:
    LinkView      links;
    NodeView      nodes;

    //!
    //! \brief default constructor
    //!
    //! Does nothing else than calling the default constructor of Node and
    //! leaves in valid HDF5 object.
    //!
    Group();

    //!
    //! \brief copy constructor
    //!
    Group(const Group &group);

    //!
    //! \brief constructor
    //!
    //! Construct an instance of Group from a generic Node class.
    //!
    //! \throws std::runtime_error in case of a failure
    //!
    Group(const Node &node);

    //!
    //! \brief constructor
    //!
    //! \param parent reference to the parent group of the new group
    //! \param path the path to the new group
    //! \param lcpl reference to the link creation property list
    //! \param gcpl reference to the group creation property list
    //! \param gapl reference to the group access property list
    //!
    Group(const Group &parent,const Path &path,
          const property::LinkCreationList &lcpl = property::LinkCreationList(),
          const property::GroupCreationList &gcpl = property::GroupCreationList(),
          const property::GroupAccessList &gapl = property::GroupAccessList());

    virtual ~Group() override {}

    //!
    //! \brief copy assignment operator
    //!
    Group &operator=(const Group &group);

#if (defined(_DOXYGEN_) || H5_VERSION_GE(1,10,0))
    //!
    //! \brief flush the group (*since hdf5 1.10.0*)
    //!
    //! \throws std::runtime_error in case of a failure)
    //!
    void flush() const;
#endif

    //!
    //! \brief get reference to the iterator configuration
    //!
    //! Return a non-const reference to the iterator configuration for the group.
    //! \return reference to iterator configuration
    //!
    IteratorConfig &iterator_config() noexcept
    {
      return iter_config_;
    }

    //!
    //! \brief get reference to the interator configuration
    //!
    //! Return a const reference to the iterator configuration of the gruop.
    //! \return reference to iterator configuration
    //!
    const IteratorConfig &iterator_config() const noexcept
    {
      return iter_config_;
    }

    //!
    //! \brief checks existence of a node
    //!
    //! The name must be a valid link and valid child name. This function checks
    //! whether a link of a particular name exists and can be resolved into an
    //! object.
    //!
    bool exists(const std::string &name,
                const property::LinkAccessList &lapl = property::LinkAccessList()) const;


    //!
    //! \brief create a new group
    //!
    Group create_group(const std::string &name,
                       const property::LinkCreationList &lcpl = property::LinkCreationList(),
                       const property::GroupCreationList &gcpl = property::GroupCreationList(),
                       const property::GroupAccessList &gapl = property::GroupAccessList()) const;

    //!
    //! \brief create a new dataset
    //!
    Dataset create_dataset(const std::string &name,
                           const datatype::Datatype &type,
                           const dataspace::Dataspace &space,
                           const property::DatasetCreationList &dcpl = property::DatasetCreationList(),
                           const property::LinkCreationList &lcpl = property::LinkCreationList(),
                           const property::DatasetAccessList &dapl = property::DatasetAccessList()
                           ) const;


    //!
    //! \brief get node
    //!
    //! Retrieves node from group at specified `path`. Path can be relative or absolute.
    //!
    //! \param path path to node
    //! \throws std::runtime_error in case of a failure
    //! \return returns node if the link can be resolved
    //!
    Node operator[](const Path &path) const;

    //!
    //! \brief Create an external link
    //!
    //! Create an external link to an object stored in a different file. The target
    //! object is determined by the target file and an absolute path within this
    //! file. If link_path is a relative path the new link will be
    //! relative to the link_base group. Otherwise link_base is only used to
    //! determine the root group (and thus the file within which the link is
    //! placed).
    //!
    //! \throws std::runtime_error in case of a failure
    //!
    //! \param link_path absolute or relative path to the new link
    //! \param target_file the file where the link target is stored
    //! \param target_path absolute path to the object which we want to reference
    //!                    in the target file
    //! \param lcpl optional link creation property list
    //! \param lapl optional link access property list
    //!
    //! \pre `target_path` must be an absolute path
    //!
    void create_link(const Path &link_path,
                     const fs::path &target_file,
                     const Path &target_path,
                     const property::LinkCreationList &lcpl = property::LinkCreationList(),
                     const property::LinkAccessList &lapl = property::LinkAccessList());

    //!
    //! \brief Create a soft link
    //!
    //! Create a soft link to an object stored in the same file. If link_path is a
    //! relative path the new link will be relative to the link_base group.
    //!
    //! \throws std::runtime_error in case of a failure
    //!
    //! \param link_path absolute or relative path to the new link
    //! \param target_path absolute path to the object which we want to reference
    //!                    in the target file
    //! \param lcpl optional link creation property list
    //! \param lapl optional link access property list
    //!
    //! \pre `target_path` must be an absolute path
    //!
    void create_link(const Path &link_path,
                     const Path &target_path,
                     const property::LinkCreationList &lcpl = property::LinkCreationList(),
                     const property::LinkAccessList &lapl = property::LinkAccessList());

    //!
    //! \brief Create a soft or external link
    //!
    //! Create a link from `link_path` to `target` object. A soft link will be created if
    //! group and `target_base` reside in the same file. Otherwise an external link is created.
    //!
    //! The target for the link is determined by `target_base` and `target_path`.
    //! If the latter one is a relative path the target location is assumed
    //! relative to `target_base`. If it is an absolute path, `target_base` is used
    //! to retrieve the root group of the specific file.
    //!
    //!
    //! \param link_path path to the new link (either relative or absolute)
    //! \param target the target node
    //! \param lcpl optional link creation property list
    //! \param lapl optional link access property list
    //!
    void create_link(const Path &link_path,
                     const Node &target,
                     const property::LinkCreationList &lcpl = property::LinkCreationList(),
                     const property::LinkAccessList &lapl = property::LinkAccessList());

    //!
    //! \brief copy node object
    //!
    //! Copy `target` object to a new `link_path` within this Group. If an object
    //! of same name already exists an exception will be thrown.
    //!
    //! The copy operation should also work across file boundaries. In all cases the
    //! source object as well as the destination group must exist.
    //!
    //! \param link_path the destination relative path under the this group
    //! \param target object to be copied
    //! \param ocpl optional object copy property list
    //! \param lcpl optional link creation property list
    //! \throws std::runtime_error in case of a failure
    //!
    void copy_here(const Path &link_path,
                   const Node &target,
                   const property::ObjectCopyList &ocpl = property::ObjectCopyList(),
                   const property::LinkCreationList &lcpl = property::LinkCreationList());

    //!
    //! \brief copy node object
    //!
    //! Copy `target` object to a new location under this Group using the original object's
    //! name. If an object of same name already exists an exception will be thrown.
    //!
    //! The copy operation should also work across file boundaries. In all cases the
    //! source object as well as the destination group must exist.
    //!
    //! \param target object to be copied
    //! \param ocpl optional object copy property list
    //! \param lcpl optional link creation property list
    //! \throws std::runtime_error in case of a failure
    //!
    void copy_here(const Node &target,
                   const property::ObjectCopyList &ocpl = property::ObjectCopyList(),
                   const property::LinkCreationList &lcpl = property::LinkCreationList());

    //!
    //! \brief move node object
    //!
    //! Move `target` object to a new `link_path` under this Group. If an object
    //! of same name already exists an exception will be thrown.
    //!
    //! \param link_path the destination relative path under the this group
    //! \param target object to be moved
    //! \param lcpl optional link creation property list
    //! \param lapl optional link access property list
    //! \throws std::runtime_error in case of a failure
    //!
    //! \sa copy for the naming convention
    //!
    void move_here(const Path &link_path,
                   const Node &target,
                   const property::LinkCreationList &lcpl = property::LinkCreationList(),
                   const property::LinkAccessList &lapl = property::LinkAccessList());

    //!
    //! \brief move node object
    //!
    //! Move `target` object to a new location under this Group using the original
    //! object's name. If an object of same name already exists an exception will be thrown.
    //!
    //! \param target object to be moved
    //! \param lcpl optional link creation property list
    //! \param lapl optional link access property list
    //! \throws std::runtime_error in case of a failure
    //!
    void move_here(const Node &target,
                   const property::LinkCreationList &lcpl = property::LinkCreationList(),
                   const property::LinkAccessList &lapl = property::LinkAccessList());

    //!
    //! \brief remove node from group
    //!
    //! Remove link at `path` within this Group.
    //!
    //! \throws std::runtime_error in case of a failure
    //! \param path path of object to remove
    //! \param lapl optional link access property list
    //!
    //! \sa remove(const Node &base, const Path &object_path)
    //!
    void remove(const Path &path,
                const property::LinkAccessList &lapl = property::LinkAccessList());


    //!
    //! \brief reports if group has a link to a valid group at specified `path`
    //!
    //! \param path path to group
    //! \param lapl optional link access property list
    //! \return true if the group has a group, false otherwise
    //!
    bool has_group(const Path &path,
                   const property::LinkAccessList &lapl = property::LinkAccessList()) const noexcept;

    //!
    //! \brief reports if group has a link to a valid dataset at specified `path`
    //!
    //! \param path path to dataset
    //! \param lapl optional link access property list
    //! \return true if the group has a dataset, false otherwise
    //!
    bool has_dataset(const Path &path,
                     const property::LinkAccessList &lapl = property::LinkAccessList()) const noexcept;


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
    //! if(root.get_group("run_01/sensors").nodes.size()!=0)
    //! {
    //!
    //! }
    //! \endcode
    //!
    //! \throws std::runtime_error in case of a failure
    //! \param path path to group
    //! \param lapl optional link access property list
    //! \return new Group instance
    //! \sa get_node
    //! \sa get_dataset
    //!
    Group get_group(const Path &path,
                    const property::LinkAccessList &lapl = property::LinkAccessList()) const;

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
    //! Dataspace space = root.get_dataset("run_01/sensors/temperature").dataspace();
    //! \endcode
    //!
    //! \throws std::runtime_error in case of a failure
    //! \param path path to dataset
    //! \param lapl optional link access property list
    //! \return new Group instance
    //! \sa get_node
    //! \sa get_dataset
    //!
    Dataset get_dataset(const Path &path,
                        const property::LinkAccessList &lapl = property::LinkAccessList()) const;


 private:
    IteratorConfig iter_config_;

};
#ifdef __clang__
#pragma clang diagnostic pop
#endif


} // namespace node
} // namespace hdf5
