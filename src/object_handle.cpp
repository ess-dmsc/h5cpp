//
// (c) Copyright 2017 DESY, ESS
//
// This file is part of h5cpp.
//
// h5cpp is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// h5cpp is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with h5cpp.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Aug 07, 2017
//

#include "object_handle.hpp"
#include <sstream>
#include <stdexcept>

namespace hdf5
{

//=================constrcutors and destructors============================
ObjectHandle::ObjectHandle(hid_t &&id) :handle_(id)
{
  if(handle()<0)
  {
    std::stringstream ss;
    ss<<"Invalid object handler ("<<id<<")";
    throw std::runtime_error(ss.str());
  }
}
    
//-------------------------------------------------------------------------
ObjectHandle::ObjectHandle() noexcept :handle_(0) { }

//-------------------------------------------------------------------------
ObjectHandle::ObjectHandle(const ObjectHandle &o) 
    :handle_(o.handle_)
{
  //need to increment the reference 
  //counter for this object as we do copy construction
  if(is_valid()) increment_reference_count();
}

//-------------------------------------------------------------------------
ObjectHandle::ObjectHandle(ObjectHandle &&o) noexcept
    :handle_(o.handle_) 
{
  o.handle_ = 0;
  //since the id is removed from the original object we do not
  //have to care about the reference counter
}
    
//-------------------------------------------------------------------------
ObjectHandle::~ObjectHandle()
{
  close();
}   


//================assignment operators=====================================
//implementation of the copy assignment operator
ObjectHandle &ObjectHandle::operator=(const ObjectHandle &o)
{
  if(this == &o) return *this;

  close(); //close the current object
  handle_ = o.handle_;

  //if the original object is valid we have to increment 
  //the reference counter for this id
  if(is_valid()) increment_reference_count();

  return *this;
}

//-------------------------------------------------------------------------
//implementation of the move assignment operator
ObjectHandle &ObjectHandle::operator=(ObjectHandle &&o) noexcept
{
  if(this == &o) return *this;

  close(); //need to close the original object here 
  handle_ = o.handle_;
  o.handle_ = 0;

  //As this is a move operation we do not need to care
  //about the IDs reference. 

  return *this;
}
   
//=============basic manipulation methods==================================
bool ObjectHandle::is_valid() const 
{
  if(handle()==0) return false;

  htri_t value = H5Iis_valid(handle());
  
  if(value < 0)
  {
    std::stringstream ss;
    ss<<"Could not retrieve validity status for handle ("<<handle()<<")";
    throw std::runtime_error(ss.str());
  }

  if(value)
  {
      return true;
  }
  else 
  {
      return false;
  }
}

//----------------------------------------------------------------------------
void ObjectHandle::close() 
{
  //if the ID is valid this will decrement the reference counter or close
  //the object if the counter becomes 0.

  if(is_valid())
  {
    herr_t error_code = 0;

    switch(get_type())
    {
      case ObjectHandle::Type::DATASPACE: 
        error_code = H5Sclose(handle());
        break;
      case ObjectHandle::Type::ATTRIBUTE:
        error_code = H5Aclose(handle());
        break;
      case ObjectHandle::Type::FILE:
        error_code = H5Fclose(handle());
        break;
      case ObjectHandle::Type::PROPERTY_LIST:
        error_code = H5Pclose(handle());
        break;
      case ObjectHandle::Type::ERROR_MESSAGE:
        error_code = H5Eclose_msg(handle());
        break;
      case ObjectHandle::Type::ERROR_STACK:
        error_code = H5Eclose_stack(handle());
        break;
      case ObjectHandle::Type::ERROR_CLASS:
        error_code = H5Eunregister_class(handle());
        break;
      default:
        error_code = H5Oclose(handle());
    }

    if(error_code<0)
    {
      //TODO: maybe we should add here an entry to the error stack
      std::stringstream ss;
      ss<<"Could not close object of type "<<get_type()<<"with handle "
        <<"("<<handle()<<")!";
      throw std::runtime_error(ss.str());
    }
  }

  //in any case we have to reset the ID of the obejct
  handle_ = 0; 
}

//-----------------------------------------------------------------------------
ObjectHandle::Type ObjectHandle::get_type() const
{
  H5I_type_t type = H5Iget_type(handle_);
  
  switch(type)
  {
    case H5I_UNINIT: 
      return ObjectHandle::Type::UNINITIALIZED;	
    case H5I_BADID:  
      return ObjectHandle::Type::BADOBJECT;
    case H5I_FILE: 	
      return ObjectHandle::Type::FILE;
    case H5I_GROUP: 
      return ObjectHandle::Type::GROUP;
    case H5I_DATATYPE: 
      return ObjectHandle::Type::DATATYPE;
    case H5I_DATASPACE: 
      return ObjectHandle::Type::DATASPACE;
    case H5I_DATASET: 
      return ObjectHandle::Type::DATASET;
    case H5I_ATTR: 
      return ObjectHandle::Type::ATTRIBUTE;
    case H5I_REFERENCE: 
      return ObjectHandle::Type::REFERENCE;
    case H5I_VFL: 
      return ObjectHandle::Type::VIRTUAL_FILE_LAYER;
    case H5I_GENPROP_CLS: 
      return ObjectHandle::Type::PROPERTY_LIST_CLASS;
    case H5I_GENPROP_LST: 
      return ObjectHandle::Type::PROPERTY_LIST;
    case H5I_ERROR_CLASS: 
      return ObjectHandle::Type::ERROR_CLASS;
    case H5I_ERROR_MSG: 
      return ObjectHandle::Type::ERROR_MESSAGE;
    case H5I_ERROR_STACK: 
      return ObjectHandle::Type::ERROR_STACK;
    default:
      std::stringstream ss;
      ss<<"Unkown object type ("<<type<<")";
      throw std::runtime_error(ss.str());
  };
}

//----------------------------------------------------------------------------
void ObjectHandle::increment_reference_count() const
{
  if(H5Iinc_ref(handle_)<0)
  {
    //TODO error handling
    
    //Failing to succesfully inrement the reference counter for an internal
    //object ID is a serious issue and justifies to throw an exception here.
    throw std::runtime_error("Error incrementing the reference counter!");

  }
}


//----------------------------------------------------------------------------
void ObjectHandle::decrement_reference_count() const
{
  if(H5Idec_ref(handle_)<0)
  {
    //TODO: maybe we should add an entry here on the error stack
    throw std::runtime_error("Could not decrement the reference counter");
  }
}

//----------------------------------------------------------------------------
int ObjectHandle::get_reference_count() const
{
  int ref_cnt = H5Iget_ref(handle_);
  if(ref_cnt<0)
  {
    //TODO: maybe we should add here an entry to the error stack.
    throw std::runtime_error("Could not retrieve reference count for object!");
  }

  return ref_cnt;
}

//-------------------------------------------------------------------------
hid_t ObjectHandle::handle() const noexcept
{ 
  return handle_; 
}

//=============comparison operators========================================
//implementation of equality check
bool operator==(const ObjectHandle &lhs,const ObjectHandle &rhs)
{
  //if one of the object is not valid they are considered as in not-equal
  if((!rhs.is_valid()) || (!lhs.is_valid())) return false;
  
  return lhs.handle()==rhs.handle();
}

//-------------------------------------------------------------------------
//implementation of inequality check
bool operator!=(const ObjectHandle &a,const ObjectHandle &b)
{
    if(a == b) 
    {
      return false;
    }
    else
    {
      return true;
    }
}

//----------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &stream,const ObjectHandle::Type &type)
{
  switch(type)
  {
    case ObjectHandle::Type::UNINITIALIZED: stream<<"UNINITIALIZED"; break;
    case ObjectHandle::Type::BADOBJECT: stream<<"BADOBJECT"; break;
    case ObjectHandle::Type::FILE: stream<<"FILE"; break;
    case ObjectHandle::Type::GROUP: stream<<"GROUP"; break;
    case ObjectHandle::Type::DATATYPE: stream<<"DATATYPE"; break;
    case ObjectHandle::Type::DATASPACE: stream<<"DATASPACE"; break;
    case ObjectHandle::Type::DATASET: stream<<"DATASET"; break;
    case ObjectHandle::Type::ATTRIBUTE: stream<<"ATTRIBUTE"; break;
    case ObjectHandle::Type::PROPERTY_LIST: stream<<"PROPERTY_LIST"; break;
    case ObjectHandle::Type::REFERENCE: stream<<"REFERENCE"; break;
    case ObjectHandle::Type::VIRTUAL_FILE_LAYER: stream<<"VIRTUAL_FILE_LAYER"; break;
    case ObjectHandle::Type::PROPERTY_LIST_CLASS: stream<<"PROPERTY_LIST_CLASS"; break;
    case ObjectHandle::Type::ERROR_CLASS: stream<<"ERROR_CLASS"; break;
    case ObjectHandle::Type::ERROR_MESSAGE: stream<<"ERROR_MESSAGE"; break;
    case ObjectHandle::Type::ERROR_STACK: stream<<"ERROR_STACK"; break;
    default:
                                            stream<<"unknown";
  };

  return stream;
}

std::istream &operator>>(std::istream &stream,ObjectHandle::Type &type)
{
  std::string buffer;

  //TODO: maybe we should add here a to-upper conversion to allow mixed case strings
  stream>>buffer;

  if(buffer == "FILE")
    type = ObjectHandle::Type::FILE;
  else if(buffer == "GROUP")
    type = ObjectHandle::Type::GROUP;
  else if(buffer == "DATATYPE")
    type = ObjectHandle::Type::DATATYPE;
  else if(buffer == "DATASPACE")
    type = ObjectHandle::Type::DATASPACE;
  else if(buffer == "DATASET")
    type = ObjectHandle::Type::DATASET;
  else if(buffer == "ATTRIBUTE")
    type = ObjectHandle::Type::ATTRIBUTE;
  else if(buffer == "PROPERTY_LIST")
    type = ObjectHandle::Type::PROPERTY_LIST;
  else if(buffer == "REFERENCE")
    type = ObjectHandle::Type::REFERENCE;
  else if(buffer == "PROPERTY_LIST_CLASS")
    type = ObjectHandle::Type::PROPERTY_LIST_CLASS;
  else if(buffer == "ERROR_CLASS")
    type = ObjectHandle::Type::ERROR_CLASS;
  else if(buffer == "ERROR_MESSAGE")
    type = ObjectHandle::Type::ERROR_MESSAGE;
  else if(buffer == "ERROR_STACK")
    type = ObjectHandle::Type::ERROR_STACK;
  else
    type = ObjectHandle::Type::BADOBJECT;

  return stream;


}

} // namespace hdf5
