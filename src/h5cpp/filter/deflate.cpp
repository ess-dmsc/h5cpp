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
#include <h5cpp/filter/deflate.hpp>
#include <h5cpp/error/error.hpp>
#include <sstream>

namespace hdf5 {
namespace filter {

Deflate::Deflate():
    Filter(H5Z_FILTER_DEFLATE),
    level_(0)
{}

Deflate::Deflate(unsigned int value):
    Filter(H5Z_FILTER_DEFLATE),
    level_(value)
{
  if(value>9)
  {
    std::stringstream ss;
    ss<<"Failure to construct a deflate filter with a compression level of "
      <<value<<" - allowed values are between 0 and 9!";
    throw std::runtime_error(ss.str());
  }
}

Deflate::~Deflate()
{}

unsigned int Deflate::level() const noexcept
{
  return level_;
}

void Deflate::level(unsigned int value)
{
  if(value>9)
  {
    std::stringstream ss;
    ss<<"Cannot set the compression level to "<<value<<" for a deflate filter"
      <<std::endl<<"Allowed values are 0 to 9!";
    throw std::runtime_error(ss.str());
  }
  level_ = value;
}

void Deflate::operator()(const property::DatasetCreationList &dcpl,
                         Availability) const
{
  if(H5Pset_deflate(static_cast<hid_t>(dcpl),level_)<0)
  {
    error::Singleton::instance().throw_with_stack("Could not apply Deflate filter!");
  }
}

} // namespace filter
} // namespace hdf5
