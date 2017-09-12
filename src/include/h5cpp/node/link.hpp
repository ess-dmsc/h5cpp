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

#include "group.hpp"
#include "../path.hpp"
#include "../windows.hpp"

namespace hdf5 {
namespace node {

//!
//! \brief link target descriptor
//!
//! This class describes the target a link references. It consists of two parts
//! * the path to the object
//! * the path to the file within which the object is stored
//!
//! The latter one is required in order to handle external links where the
//! objet is not stored in the same file.
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

    boost::filesystem::path file_path() const;
    hdf5::Path object_path() const;

  private:
    boost::filesystem::path file_;
    hdf5::Path              object_path_;
};

//!
//! \brief a link
//!
//!
class DLL_EXPORT Link
{
  public:
    //!
    //! \brief constructor
    //!
    Link(const Group &parent_group,const Path &path);
    Link() = default;
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
    LinkTarget target() const;


    //!
    //! \brief get type of link
    //!
    LinkType type() const;

  private:
    Group parent_group_;
    Path  path_;
};


} // namespace node
} // namespace hdf5
