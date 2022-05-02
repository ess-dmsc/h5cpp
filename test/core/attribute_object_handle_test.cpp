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


AttributeObjectHandleTest::AttributeObjectHandleTest(const std::string &fname):
  ObjectHandleTest(hdf5::ObjectHandle::Type::Attribute),
  filename_(fname),
  environment_(filename_),
  group_(H5Gcreate(static_cast<hid_t>(environment_.file_handle()),"test",hdf5::property::kDefault,hdf5::property::kDefault,hdf5::property::kDefault))
{
  hdf5::ObjectHandle dtype(H5Tcopy(H5T_NATIVE_DOUBLE));
  hdf5::ObjectHandle dspace(H5Screate(H5S_SCALAR));

  H5Acreate(static_cast<hid_t>(group_),"test",
	    static_cast<hid_t>(dtype),
	    static_cast<hid_t>(dspace),
	    hdf5::property::kDefault,hdf5::property::kDefault);
}

AttributeObjectHandleTest::~AttributeObjectHandleTest()
{

}

hid_t AttributeObjectHandleTest::create_object()
{
  return H5Aopen(static_cast<hid_t>(group_),"test",hdf5::property::kDefault);
}
