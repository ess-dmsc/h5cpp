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
    option_mask_(32),
    pixels_per_block_(0)
{}

SZip::SZip(OptionMaskBase option_mask, unsigned int pixels_per_block):
    Filter(H5Z_FILTER_SZIP),
    option_mask_(option_mask),
    pixels_per_block_(pixels_per_block)
{}

SZip::SZip(OptionMask option_mask, unsigned int pixels_per_block):
    Filter(H5Z_FILTER_SZIP),
    option_mask_(static_cast<SZip::OptionMaskBase>(option_mask)),
    pixels_per_block_(pixels_per_block)
{}

SZip::~SZip()
{}

SZip::OptionMaskBase SZip::option_mask() const noexcept
{
  return option_mask_;
}

void SZip::option_mask(SZip::OptionMaskBase option_mask)
{
  option_mask_ = option_mask;
}

void SZip::option_mask(SZip::OptionMask option_mask)
{
  option_mask_ = static_cast<SZip::OptionMaskBase>(option_mask);
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
  if(H5Pset_szip(static_cast<hid_t>(dcpl), option_mask_, pixels_per_block_)<0)
  {
    error::Singleton::instance().throw_with_stack("Could not apply SZip filter!");
  }
}

std::ostream &operator<<(std::ostream &stream,const SZip::OptionMask &flags)
{
  switch(flags)
  {
    case SZip::OptionMask::None : return stream<<"WITHOUT_CODING";
    case SZip::OptionMask::AllowK13 : return stream<<"ALLOW_K13_CODING";
    case SZip::OptionMask::Chip : return stream<<"CHIP_CODING";
    case SZip::OptionMask::EntropyCoding : return stream<<"ENTROPY_CODING";
    case SZip::OptionMask::NearestNeighbor : return stream<<"NEAREST_NEIGHBOR_CODING";
    default:
      return stream;
  }
}

SZip::OptionMaskBase operator|(const SZip::OptionMask &lhs,const SZip::OptionMask &rhs)
{
  return static_cast<SZip::OptionMaskBase>(lhs) | static_cast<SZip::OptionMaskBase>(rhs);
}

SZip::OptionMaskBase operator|(const SZip::OptionMask &lhs,const SZip::OptionMaskBase &rhs)
{
  return static_cast<SZip::OptionMaskBase>(lhs) | rhs;
}

SZip::OptionMaskBase operator|(const SZip::OptionMaskBase &lhs,const SZip::OptionMask &rhs)
{
  return lhs | static_cast<SZip::OptionMaskBase>(rhs);
}

SZip::OptionMaskBase operator&(const SZip::OptionMask &lhs,const SZip::OptionMask &rhs)
{
  return static_cast<SZip::OptionMaskBase>(lhs) & static_cast<SZip::OptionMaskBase>(rhs);
}

SZip::OptionMaskBase operator&(const SZip::OptionMask &lhs,const SZip::OptionMaskBase &rhs)
{
  return static_cast<SZip::OptionMaskBase>(lhs) & rhs;
}

SZip::OptionMaskBase operator&(const SZip::OptionMaskBase &lhs,const SZip::OptionMask &rhs)
{
  return rhs & static_cast<SZip::OptionMaskBase>(lhs);
}

bool operator==(const SZip::OptionMask &lhs,const SZip::OptionMask &rhs)
{
  return static_cast<SZip::OptionMaskBase>(lhs) == static_cast<SZip::OptionMaskBase>(rhs);
}

bool operator==(const SZip::OptionMask &lhs,const SZip::OptionMaskBase &rhs)
{
  return static_cast<SZip::OptionMaskBase>(lhs) == rhs;
}

bool operator==(const SZip::OptionMaskBase &lhs,const SZip::OptionMask &rhs)
{
  return static_cast<SZip::OptionMaskBase>(rhs) == lhs;
}

bool operator!=(const SZip::OptionMask &lhs,const SZip::OptionMask &rhs)
{
  return !(static_cast<SZip::OptionMaskBase>(lhs) == static_cast<SZip::OptionMaskBase>(rhs));
}

bool operator!=(const SZip::OptionMask &lhs,const SZip::OptionMaskBase &rhs)
{
  return !(static_cast<SZip::OptionMaskBase>(lhs) == rhs);
}

bool operator!=(const SZip::OptionMaskBase &lhs,const SZip::OptionMask &rhs)
{
  return !(static_cast<SZip::OptionMaskBase>(rhs) == lhs);
}



} // namespace filter
} // namespace hdf5
