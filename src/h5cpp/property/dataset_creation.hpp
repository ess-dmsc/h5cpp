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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 21, 2017
//
#pragma once

#include <iostream>
#include <h5cpp/property/object_creation.hpp>
#include <h5cpp/core/types.hpp>
#include <h5cpp/datatype/datatype.hpp>
#include <h5cpp/datatype/type_trait.hpp>
#include <h5cpp/core/windows.hpp>
#include <h5cpp/error/error.hpp>

namespace hdf5 {
namespace property {

//!
//! \brief enumeration for the fill value status
//!
enum class DatasetFillValueStatus : std::underlying_type<H5D_fill_value_t>::type {
  Undefined = H5D_FILL_VALUE_UNDEFINED,
  Default = H5D_FILL_VALUE_DEFAULT,
  UserDefined = H5D_FILL_VALUE_USER_DEFINED
};

DLL_EXPORT std::ostream &operator<<(std::ostream &stream, const DatasetFillValueStatus &status);

//!
//! \brief enumeration for the fill time of a dataset
//!
enum class DatasetFillTime : std::underlying_type<H5D_fill_time_t>::type {
  IfSet = H5D_FILL_TIME_IFSET,
  Alloc = H5D_FILL_TIME_ALLOC,
  Never = H5D_FILL_TIME_NEVER
};

DLL_EXPORT std::ostream &operator<<(std::ostream &stream, const DatasetFillTime &time);

//!
//! \brief enumeration for the dataset allocation time
//!
//! The particular allocation strategy depends on the layout of the dataset.
//!
//! \sa DatasetLayout
//!
enum class DatasetAllocTime : std::underlying_type<H5D_alloc_time_t>::type {
  //!
  //! \brief choose the default allocation strategy for the particular layout
  //!
      Default = H5D_ALLOC_TIME_DEFAULT,

  //!
  //! \brief all space is allocated when the dataset is created
  //!
      Early = H5D_ALLOC_TIME_EARLY,

  //!
  //! \brief space is allocated as data is written to the file
  //!
      Incr = H5D_ALLOC_TIME_INCR,

  //!
  //! \brief all space is allocated at the first write to the dataset
  //!
      Late = H5D_ALLOC_TIME_LATE
};

DLL_EXPORT std::ostream &operator<<(std::ostream &stream, const DatasetAllocTime &time);

//!
//! \brief enumeration describing the layout of a dataset
//!
enum class DatasetLayout : std::underlying_type<H5D_layout_t>::type {
  Compact = H5D_COMPACT,
  Contiguous = H5D_CONTIGUOUS,
  Chunked = H5D_CHUNKED,
#if (defined(_DOXYGEN_) || H5_VERSION_GE(1,10,0))
  //! (*since hdf5 1.10.0*)
  Virtual = H5D_VIRTUAL
#endif
};

DLL_EXPORT std::ostream &operator<<(std::ostream &stream, const DatasetLayout &layout);

//!
//! \brief dataset creation property list
//!
class DLL_EXPORT DatasetCreationList : public ObjectCreationList {
 public:
  //!
  //! \brief default constructor
  //!
  DatasetCreationList();
  DatasetCreationList(const DatasetCreationList &) = default;

  //!
  //! \brief destructor
  //!
  ~DatasetCreationList() override;

  //!
  //! \brief constructor
  //!
  //! Construct a new dataset creation property list from an HDF5 handle.
  //! This constructor will throw an exception if the handle does not
  //! reference a dataset creation property list.
  //!
  //! \throws std::runtime_error in case of a failure
  //! \param handle r-value reference to an HDF5 handle
  //!
  explicit DatasetCreationList(ObjectHandle &&handle);

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
  //! - \c T is a native type already implemented in the library
  //! - the user has provided an appropriate type trait to construct an HDF5
  //!       datatype for \c T
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
                  const datatype::Datatype &type = datatype::TypeTrait<T>::create()) const;

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
  T fill_value(const datatype::Datatype &type = datatype::TypeTrait<T>::create()) const;

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

  //!
  //! \brief get a number of filters
  //!
  unsigned int nfilters() const;
};

template<typename T>
void DatasetCreationList::fill_value(const T &value, const datatype::Datatype &type) const {
  if (H5Pset_fill_value(static_cast<hid_t>(*this),
                        static_cast<hid_t>(type), &value) < 0) {
    error::Singleton::instance().throw_with_stack("Failure to set fill value for dataset!");
  }
}

template<typename T>
T DatasetCreationList::fill_value(const datatype::Datatype &type) const {
  T value;
  if (H5Pget_fill_value(static_cast<hid_t>(*this), static_cast<hid_t>(type), &value) < 0) {
    error::Singleton::instance().throw_with_stack("Failure retrieving the fill value for a dataset!");
  }
  return value;
}

} // namespace property
} // namespace hdf5
