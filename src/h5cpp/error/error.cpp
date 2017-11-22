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
#include <stdexcept>
#include <sstream>

extern "C"{
#include <cstdio>
#include <cstring>
}

#define bufsize 7000

namespace hdf5 {
namespace error {

void Singleton::clear_stack()
{
  herr_t ret = H5Eclear2(H5E_DEFAULT);
  if (0 > ret)
  {
    throw std::runtime_error("Could not toggle automatic error stack printing");
  }
}

void Singleton::auto_print(bool enable)
{
  herr_t ret = H5Eset_auto2(H5E_DEFAULT,
                            enable ? reinterpret_cast<H5E_auto2_t>(H5Eprint2) : NULL,
                            enable ? stderr : NULL);

  if (0 > ret)
  {
    throw std::runtime_error("Could not set automatic error printing");
  }

  auto_print_ = auto_print_enabled();
}

bool Singleton::auto_print() const
{
  return auto_print_;
}

bool Singleton::auto_print_enabled() const
{
  H5E_auto2_t func = NULL;
  herr_t ret = H5Eget_auto2(H5E_DEFAULT, &func, NULL);

  if (0 > ret)
  {
    throw std::runtime_error("Could not determine automatic error printing settings");
  }

  return (func != NULL);
}


std::string Singleton::print_stack()
{
  char* buf {NULL};
  size_t size {0};
  FILE *stream = open_memstream (&buf, &size);

  herr_t err = H5Eprint2(H5E_DEFAULT, stream);
  fflush(stream);
  fclose(stream);

  if (0 > err)
  {
    free(buf);
    throw std::runtime_error("Could not print error stack");
  }

  std::string ret(buf, size);
  free(buf);
  clear_stack();
  return ret;
}

void Singleton::throw_exception(const std::string& message)
{
  std::string m = message;
  if (!auto_print_)
    m += "\nHDF5 Stack trace:\n" + print_stack();
  throw std::runtime_error(m);
}


} // namespace file
} // namespace hdf5
