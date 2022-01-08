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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Sep 8, 2017
//
#pragma once

#include <h5cpp/core/filesystem.hpp>
#include <h5cpp/file/file.hpp>
#include <h5cpp/file/types.hpp>
#include <h5cpp/property/file_creation.hpp>
#include <h5cpp/property/file_access.hpp>
#include <h5cpp/core/windows.hpp>
#include <h5cpp/dataspace/dataspace.hpp>
#include <h5cpp/dataspace/type_trait.hpp>
#include <h5cpp/datatype/factory.hpp>
#include <h5cpp/error/error.hpp>
#include <h5cpp/core/utilities.hpp>


namespace hdf5 {
namespace file {

//!
//! \brief create a new file
//!
//! \param path the path to the new file
//! \param flags HDF5 file creation flags
//! \param fcpl reference to a file creation property list
//! \param fapl reference to a file access property list
//! \throws std::runtime_error in case of a failure
//! \return new instance of File
//! \sa AccessFlags
//! \sa FileCreationList
//! \sa FileAccessList
//!
DLL_EXPORT File create(const fs::path &path,
                       AccessFlags flags = AccessFlags::Exclusive,
                       const property::FileCreationList &fcpl = property::FileCreationList(),
                       const property::FileAccessList &fapl = property::FileAccessList());
DLL_EXPORT File create(const fs::path &path,
                       AccessFlagsBase flags,
                       const property::FileCreationList &fcpl = property::FileCreationList(),
                       const property::FileAccessList &fapl = property::FileAccessList());

//!
//! \brief open an existing file
//!
//! \param path the path to the file to open
//! \param flags file open flags
//! \param fapl reference to a file access property list
//! \throws std::runtime_error in case of a failure
//! \return a new File instance
//! \sa AccessFlags
//! \sa FileAccessList
//!
DLL_EXPORT File open(const fs::path &path,
                     AccessFlags flags = AccessFlags::ReadOnly,
                     const property::FileAccessList &fapl = property::FileAccessList());
DLL_EXPORT File open(const fs::path &path,
                     AccessFlagsBase flags,
                     const property::FileAccessList &fapl = property::FileAccessList());

//!
//! \brief check if the file reference by the path is an HDF5 file
//!
//! \param path reference to the files path
//! \throws std::runtime_error in case of a failure
//! \return true if the path references an HDF5 file, false otherwise
//!
DLL_EXPORT bool is_hdf5_file(const fs::path &path);

//!
//! \brief load an image file from a buffer
//!
//! \throws std::runtime_error in case of a failure
//! \tparam T source type
//! \param data reference to the source instance of T
//! \param flags file image flags
//! \return a new File instance
//! \sa ImageFlags
//!
template<typename T>
File from_buffer(T &data,
		 ImageFlags flags = ImageFlags::ReadOnly);
template<typename T>
File from_buffer(T &data,
		 ImageFlagsBase flags);
template<typename T>
File from_buffer(T &data,
		 const datatype::Datatype &mem_type,
		 const dataspace::Dataspace &mem_space,
		 ImageFlagsBase flags);

template<typename T>
File from_buffer(const T &data,
		 ImageFlags flags = ImageFlags::ReadOnly);
template<typename T>
File from_buffer(const T &data,
		 ImageFlagsBase flags);



template<typename T>
File from_buffer(T &data, ImageFlags flags)
{
  return from_buffer(data, static_cast<ImageFlagsBase>(flags));
}

template<typename T>
File from_buffer(const T &data, ImageFlags flags)
{
  return from_buffer(data, static_cast<ImageFlagsBase>(flags));
}

template<typename T>
File from_buffer(const T &data, ImageFlagsBase flags)
{
  if((flags & ImageFlags::ReadWrite) && (flags & ImageFlags::DontCopy))
    throw std::runtime_error("Invalid ImageFlags for const buffer: the DONT_COPY flag together with the READWRITE flag");
  return from_buffer(const_cast<T&>(data), static_cast<ImageFlagsBase>(flags));
}

template<typename T>
File from_buffer(T &data, ImageFlagsBase flags)
{
  auto mem_space = hdf5::dataspace::create(data);
  hdf5::datatype::DatatypeHolder mem_type_holder;
  return from_buffer(data, mem_type_holder.get(data), mem_space, flags);
}

template<typename T>
File from_buffer(T &data,
		 const datatype::Datatype &mem_type,
		 const dataspace::Dataspace &mem_space,
		 ImageFlagsBase flags)
{
  if ((flags & ImageFlags::DontCopy) && !(flags & ImageFlags::DontRelease))
    throw std::runtime_error("Invalid ImageFlags in from_buffer: the DONT_COPY flag without the DONT_RELEASE flag");
  size_t databytesize = signed2unsigned<size_t>(mem_space.size()) * mem_type.size();
  hid_t fid = 0;
  if(mem_type.get_class() == datatype::Class::Integer)
    {

      fid = H5LTopen_file_image(dataspace::ptr(data), databytesize, flags);
      if (fid < 0)
	{
	  std::stringstream ss;
	  ss << "Failure opening file image";
	  error::Singleton::instance().throw_with_stack(ss.str());
	}
      return File(ObjectHandle(fid));
    }
  else
    {
      std::stringstream ss;
      ss<<"Failure to open non-integer buffer";
      error::Singleton::instance().throw_with_stack(ss.str());
    }
  return File(hdf5::ObjectHandle(fid));
}

} // namespace file
} // namespace hdf5




