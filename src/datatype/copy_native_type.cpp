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
// Created on: Aug 23, 2017
//

#include <h5cpp/datatype/copy_native_type.hpp>

namespace hdf5 {
namespace datatype {

  COPY_NATIVE_TYPE_SPECIALIZATION(char,H5T_NATIVE_CHAR)
  COPY_NATIVE_TYPE_SPECIALIZATION(unsigned char,H5T_NATIVE_UCHAR)
  COPY_NATIVE_TYPE_SPECIALIZATION(signed char,H5T_NATIVE_SCHAR)
  COPY_NATIVE_TYPE_SPECIALIZATION(short,H5T_NATIVE_SHORT)
  COPY_NATIVE_TYPE_SPECIALIZATION(unsigned short,H5T_NATIVE_USHORT)
  COPY_NATIVE_TYPE_SPECIALIZATION(int,H5T_NATIVE_INT)
  COPY_NATIVE_TYPE_SPECIALIZATION(unsigned int,H5T_NATIVE_UINT)
  COPY_NATIVE_TYPE_SPECIALIZATION(long,H5T_NATIVE_LONG)
  COPY_NATIVE_TYPE_SPECIALIZATION(unsigned long,H5T_NATIVE_ULONG)
  COPY_NATIVE_TYPE_SPECIALIZATION(long long,H5T_NATIVE_LLONG)
  COPY_NATIVE_TYPE_SPECIALIZATION(unsigned long long,H5T_NATIVE_ULLONG)
  COPY_NATIVE_TYPE_SPECIALIZATION(float,H5T_NATIVE_FLOAT)
  COPY_NATIVE_TYPE_SPECIALIZATION(double,H5T_NATIVE_DOUBLE)
  COPY_NATIVE_TYPE_SPECIALIZATION(long double,H5T_NATIVE_LDOUBLE)

} // namespace datatype
} // namespace hdf5




