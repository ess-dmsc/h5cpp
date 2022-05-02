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
// Created on: Nov 6, 2017
//

#include <h5cpp/core/hdf5_capi.hpp>
#include <h5cpp/file/direct_driver.hpp>
#include <h5cpp/property/file_access.hpp>
#include <h5cpp/error/error.hpp>

#ifdef H5_HAVE_DIRECT

namespace hdf5 {
namespace file {

DirectDriver::DirectDriver():
    alignment_(0),
    block_size_(0),
    copy_buffer_size_(0)
{}

DirectDriver::DirectDriver(size_t alignment,size_t block_size,
                           size_t copy_buffer_size):
  alignment_(alignment),
  block_size_(block_size),
  copy_buffer_size_(copy_buffer_size)
{}

size_t DirectDriver::alignment() const noexcept
{
  return alignment_;
}

void DirectDriver::alignment(size_t value)
{
  alignment_ = value;
}

size_t DirectDriver::block_size() const noexcept
{
  return block_size_;
}

void DirectDriver::block_size(size_t value)
{
  block_size_ = value;
}

size_t DirectDriver::copy_buffer_size() const noexcept
{
  return copy_buffer_size_;
}

void DirectDriver::copy_buffer_size(size_t value)
{
  copy_buffer_size_ = value;
}

void DirectDriver::operator()(const property::FileAccessList &fapl) const
{
  if(H5Pset_fapl_direct(static_cast<hid_t>(fapl),alignment_,
                        block_size_,copy_buffer_size_)<0)
  {
    error::Singleton::instance().throw_with_stack("Failure to set direct file driver!");
  }
}

DriverID DirectDriver::id() const noexcept
{
  return DriverID::Direct;
}

} // namespace file
} // namespace hdf5
#endif
