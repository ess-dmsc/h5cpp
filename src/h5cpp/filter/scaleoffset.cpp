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
#include <h5cpp/filter/scaleoffset.hpp>
#include <h5cpp/error/error.hpp>
#include <sstream>

namespace hdf5 {
namespace filter {

ScaleOffset::ScaleOffset():
    Filter(H5Z_FILTER_SCALEOFFSET),
    scale_type_(SOScaleType::FLOAT_DSCALE),
    scale_factor_(1)
{}

ScaleOffset::ScaleOffset(SOScaleType scale_type, int scale_factor):
    Filter(H5Z_FILTER_SCALEOFFSET),
    scale_type_(scale_type),
    scale_factor_(scale_factor)
{}

ScaleOffset::~ScaleOffset()
{}

SOScaleType ScaleOffset::scale_type() const noexcept
{
  return scale_type_;
}

void ScaleOffset::scale_type(SOScaleType scale_type)
{
  scale_type_ = scale_type;
}

int ScaleOffset::scale_factor() const noexcept
{
  return scale_factor_;
}

void ScaleOffset::scale_factor(int scale_factor)
{
  scale_factor_ = scale_factor;
}

void ScaleOffset::operator()(const property::DatasetCreationList &dcpl,
                         Availability) const
{
  if(H5Pset_scaleoffset(static_cast<hid_t>(dcpl), static_cast<H5Z_SO_scale_type_t>(scale_type_), scale_factor_)<0)
  {
    error::Singleton::instance().throw_with_stack("Could not apply ScaleOffset filter!");
  }
}

std::ostream &operator<<(std::ostream &stream, const SOScaleType &scale_type) {
  switch (scale_type) {
    case SOScaleType::FLOAT_DSCALE: return stream << "FLOAT_DSCALE";
    case SOScaleType::FLOAT_ESCALE: return stream << "FLOAT_ESCALE";
    case SOScaleType::INT: return stream << "INT";
    default:return stream;
  }
}

} // namespace filter
} // namespace hdf5
