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
// Created on: Nov 6, 2017
//

#include <stdexcept>
#include <h5cpp/file/memory_driver.hpp>

namespace hdf5 {
namespace file {

MemoryDriver::MemoryDriver() noexcept:
    increment_(1024*1024),
    backing_store_(false)
{}


MemoryDriver::MemoryDriver(size_t increment,bool backing_store) noexcept:
    increment_(increment),
    backing_store_(backing_store)
{}

bool MemoryDriver::backing_store() const noexcept
{
  return backing_store_;
}


void MemoryDriver::backing_store(bool value) noexcept
{
  backing_store_ = value;
}

size_t MemoryDriver::increment() const noexcept
{
  return increment_;
}

void MemoryDriver::increment(size_t value)
{
  increment_ = value;
}

void MemoryDriver::operator()(const property::FileAccessList &fapl) const
{
  if(H5Pset_fapl_core(static_cast<hid_t>(fapl),increment_,backing_store_)<0)
  {
    throw std::runtime_error("Failure setting Core driver!");
  }
}

DriverID MemoryDriver::id() const noexcept
{
  return DriverID::MEMORY;
}


}
}
