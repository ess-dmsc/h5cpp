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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Aug 25, 2017
//
#include <stdexcept>
#include <h5cpp/property/property_class.hpp>
#include <h5cpp/property/dataset_creation.hpp>
#include <h5cpp/core/types.hpp>

namespace hdf5 {
namespace property {

std::ostream &operator<<(std::ostream &stream,const DatasetFillValueStatus &status)
{
  switch(status)
  {
    case DatasetFillValueStatus::UNDEFINED:
      return stream<<"UNDEFINED";
    case DatasetFillValueStatus::DEFAULT:
      return stream<<"DEFAULT";
    case DatasetFillValueStatus::USER_DEFINED:
      return stream<<"USER_DEFINED";
  }
  return stream;
}

std::ostream &operator<<(std::ostream &stream,const DatasetFillTime &time)
{
  switch(time)
  {
    case DatasetFillTime::IFSET:
      return stream<<"IFSET";
    case DatasetFillTime::ALLOC:
      return stream<<"ALLOC";
    case DatasetFillTime::NEVER:
      return stream<<"NEVER";
  }
  return stream;
}

std::ostream &operator<<(std::ostream &stream,const DatasetAllocTime &time)
{
  switch(time)
  {
    case DatasetAllocTime::DEFAULT:
      return stream<<"DEFAULT";
    case DatasetAllocTime::EARLY:
      return stream<<"EARLY";
    case DatasetAllocTime::INCR:
      return stream<<"INCR";
    case DatasetAllocTime::LATE:
      return stream<<"LATE";
  }
  return stream;
}

std::ostream &operator<<(std::ostream &stream,const DatasetLayout &layout)
{
  switch(layout)
  {
    case DatasetLayout::COMPACT:
      return stream<<"COMPACT";
    case DatasetLayout::CONTIGUOUS:
      return stream<<"CONTIGUOUS";
    case DatasetLayout::CHUNKED:
      return stream<<"CHUNKED";
#if H5_VERSION_GE(1,10,0)
    case DatasetLayout::VIRTUAL:
      return stream<<"VIRTUAL";
#endif
  }
  return stream;
}


DatasetCreationList::DatasetCreationList():
    ObjectCreationList(kDatasetCreate)
{}

DatasetCreationList::~DatasetCreationList()
{}

void DatasetCreationList::layout(DatasetLayout layout) const
{
  if(H5Pset_layout(static_cast<hid_t>(*this),static_cast<H5D_layout_t>(layout))<0)
  {
    throw std::runtime_error("Failure setting the dataset layout!");
  }
}

DatasetLayout DatasetCreationList::layout() const
{
  switch(H5Pget_layout(static_cast<hid_t>(*this)))
  {
    case H5D_COMPACT:
      return DatasetLayout::COMPACT;
    case H5D_CONTIGUOUS:
      return DatasetLayout::CONTIGUOUS;
    case H5D_CHUNKED:
      return DatasetLayout::CHUNKED;
#if H5_VERSION_GE(1,10,0)
    case H5D_VIRTUAL:
      return DatasetLayout::VIRTUAL;
#endif
    default:
      throw std::runtime_error("Failure retrieving the dataset layout!");
  }
}

void DatasetCreationList::chunk(const Dimensions &chunk_dims) const
{
  if(H5Pset_chunk(static_cast<hid_t>(*this),chunk_dims.size(),chunk_dims.data())<0)
  {
    throw std::runtime_error("Failure setting chunk dimensions!");
  }
}

Dimensions DatasetCreationList::chunk() const
{
  int s = H5Pget_chunk(static_cast<hid_t>(*this),0,NULL);
  if(s<0)
  {
    throw std::runtime_error("Failure retrieving the chunk rank!");
  }

  Dimensions buffer(s);
  if(H5Pget_chunk(static_cast<hid_t>(*this),s,buffer.data())<0)
  {
    throw std::runtime_error("Failure retrieving the chunk dimension!");
  }

  return buffer;
}

DatasetFillValueStatus DatasetCreationList::fill_value_status() const
{
  H5D_fill_value_t status;
  if(H5Pfill_value_defined(static_cast<hid_t>(*this),&status)<0)
  {
    throw std::runtime_error("Failure obtaining the fill value status!");
  }
  return static_cast<DatasetFillValueStatus>(status);
}

void DatasetCreationList::fill_time(DatasetFillTime time) const
{
  if(H5Pset_fill_time(static_cast<hid_t>(*this),
                      static_cast<H5D_fill_time_t>(time))<0)
  {
    throw std::runtime_error("Failure setting the fill time for the dataset!");
  }
}

DatasetFillTime DatasetCreationList::fill_time() const
{
  H5D_fill_time_t buffer;
  if(H5Pget_fill_time(static_cast<hid_t>(*this),&buffer)<0)
  {
    throw std::runtime_error("Failure retrieving dataset fill time!");
  }
  return static_cast<DatasetFillTime>(buffer);
}

void DatasetCreationList::allocation_time(DatasetAllocTime time) const
{
  if(H5Pset_alloc_time(static_cast<hid_t>(*this),
                       static_cast<H5D_alloc_time_t>(time))<0)
  {
    throw std::runtime_error("Failure setting dataset allocation time!");
  }
}

DatasetAllocTime DatasetCreationList::allocation_time() const
{
  H5D_alloc_time_t buffer;
  if(H5Pget_alloc_time(static_cast<hid_t>(*this),&buffer)<0)
  {
    throw std::runtime_error("Failure retrieving dataset allocation time!");
  }
  return static_cast<DatasetAllocTime>(buffer);
}

} // namespace property
} // namespace hdf5
