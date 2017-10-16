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
// Created on: Sep 8, 2017
//
#pragma once

#include "types.hpp"
#include <boost/filesystem.hpp>
#include "../windows.hpp"
#include "../object_handle.hpp"
#include "../object_id.hpp"
#include "../property/group_access_list.hpp"

namespace hdf5 {
namespace node {
class Group;
}
}

namespace hdf5 {
namespace file {

class DLL_EXPORT File
{
  public:
    //!
    //! \brief default constructor
    //!
    //! Use default implementation here. We need this to store instances of
    //! this class in an STL container. A default constructed instance of File
    //! is in an invalid state. This can be checked using the is_valid()
    //! method.
    //!
    //! \sa is_valid()
    //!
    File()             = default;

    //!
    //! \brief copy constructor
    //!
    //! Use default implementation here.
    //!
    File(const File &) = default;

    //!
    //! \brief move constructor
    //!
    //! Use default implementation here.
    //!
    File(File &&)      = default;

    //!
    //! \brief constructor
    //!
    //! Construct a file from an rvalue reference to a handle.
    //!
    //! \param handle rvalue reference to the file handler
    //!
    explicit File(ObjectHandle &&handle);

    File &operator=(const File&) = default;

    //!
    //! \brief get access flags for the file
    //!
    //! \throws std::runtime_error in case of a failure
    //!
    AccessFlags intent() const;

    //!
    //! \brief get the file size in bytes
    //!
    //! \throws std::runtime_error in case of a failure
    //!
    size_t size() const;

    //!
    //! \brief flush the file
    //!
    //! \throws std::runtime_error in case of a failure
    //! \param scope the scope within which the file should be flushed
    //!
    void flush(Scope scope) const;

    //!
    //! \brief close the file
    //!
    //! \throws std::runtime_error in case of a failure
    //!
    void close();

    //!
    //! \brief get path on file system
    //!
    //! Return the file system path of the file.
    //!
    boost::filesystem::path path() const;

    //!
    //! \brief count number of open objects
    //!
    //! Return the number of open objects belonging to that very file instance.
    //!
    size_t count_open_objects(SearchFlags flag) const;
    size_t count_open_objects(SearchFlagsBase flags) const;

    //!
    //! \brief get root group
    //!
    //! Return an instance to the root group of the file.
    //!
    //! \throws std::runtime_error in case of a failure
    //!
    //! \param gapl reference to a group access property list
    //! \return new instance of node::Group
    //!
    node::Group root(const property::GroupAccessList &gapl = property::GroupAccessList()) const;

    explicit operator hid_t() const
    {
      return static_cast<hid_t>(handle_);
    }

    //!
    //! \brief check validity of the instance
    //!
    //! Return true if the instance refers to a valid HDF5 file instance.
    //!
    //! \throw std::runtime_error in case of a failure
    //!
    //! \return true if valid, false otherwise
    bool is_valid() const;

    //!
    //! \brief return a unique id for the file object
    //!
    //! Return an instance of ObjectId which uniquely identifies a file object.
    //!
    ObjectId id() const;


  private:
    ObjectHandle handle_; //!< handle for the file object

};

} // namespace file
} // namespace hdf5
