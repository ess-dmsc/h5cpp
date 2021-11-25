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
//         Eugen Wintersberger <eugen.wintersberger@desy.de>
//         Jan Kotanski <jan.kotanski@desy.de>
// Created on: Dec 20, 2020
//

#include <h5cpp/core/hdf5_capi.hpp>
#include <h5cpp/filter/szip.hpp>
#include <h5cpp/error/error.hpp>
#include <sstream>

namespace hdf5 {
namespace filter {

SZip::SZip():
    Filter(H5Z_FILTER_SZIP),
    options_mask_(32),
    pixels_per_block_(0)
{}

SZip::SZip(unsigned int options_mask, unsigned int pixels_per_block):
    Filter(H5Z_FILTER_SZIP),
    options_mask_(options_mask),
    pixels_per_block_(pixels_per_block)
{}

SZip::~SZip()
{}

unsigned int SZip::options_mask() const noexcept
{
  return options_mask_;
}

void SZip::options_mask(unsigned int options_mask)
{
  options_mask_ = options_mask;
}

unsigned int SZip::pixels_per_block() const noexcept
{
  return pixels_per_block_;
}

void SZip::pixels_per_block(unsigned int pixels_per_block)
{
  pixels_per_block_ = pixels_per_block;
}

void SZip::operator()(const property::DatasetCreationList &dcpl,
                         Availability) const
{
  if(H5Pset_szip(static_cast<hid_t>(dcpl), options_mask_, pixels_per_block_)<0)
  {
    error::Singleton::instance().throw_with_stack("Could not apply SZip filter!");
  }
}

const unsigned int SZip::ec_option_mask = H5_SZIP_EC_OPTION_MASK;
const unsigned int SZip::nn_option_mask = H5_SZIP_NN_OPTION_MASK;


} // namespace filter
} // namespace hdf5
