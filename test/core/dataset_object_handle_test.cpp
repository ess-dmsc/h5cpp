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
// Created on: Aug 07, 2017
//

#include "object_handle_test.hpp"

DatasetObjectHandleTest::DatasetObjectHandleTest(const std::string &filename):
  ObjectHandleTest(hdf5::ObjectHandle::Type::Dataset),
  filename_(filename),
  environment_(filename_),
  dtype_(H5Tcopy(H5T_NATIVE_DOUBLE)),
  dspace_(H5Screate(H5S_SCALAR))
{
  H5Dcreate(static_cast<hid_t>(environment_.file_handle()),"test",
	    static_cast<hid_t>(dtype_),
	    static_cast<hid_t>(dspace_),
	    hdf5::property::kDefault,hdf5::property::kDefault,hdf5::property::kDefault);
}

DatasetObjectHandleTest::~DatasetObjectHandleTest()
{

}

hid_t DatasetObjectHandleTest::create_object()
{
  return H5Dopen(static_cast<hid_t>(environment_.file_handle()),"test",hdf5::property::kDefault);
}



