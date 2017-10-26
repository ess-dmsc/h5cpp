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
// Author: Martin Shetty <martin.shetty@esss.se>
// Created on: Oct 25, 2017
//

#include <h5cpp/error/error.hpp>

extern "C"{
#include <cstdio>
}

namespace hdf5 {
namespace error {

void clear_stack()
{
  herr_t ret = H5Eclear2(H5Eget_current_stack());
  if (0 > ret)
  {
    throw std::runtime_error("Could not toggle automatic error stack printing");
  }
}

void auto_print(bool enable)
{
  herr_t ret = H5Eset_auto(H5E_DEFAULT,
                           enable ? reinterpret_cast<H5E_auto2_t>(H5Eprint2) : NULL,
                           enable ? stderr : NULL);

  if (0 > ret)
  {
    throw std::runtime_error("Could not toggle automatic error stack printing");
  }
}


} // namespace file
} // namespace hdf5
