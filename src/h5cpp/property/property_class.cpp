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
// Created on: Aug 16, 2017
//

#include <h5cpp/property/property_class.hpp>
#include <h5cpp/error/error.hpp>

#include <iterator>
#include <cstring>


namespace hdf5{
namespace property{

Class::Class(ObjectHandle &&handle):
    handle_(handle)
{}

std::string Class::name() const
{
  char *cptr = H5Pget_class_name(static_cast<hid_t>(handle_));
  if(!cptr)
  {
    return std::string();
  }

  std::string buffer(cptr,std::strlen(cptr));
  free((void*)cptr);
  return buffer;

}

bool operator==(const Class &lhs,const Class &rhs)
{
  htri_t result = H5Pequal(static_cast<hid_t>(lhs),static_cast<hid_t>(rhs));
  if(result>0)
    return true;
  else if(result==0)
    return false;
  else
    error::Singleton::instance().throw_with_stack("Could check equality of property list classes");

}

bool operator!=(const Class &lhs,const Class &rhs)
{
  htri_t result = H5Pequal(static_cast<hid_t>(lhs),static_cast<hid_t>(rhs));
  if(result>0)
    return false;
  else if(result==0)
    return true;
  else
    error::Singleton::instance().throw_with_stack("Could check inequality of property list classes");

}

const Class kAttributeCreate = Class(ObjectHandle(H5P_ATTRIBUTE_CREATE,
						  ObjectHandle::Policy::WITHOUT_WARD));
const Class kDatasetAccess = Class(ObjectHandle(H5P_DATASET_ACCESS,
						ObjectHandle::Policy::WITHOUT_WARD));
const Class kDatasetCreate = Class(ObjectHandle(H5P_DATASET_CREATE,
						ObjectHandle::Policy::WITHOUT_WARD));
const Class kDatasetXfer = Class(ObjectHandle(H5P_DATASET_XFER,
					      ObjectHandle::Policy::WITHOUT_WARD));
const Class kDatatypeAccess = Class(ObjectHandle(H5P_DATATYPE_ACCESS,
						 ObjectHandle::Policy::WITHOUT_WARD));
const Class kDatatypeCreate = Class(ObjectHandle(H5P_DATATYPE_CREATE,
						 ObjectHandle::Policy::WITHOUT_WARD));
const Class kFileAccess = Class(ObjectHandle(H5P_FILE_ACCESS,
					     ObjectHandle::Policy::WITHOUT_WARD));
const Class kFileCreate = Class(ObjectHandle(H5P_FILE_CREATE,
					     ObjectHandle::Policy::WITHOUT_WARD));
const Class kFileMount = Class(ObjectHandle(H5P_FILE_MOUNT,
					    ObjectHandle::Policy::WITHOUT_WARD));
const Class kGroupAccess = Class(ObjectHandle(H5P_GROUP_ACCESS,
					      ObjectHandle::Policy::WITHOUT_WARD));
const Class kGroupCreate = Class(ObjectHandle(H5P_GROUP_CREATE,
					      ObjectHandle::Policy::WITHOUT_WARD));
const Class kLinkAccess = Class(ObjectHandle(H5P_LINK_ACCESS,
					     ObjectHandle::Policy::WITHOUT_WARD));
const Class kLinkCreate = Class(ObjectHandle(H5P_LINK_CREATE,
					     ObjectHandle::Policy::WITHOUT_WARD));
const Class kObjectCopy = Class(ObjectHandle(H5P_OBJECT_COPY,
					     ObjectHandle::Policy::WITHOUT_WARD));
const Class kObjectCreate = Class(ObjectHandle(H5P_OBJECT_CREATE,
					       ObjectHandle::Policy::WITHOUT_WARD));
const Class kStringCreate= Class(ObjectHandle(H5P_STRING_CREATE,
					      ObjectHandle::Policy::WITHOUT_WARD));



} // namespace property_list
} // namespace hdf5



