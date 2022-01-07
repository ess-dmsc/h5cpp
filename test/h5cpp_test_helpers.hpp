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
// Author: Martin Shetty <martin.shetty@esss.se>
// Created on: May 5, 2018
//

#pragma  once

#include <h5cpp/core/object_handle.hpp>
#include <h5cpp/error/error.hpp>

#define INVALIDATE_HID(OBJ) hdf5::ObjectHandle(static_cast<hid_t>(OBJ)).close()

inline void provoke_h5_error()
{
  hdf5::ObjectHandle invalid_handle;
  H5Iget_ref(static_cast<hid_t>(invalid_handle));
}

inline void provoke_h5cpp_exception()
{
  hdf5::ObjectHandle invalid_handle;
  invalid_handle.get_reference_count();
}
