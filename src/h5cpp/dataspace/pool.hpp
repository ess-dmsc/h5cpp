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
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Nov 1, 2021
//
#pragma once

#include <map>

#include <h5cpp/dataspace/dataspace.hpp>
#include <h5cpp/dataspace/simple.hpp>
#include <h5cpp/core/types.hpp>

namespace hdf5 {
namespace dataspace {

//!
//! @brief data space object pool
//!
class DLL_EXPORT DataspacePool
{
  public:

  //!
  //! \brief pool of reference of Simple data spaces
  //!
  //! Returns data space reference for static data space object
  //!
  //! @param size dimension of 1D Simple Dataspace to get or create
  //! @return data space reference for data space object
  //!
  const Dataspace & getSimple(size_t size);

 private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::map<size_t, Dataspace> pool_map;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
};

inline const Dataspace & DataspacePool::getSimple(size_t size)
{
  if(pool_map.count(size) < 1)
    pool_map[size] = Simple(hdf5::Dimensions{size}, hdf5::Dimensions{size});
  return pool_map[size];
}

} // namespace dataspace
} // namespace hdf5
