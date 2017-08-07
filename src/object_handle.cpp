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

namespace hdf5
{

//=================constrcutors and destructors============================
ObjectHandle::ObjectHandle(hid_t &&id) :handle_(id)
{
  if(handle()<0)
  {
    //TODO: error handling
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
    //TODO: error handling
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

//-------------------------------------------------------------------------
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
      default:
        error_code = H5Oclose(handle());

        //TODO: have to check here how to deal with all other types!!!
    }

    if(error_code<0)
    {
      //TODO: error handling
    }
  }

  //in any case we have to reset the ID of the obejct
  handle_ = 0; 
}

//----------------------------------------------------------------------------
ObjectHandle::Type ObjectHandle::get_type() const
{
  H5I_type_t type = H5Iget_type(handle_);
  
  switch(type)
  {
    case H5I_UNINIT: return ObjectHandle::Type::UNINITIALIZED;	
    case H5I_BADID:  return ObjectHandle::Type::BADOBJECT;
    case H5I_FILE: 	return ObjectHandle::Type::FILE;
    case H5I_GROUP: return ObjectHandle::Type::GROUP;
    case H5I_DATATYPE: return ObjectHandle::Type::DATATYPE;
    case H5I_DATASPACE: return ObjectHandle::Type::DATASPACE;
    case H5I_DATASET: return ObjectHandle::Type::DATASET;
    case H5I_ATTR: return ObjectHandle::Type::ATTRIBUTE;
    case H5I_REFERENCE: return ObjectHandle::Type::REFERENCE;
    case H5I_VFL: return ObjectHandle::Type::VIRTUAL_FILE_LAYER;
    case H5I_GENPROP_CLS: return ObjectHandle::Type::PROPERTY_LIST_CLASS;
    case H5I_GENPROP_LST: return ObjectHandle::Type::PROPERTY_LIST;
    case H5I_ERROR_CLASS: return ObjectHandle::Type::ERROR_CLASS;
    case H5I_ERROR_MSG: return ObjectHandle::Type::ERROR_MESSAGE;
    case H5I_ERROR_STACK: return ObjectHandle::Type::ERROR_STACK;
                          //TODO: error handling
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

  }
}


//----------------------------------------------------------------------------
void ObjectHandle::decrement_reference_count() const
{
  if(H5Idec_ref(handle_)<0)
  {
    //TODO: error handling
  }
}

//----------------------------------------------------------------------------
int ObjectHandle::get_reference_count() const
{
  int ref_cnt = H5Iget_ref(handle_);
  if(ref_cnt<0)
  {
    //TODO: error handling
  }

  return ref_cnt;
}

//-------------------------------------------------------------------------
const hid_t &ObjectHandle::handle() const noexcept 
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



} // namespace hdf5
