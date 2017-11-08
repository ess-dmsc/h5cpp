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
// Created on: Aug 21, 2017
//
#pragma once

#include <iostream>
#include <h5cpp/property/object_creation_list.hpp>
#include <h5cpp/types.hpp>
#include <h5cpp/datatype/datatype.hpp>
#include <h5cpp/datatype/type_trait.hpp>
#include <h5cpp/windows.hpp>

namespace hdf5 {
namespace property {

//!
//! \brief enumeration for the fill value status
//!
enum class DatasetFillValueStatus : std::underlying_type<H5D_fill_value_t>::type
{
  UNDEFINED = H5D_FILL_VALUE_UNDEFINED,
  DEFAULT   = H5D_FILL_VALUE_DEFAULT,
  USER_DEFINED = H5D_FILL_VALUE_USER_DEFINED
};

DLL_EXPORT std::ostream &operator<<(std::ostream &stream,const DatasetFillValueStatus &status);


//!
//! \brief enumeration for the fill time of a dataset
//!
enum class DatasetFillTime : std::underlying_type<H5D_fill_time_t>::type
{
  IFSET = H5D_FILL_TIME_IFSET,
  ALLOC = H5D_FILL_TIME_ALLOC,
  NEVER = H5D_FILL_TIME_NEVER
};

DLL_EXPORT std::ostream &operator<<(std::ostream &stream,const DatasetFillTime &time);


//!
//! \brief enumeration for the dataset allocation time
//!
//! The particular allocation strategy depends on the layout of the dataset.
//!
//! \sa DatasetLayout
//!
enum class DatasetAllocTime : std::underlying_type<H5D_alloc_time_t>::type
{
  //!
  //! \brief choose the default allocation strategy for the particular layout
  //!
  DEFAULT = H5D_ALLOC_TIME_DEFAULT,

  //!
  //! \brief all space is allocated when the dataset is created
  //!
  EARLY   = H5D_ALLOC_TIME_EARLY,

  //!
  //! \brief space is allocated as data is written to the file
  //!
  INCR    = H5D_ALLOC_TIME_INCR,

  //!
  //! \brief all space is allocated at the first write to the dataset
  //!
  LATE    = H5D_ALLOC_TIME_LATE
};

DLL_EXPORT std::ostream &operator<<(std::ostream &stream,const DatasetAllocTime &time);

//!
//! \brief enumeration describing the layout of a dataset
//!
enum class DatasetLayout : std::underlying_type<H5D_layout_t>::type
{
  COMPACT    = H5D_COMPACT,
  CONTIGUOUS = H5D_CONTIGUOUS,
  CHUNKED    = H5D_CHUNKED,
#if H5_VERSION_GE(1,10,0)
  VIRTUAL    = H5D_VIRTUAL
#endif
};

DLL_EXPORT std::ostream &operator<<(std::ostream &stream,const DatasetLayout &layout);

//!
//! \brief dataset creation property list
//!
class DLL_EXPORT DatasetCreationList : public ObjectCreationList
{
  public:
    DatasetCreationList();
    ~DatasetCreationList();

    //!
    //! \brief set dataset layout
    //! \throws std::runtime_error in case of failures
    //! \param layout required dataset layout
    //! \sa layout()
    //!
    void layout(DatasetLayout layout) const;

    //!
    //! \brief get dataset layout
    //! \throws std::runtime_error in case of failures
    //! \return new instance of DatasetLayout
    //! \sa layout(DatasetLayout layout)
    //! \sa DatasetLayout
    DatasetLayout layout() const;

    //!
    //! \brief set chunk dimensions
    //!
    //! The chunk dimensions must be of same rank as the dataspace used
    //! to create the dataset.
    //!
    //! \throws std::runtime_error in case of a failure
    //! \param chunk_dims vector with elements along each chunk dimension
    //! \sa chunk()
    void chunk(const hdf5::Dimensions &chunk_dims) const;

    //!
    //! \brief get chunk dimensions
    //! \throws std::runtime_error in case of a failure
    //! \returns an instance of hdf5::Dimensions with the number of elements along each
    //!          chunk dimension
    hdf5::Dimensions chunk() const;


    //!
    //! \brief set fill value for a dataset
    //!
    //! By default the library tries to deduce the appropriate HDF5 data type automatically.
    //! This will succeed if
    //!
    //! \list T is a native type already implemented in the library
    //! \list the user has provided an appropriate type trait to construct an HDF5
    //!       datatype for T
    //!
    //! Optionally, an HDF5 data type can be passed as a second argument to this member
    //! function. T must not necessarily be the same type used to create the dataset however,
    //! the two types must be convertible.
    //!
    //! \throws std::runtime_error in case of a failure
    //! \param value the actual fill value
    //! \param type an optional HDF5 data type
    //! \tparam T the type of the fill value
    //! \sa fill_value(const datatype::Datatype &type)
    template<typename T>
    void fill_value(const T &value,
                    const datatype::Datatype &type=datatype::TypeTrait<T>::create()) const;

    //!
    //! \brief get the fill value
    //!
    //! Get the fill value for a dataset stored in the property list as an instance of T.
    //! T must not necessarily be of the same type as the data type used t
    //!
    //! \tparam T requrested type for the fill value
    //! \param type optional HDF5 data type
    //!
    template<typename T>
    T fill_value(const datatype::Datatype &type=datatype::TypeTrait<T>::create()) const;

    DatasetFillValueStatus fill_value_status() const;

    //!
    //! \brief set fill time
    //!
    void fill_time(DatasetFillTime time) const;

    //!
    //! \brief get fill time
    //!
    DatasetFillTime fill_time() const;

    //!
    //! \brief set allocation time
    //!
    void allocation_time(DatasetAllocTime time) const;

    //!
    //! \brief get allocation time
    //!
    //! \sa DatasetAllocTime
    //! \sa allocation_time(DatasetAllocTime)
    //!
    DatasetAllocTime allocation_time() const;
};

template<typename T>
void DatasetCreationList::fill_value(const T &value,const datatype::Datatype &type) const
{
  if(H5Pset_fill_value(static_cast<hid_t>(*this),
                       static_cast<hid_t>(type),&value)<0)
  {
    throw std::runtime_error("Failure to set fill value for dataset!");
  }
}

template<typename T>
T DatasetCreationList::fill_value(const datatype::Datatype &type) const
{
  T value;
  if(H5Pget_fill_value(static_cast<hid_t>(*this),static_cast<hid_t>(type),&value)<0)
  {
    throw std::runtime_error("Failure retrieving the fill value for a dataset!");
  }
  return value;
}

} // namespace property
} // namespace hdf5
