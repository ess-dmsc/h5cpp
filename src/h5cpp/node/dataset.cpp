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
//   Jan Kotanski <jan.kotanski@desy.de>
//
// Created on: Sep 12, 2017
//

#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <h5cpp/node/dataset.hpp>
#include <h5cpp/node/functions.hpp>
#include <h5cpp/filter/external_filter.hpp>
#include <h5cpp/error/error.hpp>
#include <h5cpp/contrib/stl/string.hpp>
#include <h5cpp/core/utilities.hpp>

namespace hdf5 {
namespace node {

//=============================================================================
// implementation of private member functions
//=============================================================================


Node Dataset::create_dataset(const Group &base,
                             const Path &path,
                             const datatype::Datatype &type,
                             const dataspace::Dataspace &space,
                             const property::LinkCreationList &lcpl,
                             const property::DatasetCreationList &dcpl,
                             const property::DatasetAccessList &dapl)
{

  hid_t id = 0;

  if((id = H5Dcreate(static_cast<hid_t>(base),
                     static_cast<std::string>(path).c_str(),
                     static_cast<hid_t>(type),
                     static_cast<hid_t>(space),
                     static_cast<hid_t>(lcpl),
                     static_cast<hid_t>(dcpl),
                     static_cast<hid_t>(dapl))) < 0 )
  {
    std::stringstream ss;
    ss<<"Failure to create dataset ["<<path<<"] on group ["<<base.link().path()
      <<"]!";
    hdf5::error::Singleton::instance().throw_with_stack(ss.str());
  }
  H5Dclose(id);

  return Node(node::get_node(base,path));
}

//=============================================================================
// implementation of public member functions
//=============================================================================
Dataset::Dataset(const Node &node):
    Node(node)
{
  if(node.type()!=Type::Dataset)
  {
    std::stringstream ss;
    ss<<"Construction of a Dataset from a Node failed since ";
    ss<<"Node ["<<node.link().path()<<"] is not a dataset!";
    throw std::runtime_error(ss.str());
  }
  file_type_ = datatype();
  file_type_class = file_type_.get_class();
}

Dataset::Dataset(const Group &base,const Path &path,
                 const datatype::Datatype &type,
                 const dataspace::Dataspace &space,
                 const property::LinkCreationList &lcpl,
                 const property::DatasetCreationList &dcpl,
                 const property::DatasetAccessList &dapl):
  Node(create_dataset(base,path,type,space,lcpl,dcpl,dapl))
  {
  file_type_ = datatype();
  file_type_class = file_type_.get_class();
}


dataspace::Dataspace Dataset::dataspace() const
{
  hid_t id = H5Dget_space(static_cast<hid_t>(*this));
  if(id<0)
  {
    std::stringstream ss;
    ss<<"Failure retrieving dataspace for dataset "<<link().path()<<"!";
    hdf5::error::Singleton::instance().throw_with_stack(ss.str());
  }
  return dataspace::Dataspace(ObjectHandle(id));
}

datatype::Datatype Dataset::datatype() const
{
  hid_t id = H5Dget_type(static_cast<hid_t>(*this));
  if(id<0)
  {
    std::stringstream ss;
    ss<<"Failure retrieving datatype for dataset "<<link().path()<<"!";
    hdf5::error::Singleton::instance().throw_with_stack(ss.str());
  }
  return datatype::Datatype(ObjectHandle(id));
}

property::DatasetCreationList Dataset::creation_list() const
{
  hid_t id = 0;
  if((id=H5Dget_create_plist(static_cast<hid_t>(*this)))<0)
  {
    std::stringstream ss;
    ss<<"Cannot obtain dataset creation property list for dataset ["
      <<link().path()<<"]!";
    hdf5::error::Singleton::instance().throw_with_stack(ss.str());
  }

  return property::DatasetCreationList(ObjectHandle(id));
}

property::DatasetAccessList Dataset::access_list() const
{
  hid_t id=0;
  if((id=H5Dget_access_plist(static_cast<hid_t>(*this)))<0)
  {
    std::stringstream ss;
    ss<<"Failure obtaining dataset creation property list for dataset ["
      <<link().path()<<"]!";
    hdf5::error::Singleton::instance().throw_with_stack(ss.str());
  }

  return property::DatasetAccessList(ObjectHandle(id));
}

void Dataset::extent(const Dimensions &dims) const
{
  resize(dims);
}

void Dataset::resize(const Dimensions &dims) const
{
  if(H5Dset_extent(static_cast<hid_t>(*this),dims.data())<0)
  {
    std::stringstream ss;
    ss<<"Failed to set extent for dataset "<<link().path()<<"!";
    hdf5::error::Singleton::instance().throw_with_stack(ss.str());
  }
}

void Dataset::extent(size_t dim,ssize_t delta_elements) const
{
  resize_by(*this,dim,delta_elements);
}

#if H5_VERSION_GE(1,10,0)
void Dataset::refresh() const
{
  if(H5Drefresh(static_cast<hid_t>(*this))<0)
  {
    std::stringstream ss;
    ss<<"Failure to refresh dataset ["<<link().path()<<"]!";
    hdf5::error::Singleton::instance().throw_with_stack(ss.str());
  }
}

#endif


#if H5_VERSION_GE(1,10,2)

unsigned long long Dataset::chunk_storage_size(
			 std::vector<unsigned long long> offset) const
{
  unsigned long long storage_size;
  if(H5Dget_chunk_storage_size(static_cast<hid_t>(*this),
			       offset.data(),
			       &storage_size)<0)
    {
      std::stringstream ss;
      ss<<"Failure to read chunk data size from dataset ["<<link().path()<<"]!";
      error::Singleton::instance().throw_with_stack(ss.str());
    }
  return storage_size;
}

#endif

void Dataset::write(const char *data,const property::DatasetTransferList &dtpl)
{
  write(std::string(data),dtpl);
}

void Dataset::write(const char *data,const property::DatasetTransferList &dtpl) const
{
  write(std::string(data),dtpl);
}

filter::ExternalFilters Dataset::filters() const
{
  filter::ExternalFilters efilters = filter::ExternalFilters();
  efilters.fill(creation_list());
  return efilters;
}

void resize_by(const Dataset &dataset,size_t dimension_index,ssize_t delta)
{
  dataspace::Dataspace space = dataset.dataspace();
  if(space.type()!=dataspace::Type::Simple)
  {
    std::stringstream ss;
    ss<<"Dataset ["<<dataset.link().path()<<"] does not use a simple dataspace"
      <<" and thus cannot be extended!";
    throw std::runtime_error(ss.str());
  }
  dataspace::Simple simple_space(space);

  Dimensions current_dims = simple_space.current_dimensions();
  //check current dimensions
  if(dimension_index>=current_dims.size())
  {
    std::stringstream ss;
    ss<<"Dataset ["<<dataset.link().path()<<"] has rank "<<current_dims.size()
      <<" however you requested to change dimension "<<dimension_index
      <<" this would not work!";
    throw std::runtime_error(ss.str());
  }

  if((delta<0) && (current_dims[dimension_index] < static_cast<hsize_t>(std::abs(delta))))
  {
    std::stringstream ss;
    ss<<"Extent of dataset ["<<dataset.link().path()<<"] cannot be changed "
      <<" by "<<delta<<" along dimensions "<<dimension_index
      <<" (currently "<<current_dims[dimension_index]<<") as the resulting size"
      <<" would be negative";
    throw std::runtime_error(ss.str());
  }
  if (delta < 0)
    current_dims[dimension_index] -= signed2unsigned<unsigned long long>(-delta);
  else
    current_dims[dimension_index] += signed2unsigned<unsigned long long>(delta);
  dataset.resize(current_dims);
}

} // namespace node
} // namespace hdf5
