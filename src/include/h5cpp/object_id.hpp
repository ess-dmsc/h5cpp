//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5pp.
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
// Author: Martin Shetty <martin.shetty@esss.se>
//
#pragma once

extern "C" {
#include <hdf5.h>
}

#include <string>
#include <sstream>
#include <boost/filesystem.hpp>
#include "windows.hpp"
#include "object_handle.hpp"

namespace hdf5
{

//!
//! \brief Unique ID of an HDF5 object
//!
//! Such an ID is constructed from an ObjectHandle instance. However, no
//! reference to that handle is stored in the class.
//! An instance of ObjectId allows the unique identification of an HDF5 object
//! within the context of a program. The ID is currently formed from the
//! \li address of an object within the file it is stored
//! \li the HDF5 file number of the objects parent file
//!
//! Optinally we also provide the name of the the object is stored in.
//!
class DLL_EXPORT ObjectId
{
  public:
    //!
    //! \brief default constructor
    //!
    //! We need the default constructor for compliance with STL containers as
    //! we may want to store IDs in one.
    //!
    ObjectId();

    //!
    //! \brief constructor
    //!
    //! Construct an ID from a handler instance. If the handler is default
    //! constructed and thus invalid a default constructed Id instance will 
	//! be returned. 
    //!
    //! \param handle reference to an object handler
    //!
    ObjectId(const ObjectHandle &handle);

    //!
    //! \brief copy constructor
    //!
    //! We need this for compliance with STL containers. As all memebers of
    //! this class support copy construction and assignment we can safely use
    //! the default implementation, provided by the compiler, here.
    //!
    ObjectId(const ObjectId &id) = default;

    //!
    //! \brief Equality operator for IDs
    //!
    bool operator== (const ObjectId& other) const;

    //!
    //! \brief Inequality operator for IDs
    //!
    bool operator!= (const ObjectId& other) const;

    //!
    //! \brief Allows sorting of IDs
    //!
    //!
    bool operator< (const ObjectId& other) const;

    DLL_EXPORT friend std::ostream & operator<<(std::ostream &os, const ObjectId& p);

    //!
    //! \brief Get the HDF5 file number
    //!
    //! Return the HDF5 file number of the file the object referenced by this
    //! ID belongs to. If the ID is default constructed this method returns 0.
    //!
    //! \return file number of the parent file
    //!
    unsigned long file_number() const noexcept;

    //!
    //! \brief Get object address
    //!
    //! Return the address of the referenced object within its file.
    //! If the ID instance is default constructed this method returns 0.
    //!
    //! \return object address within its file
    //!
    haddr_t       object_address() const noexcept;

    //!
    //! \brief Get file name
    //!
    //! Return the name fo the file the object referenced by this ID is stored
    //! in. An empty path is returned in the case of a default constructed ID.
    //!
    //! \return path to the objects parent file
    //!
    boost::filesystem::path   file_name() const noexcept;

  private:
    unsigned long file_num_ {0};
    haddr_t       obj_addr_ {0};
    boost::filesystem::path   file_name_;

    //!
    //! \brief get the name of the file
    //!
    //! Private utility function to obtain the name of the file where the
    //! object is stored in.
    static std::string get_file_name(const ObjectHandle &handle);
};


}
