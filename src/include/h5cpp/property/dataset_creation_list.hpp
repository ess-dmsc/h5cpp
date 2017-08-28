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
#include "object_creation_list.hpp"
#include "../types.hpp"
#include "../datatype/datatype.hpp"
#include "../datatype/type_trait.hpp"

namespace hdf5 {
namespace property {

enum class DatasetFillValueStatus : std::underlying_type<H5D_fill_value_t>::type
{
  UNDEFINED = H5D_FILL_VALUE_UNDEFINED,
  DEFAULT   = H5D_FILL_VALUE_DEFAULT,
  USER_DEFINED = H5D_FILL_VALUE_USER_DEFINED
};

std::ostream &operator<<(std::ostream &stream,const DatasetFillValueStatus &status);

enum class DatasetFillTime : std::underlying_type<H5D_fill_time_t>::type
{
  IFSET = H5D_FILL_TIME_IFSET,
  ALLOC = H5D_FILL_TIME_ALLOC,
  NEVER = H5D_FILL_TIME_NEVER
};

std::ostream &operator<<(std::ostream &stream,const DatasetFillTime &time);

enum class DatasetAllocTime : std::underlying_type<H5D_alloc_time_t>::type
{
  DEFAULT = H5D_ALLOC_TIME_DEFAULT,
  EARLY   = H5D_ALLOC_TIME_EARLY,
  INCR    = H5D_ALLOC_TIME_INCR,
  LATE    = H5D_ALLOC_TIME_LATE
};

std::ostream &operator<<(std::ostream &stream,const DatasetAllocTime &time);

enum class DatasetLayout : std::underlying_type<H5D_layout_t>::type
{
  COMPACT    = H5D_COMPACT,
  CONTIGUOUS = H5D_CONTIGUOUS,
  CHUNKED    = H5D_CHUNKED,
#if H5_VERSION_GE(1,10,0)
  VIRTUAL    = H5D_VIRTUAL
#endif
};

std::ostream &operator<<(std::ostream &stream,const DatasetLayout &layout);

class DatasetCreationList : public ObjectCreationList
{
  public:

    DatasetCreationList();
    ~DatasetCreationList();

    void layout(DatasetLayout layout) const;
    DatasetLayout layout() const;

    void chunk(const hdf5::Dimensions &chunk_dims) const;
    hdf5::Dimensions chunk() const;


    template<typename T>
    void fill_value(const T &value,
                    const datatype::Datatype &type=datatype::TypeTrait<T>::create()) const;
    template<typename T>
    T fill_value(const datatype::Datatype &type=datatype::TypeTrait<T>::create()) const;

    DatasetFillValueStatus fill_value_status() const;

    void fill_time(DatasetFillTime time) const;
    DatasetFillTime fill_time() const;

    void allocation_time(DatasetAllocTime time) const;
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
