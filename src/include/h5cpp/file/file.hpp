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
#include "../node/group.hpp"
#include "../property/group_access_list.hpp"

namespace hdf5 {
namespace file {

class DLL_EXPORT File
{
  public:
    File()             = default;
    File(const File &) = default;
    File(File &&)      = default;

    //!
    //! \brief constructor
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
    void close();

    boost::filesystem::path path() const;
    size_t count_open_objects(SearchFlags flag) const;
    size_t count_open_objects(SearchFlagsBase flags) const;

    node::Group root(const property::GroupAccessList &gapl = property::GroupAccessList()) const;

    explicit operator hid_t() const
    {
      return static_cast<hid_t>(handle_);
    }

  private:
    ObjectHandle handle_;

};

} // namespace file
} // namespace hdf5
