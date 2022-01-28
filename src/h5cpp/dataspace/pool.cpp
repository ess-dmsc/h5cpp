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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 24, 2017
//
#include <h5cpp/dataspace/simple.hpp>
#include <h5cpp/error/error.hpp>
#include <h5cpp/dataspace/pool.hpp>

namespace hdf5 {
namespace dataspace {

const Simple & DataspacePool::getSimple(size_t size)
{
  auto key = hdf5::Dimensions{size, size};
  if(pool_map.count(key) < 1)
    pool_map[key] = Simple(hdf5::Dimensions{size}, hdf5::Dimensions{size});
  return pool_map[key];
}

const Simple & DataspacePool::getSimple(const Dimensions &current,
                                                  const Dimensions &maximum)
{
  auto maxdim = hdf5::Dimensions(maximum);
  if (maximum.empty())
    maxdim = current;
  else if(current.size() != maxdim.size())
    error::Singleton::instance().throw_with_stack("The current dimensions size is different than the maximum dimensions size");

  auto key = hdf5::Dimensions(current);
  key.insert(key.end(), maxdim.begin(), maxdim.end());

  if(pool_map.count(key) < 1)
    pool_map[key] = Simple(current, maxdim);
  return pool_map[key];
}

} // namespace dataspace
} // namespace hdf5
