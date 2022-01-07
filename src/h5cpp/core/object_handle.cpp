//
// (c) Copyright 2017 DESY, ESS
//
// This file is part of h5cpp.
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
//
// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
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
// Created on: Aug 07, 2017
//

#include <h5cpp/core/object_handle.hpp>

#include <sstream>
#include <h5cpp/error/error.hpp>

namespace hdf5 {

//=================constructors and destructors============================
ObjectHandle::ObjectHandle(hid_t id, ObjectHandle::Policy policy)
    : handle_(id)
{
  if (handle_ < 0)
  {
    std::stringstream ss;
    ss << "ObjectHandle: constructor failed, invalid hid=" << id;
    error::Singleton::instance().throw_with_stack(ss.str());
  }

  //
  // if we do not care about the object we have to increment its reference count
  // in order to avoid getting it destroyed when the ID loses scope.
  //
  if (policy == Policy::WithoutWard)
    increment_reference_count();
}

//-------------------------------------------------------------------------
ObjectHandle::ObjectHandle() noexcept : handle_(0) {}

//-------------------------------------------------------------------------
ObjectHandle::ObjectHandle(const ObjectHandle &o)
    : handle_(o.handle_)
{
  //need to increment the reference
  //counter for this object as we do copy construction
  if (is_valid()) increment_reference_count();
}

//-------------------------------------------------------------------------
ObjectHandle::ObjectHandle(ObjectHandle &&o) noexcept
    : handle_(o.handle_)
{
  o.handle_ = 0;
  //since the id is removed from the original object we do not
  //have to care about the reference counter
}

//-------------------------------------------------------------------------
ObjectHandle::~ObjectHandle() noexcept
{
  try
  {
    if (is_valid())
      close();
  }
  catch (std::runtime_error &e)
  {
    // This should almost never happen, unless is_valid() threw
    std::cerr << "Failed ~ObjectHandle:\n" << hdf5::error::print_nested(e, 1);
  }
  catch (...)
  {
    // Pokemon clause
    // ensures noexcept behavior
  }
}

//================assignment operators=====================================
//implementation of the copy assignment operator
ObjectHandle &ObjectHandle::operator=(const ObjectHandle &o)
{
  if (this == &o) return *this;

  //close the current object
  try
  {
    if (is_valid())
      close();
  }
  catch (...)
  {
    std::stringstream ss;
    ss << "ObjectHandle: failed to close hid=" << handle_ << " while copying hid=" << o.handle_;
    std::throw_with_nested(std::runtime_error(ss.str()));
  }

  //if the original object is valid we have to increment
  //the reference counter for this id
  try
  {
    if (o.is_valid())
      o.increment_reference_count();
  }
  catch (...)
  {
    std::stringstream ss;
    ss << "ObjectHandle: failed to copy hid=" << o.handle_;
    std::throw_with_nested(std::runtime_error(ss.str()));
  }

  handle_ = o.handle_;

  return *this;
}

//-------------------------------------------------------------------------
//implementation of the move assignment operator
ObjectHandle &ObjectHandle::operator=(ObjectHandle &&o) noexcept
{
  if (this == &o) return *this;

  //need to close the original object here
  try
  {
    if (is_valid())
      close();
  }
  catch (...)
  {
    // Pokemon clause
    // to ensure noexcept behavior
  }

  handle_ = o.handle_;
  o.handle_ = 0;

  //As this is a move operation we do not need to care
  //about the IDs reference.

  return *this;
}

//=============basic manipulation methods==================================
bool ObjectHandle::is_valid() const
{
  if (handle_ == 0) return false;

  htri_t value = H5Iis_valid(handle_);

  if (value < 0)
  {
    std::stringstream ss;
    ss << "ObjectHandle: could not retrieve validity for hid=" << handle_;
    error::Singleton::instance().throw_with_stack(ss.str());
  }

  return (0 != value);
}

//----------------------------------------------------------------------------
void ObjectHandle::close()
{
  //if the ID is valid this will decrement the reference counter or close
  //the object if the counter becomes 0.

  ObjectHandle::Type oht{Type::Uninitialized};

  try
  {
    oht = get_type();
  }
  catch (...)
  {
    std::stringstream ss;
    ss << "ObjectHandle: could not close hid=" << handle_;
    std::throw_with_nested(std::runtime_error(ss.str()));
  }

  herr_t error_code = 0;
  switch (oht)
  {
    case ObjectHandle::Type::Dataspace:
      error_code = H5Sclose(handle_);
      break;
    case ObjectHandle::Type::Group:
      error_code = H5Gclose(handle_);
      break;
    case ObjectHandle::Type::Datatype:
      error_code = H5Tclose(handle_);
      break;
    case ObjectHandle::Type::Attribute:
      error_code = H5Aclose(handle_);
      break;
    case ObjectHandle::Type::File:
      error_code = H5Fclose(handle_);
      break;
    case ObjectHandle::Type::PropertyList:
      error_code = H5Pclose(handle_);
      break;
    case ObjectHandle::Type::PropertyListClass:
      error_code = H5Pclose_class(handle_);
      break;
    case ObjectHandle::Type::ErrorMessage:
      error_code = H5Eclose_msg(handle_);
      break;
    case ObjectHandle::Type::ErrorStack:
      error_code = H5Eclose_stack(handle_);
      break;
    case ObjectHandle::Type::ErrorClass:
      error_code = H5Eunregister_class(handle_);
      break;
    case ObjectHandle::Type::Dataset:
      error_code = H5Dclose(handle_);
      break;
    case ObjectHandle::Type::Uninitialized:
      error_code = H5Oclose(handle_);
      break;
    case ObjectHandle::Type::BadObject:
      error_code = H5Oclose(handle_);
      break;
    case ObjectHandle::Type::VirtualFileLayer:
      error_code = H5Oclose(handle_);
      break;
    default:
      error_code = H5Oclose(handle_);
  }

  if (error_code < 0)
  {
    std::stringstream ss;
    ss << "ObjectHandle: could not close hid= " << handle_ << " type=" << oht;
    error::Singleton::instance().throw_with_stack(ss.str());
  }

  //in any case we have to reset the ID of the obejct
  handle_ = 0;
}

//-----------------------------------------------------------------------------
ObjectHandle::Type ObjectHandle::get_type() const
{
  H5I_type_t type = H5Iget_type(handle_);

  switch (type)
  {
    case H5I_UNINIT:
      return ObjectHandle::Type::Uninitialized;
    case H5I_BADID:
      return ObjectHandle::Type::BadObject;
    case H5I_FILE:
      return ObjectHandle::Type::File;
    case H5I_GROUP:
      return ObjectHandle::Type::Group;
    case H5I_DATATYPE:
      return ObjectHandle::Type::Datatype;
    case H5I_DATASPACE:
      return ObjectHandle::Type::Dataspace;
    case H5I_DATASET:
      return ObjectHandle::Type::Dataset;
    case H5I_ATTR:
      return ObjectHandle::Type::Attribute;
    case H5I_VFL:
      return ObjectHandle::Type::VirtualFileLayer;
    case H5I_GENPROP_CLS:
      return ObjectHandle::Type::PropertyListClass;
    case H5I_GENPROP_LST:
      return ObjectHandle::Type::PropertyList;
    case H5I_ERROR_CLASS:
      return ObjectHandle::Type::ErrorClass;
    case H5I_ERROR_MSG:
      return ObjectHandle::Type::ErrorMessage;
    case H5I_ERROR_STACK:
      return ObjectHandle::Type::ErrorStack;
    default:
      std::stringstream ss;
      ss << "ObjectHandle: unknown object type=" << type;
      error::Singleton::instance().throw_with_stack(ss.str());
  };
  return {};
}

//----------------------------------------------------------------------------
void ObjectHandle::increment_reference_count() const
{
  if (H5Iinc_ref(handle_) < 0)
  {
    //Failing to succesfully increment the reference counter for an internal
    //object ID is a serious issue and justifies to throw an exception here.
    error::Singleton::instance().throw_with_stack("ObjectHandle: could not increment reference counter");
  }
}

//----------------------------------------------------------------------------
void ObjectHandle::decrement_reference_count() const
{
  if (H5Idec_ref(handle_) < 0)
  {
    error::Singleton::instance().throw_with_stack("ObjectHandle: could not decrement reference counter");
  }
}

//----------------------------------------------------------------------------
int ObjectHandle::get_reference_count() const
{
  int ref_cnt = H5Iget_ref(handle_);
  if (ref_cnt < 0)
  {
    error::Singleton::instance().throw_with_stack("ObjectHandle: could not get reference counter");
  }

  return ref_cnt;
}

//=============comparison operators========================================
//implementation of equality check
bool operator==(const ObjectHandle &lhs, const ObjectHandle &rhs)
{
  //if one of the object is not valid they are considered as in not-equal
  if ((!rhs.is_valid()) || (!lhs.is_valid())) return false;

  return static_cast<hid_t>(lhs) == static_cast<hid_t>(rhs);
}

//-------------------------------------------------------------------------
//implementation of inequality check
bool operator!=(const ObjectHandle &a, const ObjectHandle &b)
{
  if (a == b)
  {
    return false;
  } else
  {
    return true;
  }
}

//----------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &stream, const ObjectHandle::Type &type)
{
  switch (type)
  {
    case ObjectHandle::Type::Uninitialized:
      stream << "UNINITIALIZED";
      break;
    case ObjectHandle::Type::BadObject:
      stream << "BADOBJECT";
      break;
    case ObjectHandle::Type::File:
      stream << "FILE";
      break;
    case ObjectHandle::Type::Group:
      stream << "GROUP";
      break;
    case ObjectHandle::Type::Datatype:
      stream << "DATATYPE";
      break;
    case ObjectHandle::Type::Dataspace:
      stream << "DATASPACE";
      break;
    case ObjectHandle::Type::Dataset:
      stream << "DATASET";
      break;
    case ObjectHandle::Type::Attribute:
      stream << "ATTRIBUTE";
      break;
    case ObjectHandle::Type::PropertyList:
      stream << "PROPERTY_LIST";
      break;
    case ObjectHandle::Type::VirtualFileLayer:
      stream << "VIRTUAL_FILE_LAYER";
      break;
    case ObjectHandle::Type::PropertyListClass:
      stream << "PROPERTY_LIST_CLASS";
      break;
    case ObjectHandle::Type::ErrorClass:
      stream << "ERROR_CLASS";
      break;
    case ObjectHandle::Type::ErrorMessage:
      stream << "ERROR_MESSAGE";
      break;
    case ObjectHandle::Type::ErrorStack:
      stream << "ERROR_STACK";
      break;
    default:
      stream << "unknown";
  };

  return stream;
}

} // namespace hdf5
