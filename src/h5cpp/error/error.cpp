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
// Author: Martin Shetty <martin.shetty@esss.se>
// Created on: Oct 25, 2017
//

#include <h5cpp/error/error.hpp>
#include <sstream>

extern "C"{
#ifdef __clang__
#include <string.h>
#else
#include <cstring>
#endif
}

namespace hdf5 {
namespace error {

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

H5CError Singleton::extract_stack()
{
  std::list<Descriptor> ret;
  herr_t err = H5Ewalk2(H5E_DEFAULT, H5E_WALK_DOWNWARD,
                        reinterpret_cast<H5E_walk2_t>(to_list), &ret);

  if (0 > err)
  {
    throw std::runtime_error("Could not extract error stack");
  }
  clear_stack();

  return H5CError(ret);
}

void Singleton::throw_with_stack(const std::string& message)
{
  if (!auto_print_)
  {
    try
    {
      throw_stack();
    }
    catch(...)
    {
      std::throw_with_nested( std::runtime_error(message) );
    }
  }
  throw std::runtime_error(message);
}

std::string print_nested(const std::exception& exception, int level)
{
  std::stringstream ss;
  ss << std::string(level, ' ') << exception.what() << '\n';
  try
  {
    std::rethrow_if_nested(exception);
  }
  catch(const H5CError& s)
  {
    for (auto error : s.contents())
      ss << std::string(++level, ' ') << error << "\n";
  }
  catch(const std::exception& e)
  {
    ss << print_nested(e, level+1);
  }
  catch(...)
  {}
  return ss.str();
}

// Helper functions, private

void Singleton::throw_stack()
{
  auto stack = extract_stack();
  if (!stack.empty())
    throw stack;
}


void Singleton::clear_stack()
{
  herr_t ret = H5Eclear2(H5E_DEFAULT);
  if (0 > ret)
  {
    throw std::runtime_error("Could not clear HDF5 error stack");
  }
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

herr_t Singleton::to_list(unsigned n,
                          const H5E_error2_t *err_desc,
                          std::list<Descriptor> *list)
{
  (void)n;
  list->push_back(Descriptor(*err_desc));
  return 0;
}



} // namespace file
} // namespace hdf5
