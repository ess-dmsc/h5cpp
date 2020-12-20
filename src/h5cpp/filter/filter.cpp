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

#include <h5cpp/filter/filter.hpp>

namespace hdf5 {
namespace filter {

Filter::Filter():
    id_(H5Z_FILTER_NONE)
{}

Filter::Filter(FilterID id):
    id_(id)
{}

Filter::~Filter()
{}

FilterID Filter::id() const noexcept
{
  return id_;
}

bool Filter::is_encoding_enabled() const
{
  unsigned int filter_info;
  if(H5Zget_filter_info(id_, &filter_info) < 0)
  {
    std::stringstream ss;
    ss<<"Configuration flag cannot be checked for filter: " << id_;
    error::Singleton::instance().throw_with_stack(ss.str());
  }

  return  bool(filter_info & H5Z_FILTER_CONFIG_ENCODE_ENABLED);
}

bool Filter::is_decoding_enabled() const
{
  unsigned int filter_info;
  if(H5Zget_filter_info(id_, &filter_info) < 0)
  {
    std::stringstream ss;
    ss<<"Configuration flag cannot be checked for filter: " << id_;
    error::Singleton::instance().throw_with_stack(ss.str());
  }

  return  bool(filter_info & H5Z_FILTER_CONFIG_DECODE_ENABLED);
}

} // namespace filter
} // namesapce hdf5
