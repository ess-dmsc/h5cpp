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
#include <h5cpp/dataspace/dataspace.hpp>
#include <h5cpp/datatype/datatype.hpp>


namespace hdf5 {
namespace node {

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

    //!
    //! \brief copy assignment operator
    //!
    Group &operator=(const Group &group);

    //!
    //! \brief close the group
    //!
    void close() const;

    //!
    //! \brief flush group
    //!
    void flush() const;

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
    //! Like for groups the
    Dataset create_dataset(const std::string &name,
                           const datatype::Datatype &type,
                           const dataspace::Dataspace &space,
                           const property::LinkCreationList &lcpl = property::LinkCreationList(),
                           const property::DatasetCreationList &dcpl = property::DatasetCreationList(),
                           const property::DatasetAccessList &dapl = property::DatasetAccessList()
                           ) const;

    Node operator[](const std::string &name) const;

  private:
    IteratorConfig iter_config_;

};



} // namespace node
} // namespace hdf5
