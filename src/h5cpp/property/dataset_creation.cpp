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
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Aug 25, 2017
//
#include <h5cpp/property/property_class.hpp>
#include <h5cpp/property/dataset_creation.hpp>
#include <h5cpp/core/utilities.hpp>

namespace hdf5 {
namespace property {

std::ostream &operator<<(std::ostream &stream, const DatasetFillValueStatus &status) {
  switch (status) {
    case DatasetFillValueStatus::Undefined:return stream << "UNDEFINED";
    case DatasetFillValueStatus::Default:return stream << "DEFAULT";
    case DatasetFillValueStatus::UserDefined:return stream << "USER_DEFINED";
  }
  return stream;
}

std::ostream &operator<<(std::ostream &stream, const DatasetFillTime &time) {
  switch (time) {
    case DatasetFillTime::IfSet:return stream << "IFSET";
    case DatasetFillTime::Alloc:return stream << "ALLOC";
    case DatasetFillTime::Never:return stream << "NEVER";
  }
  return stream;
}

std::ostream &operator<<(std::ostream &stream, const DatasetAllocTime &time) {
  switch (time) {
    case DatasetAllocTime::Default:return stream << "DEFAULT";
    case DatasetAllocTime::Early:return stream << "EARLY";
    case DatasetAllocTime::Incr:return stream << "INCR";
    case DatasetAllocTime::Late:return stream << "LATE";
  }
  return stream;
}

std::ostream &operator<<(std::ostream &stream, const DatasetLayout &layout) {
  switch (layout) {
    case DatasetLayout::Compact:return stream << "COMPACT";
    case DatasetLayout::Contiguous:return stream << "CONTIGUOUS";
    case DatasetLayout::Chunked:return stream << "CHUNKED";
#if H5_VERSION_GE(1, 10, 0)
    case DatasetLayout::Virtual:return stream << "VIRTUAL";
#endif
  }
  return stream;
}

DatasetCreationList::DatasetCreationList() :
    ObjectCreationList(kDatasetCreate) {}

DatasetCreationList::~DatasetCreationList() {}

DatasetCreationList::DatasetCreationList(ObjectHandle &&handle) :
    ObjectCreationList(std::move(handle)) {
  if (get_class() != kDatasetCreate) {
    std::stringstream ss;
    ss << "Cannot create property::DatasetCreationList from " << get_class();
    throw std::runtime_error(ss.str());
  }
}

void DatasetCreationList::layout(DatasetLayout layout) const {
  if (H5Pset_layout(static_cast<hid_t>(*this), static_cast<H5D_layout_t>(layout)) < 0) {
    error::Singleton::instance().throw_with_stack("Failure setting the dataset layout!");
  }
}

DatasetLayout DatasetCreationList::layout() const {
  switch (H5Pget_layout(static_cast<hid_t>(*this))) {
    case H5D_COMPACT:return DatasetLayout::Compact;
    case H5D_CONTIGUOUS:return DatasetLayout::Contiguous;
    case H5D_CHUNKED:return DatasetLayout::Chunked;
#if H5_VERSION_GE(1, 10, 0)
    case H5D_VIRTUAL:return DatasetLayout::Virtual;
#endif
    default:error::Singleton::instance().throw_with_stack("Failure retrieving the dataset layout!");
  }
  return {};
}

void DatasetCreationList::chunk(const Dimensions &chunk_dims) const {
  if (H5Pset_chunk(static_cast<hid_t>(*this),
		   static_cast<int>(chunk_dims.size()),
		   chunk_dims.data()) < 0) {
    error::Singleton::instance().throw_with_stack("Failure setting chunk dimensions!");
  }
}

Dimensions DatasetCreationList::chunk() const {
  int s = H5Pget_chunk(static_cast<hid_t>(*this), 0, nullptr);
  if (s < 0) {
    error::Singleton::instance().throw_with_stack("Failure retrieving the chunk rank!");
  }

  Dimensions buffer(signed2unsigned<size_t>(s));
  if (H5Pget_chunk(static_cast<hid_t>(*this), s, buffer.data()) < 0) {
    error::Singleton::instance().throw_with_stack("Failure retrieving the chunk dimension!");
  }

  return buffer;
}

DatasetFillValueStatus DatasetCreationList::fill_value_status() const {
  H5D_fill_value_t status;
  if (H5Pfill_value_defined(static_cast<hid_t>(*this), &status) < 0) {
    error::Singleton::instance().throw_with_stack("Failure obtaining the fill value status!");
  }
  return static_cast<DatasetFillValueStatus>(status);
}

void DatasetCreationList::fill_time(DatasetFillTime time) const {
  if (H5Pset_fill_time(static_cast<hid_t>(*this),
                       static_cast<H5D_fill_time_t>(time)) < 0) {
    error::Singleton::instance().throw_with_stack("Failure setting the fill time for the dataset!");
  }
}

DatasetFillTime DatasetCreationList::fill_time() const {
  H5D_fill_time_t buffer;
  if (H5Pget_fill_time(static_cast<hid_t>(*this), &buffer) < 0) {
    error::Singleton::instance().throw_with_stack("Failure retrieving dataset fill time!");
  }
  return static_cast<DatasetFillTime>(buffer);
}

void DatasetCreationList::allocation_time(DatasetAllocTime time) const {
  if (H5Pset_alloc_time(static_cast<hid_t>(*this),
                        static_cast<H5D_alloc_time_t>(time)) < 0) {
    error::Singleton::instance().throw_with_stack("Failure setting dataset allocation time!");
  }
}

DatasetAllocTime DatasetCreationList::allocation_time() const {
  H5D_alloc_time_t buffer;
  if (H5Pget_alloc_time(static_cast<hid_t>(*this), &buffer) < 0) {
    error::Singleton::instance().throw_with_stack("Failure retrieving dataset allocation time!");
  }
  return static_cast<DatasetAllocTime>(buffer);
}

unsigned int DatasetCreationList::nfilters() const{
  int nfilters = H5Pget_nfilters(static_cast<hid_t>(*this));
  if(nfilters < 0)
  {
      std::stringstream ss;
      ss<<"Failure to read a number of filters from " << this->get_class();
      error::Singleton::instance().throw_with_stack(ss.str());
  }
  return static_cast<unsigned int>(nfilters);

}


} // namespace property
} // namespace hdf5
