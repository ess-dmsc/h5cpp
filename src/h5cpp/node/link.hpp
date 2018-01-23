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

#include <h5cpp/file/file.hpp>
#include <h5cpp/core/path.hpp>
#include <h5cpp/core/windows.hpp>
#include <h5cpp/property/link_access.hpp>
#include <h5cpp/node/types.hpp>

namespace hdf5 {
namespace node {

class Group;
class Node;

//!
//! \brief link target descriptor
//!
//! This class describes the target a link references. It consists of two parts
//! * the path to the object
//! * the path to the file within which the object is stored
//!
//! The latter one is required in order to handle external links where the
//! object is not stored in the same file.
//!
class DLL_EXPORT LinkTarget
{
  public:
    //!
    //! \brief default constructor
    //!
    LinkTarget();

    //!
    //! \brief constructor
    //!
    //! Could be used mainly for internal hard or soft links. Its only argument
    //! is the path to the object within the file.
    //!
    //! \param object_path  path to object within the file
    //!
    explicit LinkTarget(const hdf5::Path &object_path);

    //!
    //! \brief constructor
    //!
    //! Could be used for external links.
    //!
    //! \param object_path path to the object within the  file
    //! \param file_path path to the file within which the object is stored
    //!
    explicit LinkTarget(const hdf5::Path &object_path,const boost::filesystem::path &file_path);

    //!
    //! \brief get file path
    //!
    //! Return the path to the file where the link target is located.
    //!
    boost::filesystem::path file_path() const;

    //!
    //! \brief get object path
    //!
    //! Return the object path to the link target within its file.
    //!
    hdf5::Path object_path() const;

  private:
    boost::filesystem::path file_;
    hdf5::Path              object_path_;
};

//!
//! \brief a link
//!
//! Class representing a link to an object within an HDF5 file. In order to store links
//! in a container they have to be default constructable. A default constructed link has the
//! type LinkType::ERROR.
//! Instead of a node type only the handle to the parent is stored. Thus, the parent can
//! also be a File which would identify the link as the link to the root group.
//!
class DLL_EXPORT Link
{
  public:
    //!
    //! \brief constructor
    //!
    //! \param file reference to the file via which the link was accessed
    //! \param parent_path the object path to the links parent
    //1 \param link_name the name of the link below its parent
    //!
    Link(const file::File &file,
         const Path &parent_path,
         const std::string &link_name);

    //!
    //! \brief default constructor
    //!
    //! Leaves a link of type LinkType::ERROR.
    //!
    Link() = default;

    //!
    //! \brief copy constructor
    //!
    Link(const Link &) = default;

    //!
    //! \brief get path of the link
    //!
    //! Return the actual path of the link in the file. This is basically
    //! the path of the parent group with the name of the link as a top element.
    //!
    Path path() const;

    //!
    //! \brief path to reference object
    //!
    //! Return the path to the object which is reference by this link.
    LinkTarget target(const property::LinkAccessList &lapl = property::LinkAccessList()) const;


    //!
    //! \brief get type of link
    //!
    LinkType type(const property::LinkAccessList &lapl = property::LinkAccessList()) const;

    //!
    //! \brief get reference to parent group
    //!
    //! Return a const reference to the parent group of the link.
    //!
    Group parent() const;

    const file::File &file() const;

    //!
    //! \brief get the node that the link references
    //!
    //! Return an instance to the node referenced by this particular link.
    //!
    //! \precondition all intermediate links exist and the final link must be
    //!               resolvable.
    Node operator*() const;


    //!
    //! \brief returns true if the given link exists
    //!
    bool exists() const;

    //!
    //! \brief returns true if the object reference by the link exists
    //!
    bool is_resolvable() const;


    DLL_EXPORT friend bool operator==(const Link &lhs, const Link &rhs);

  private:
    file::File parent_file_;   //!< the file via which the link was accessed
    Path parent_path_;   //!< the object path to the parent of the link
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif
    std::string  name_;  //!< the name of the link
#ifdef _MSC_VER
#pragma warning(pop)
#endif

    H5L_info_t get_link_info(const property::LinkAccessList &lapl) const;
    std::string get_link_value(const property::LinkAccessList &lapl) const;
    LinkTarget get_soft_link_target(const property::LinkAccessList &lapl) const;
    LinkTarget get_external_link_target(const property::LinkAccessList &lapl) const;
};

DLL_EXPORT bool operator!=(const Link &lhs, const Link &rhs);

DLL_EXPORT std::ostream &operator<<(std::ostream &stream,const Link &link);

} // namespace node
} // namespace hdf5
