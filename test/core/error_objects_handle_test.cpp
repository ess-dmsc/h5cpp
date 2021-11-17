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
// Created on: Aug 07, 2017
//

#include "object_handle_test.hpp"

ErrorMessageObjectHandleTest::ErrorMessageObjectHandleTest():
  ObjectHandleTest(hdf5::ObjectHandle::Type::ErrorMessage)
{

}

hid_t ErrorMessageObjectHandleTest::create_object()
{
  hid_t cid = H5Eregister_class("TestError","h5cpp","1.0.0");
  return H5Ecreate_msg(cid ,H5E_MAJOR,"hello");
}

ErrorStackObjectHandleTest::ErrorStackObjectHandleTest():
  ObjectHandleTest(hdf5::ObjectHandle::Type::ErrorStack)
{

}

hid_t ErrorStackObjectHandleTest::create_object()
{
  return H5Ecreate_stack();
}

ErrorClassObjectHandleTest::ErrorClassObjectHandleTest():
  ObjectHandleTest(hdf5::ObjectHandle::Type::ErrorClass)
{

}

hid_t ErrorClassObjectHandleTest::create_object()
{
  return H5Eregister_class("TestError","h5cpp","1.0.0");
}




