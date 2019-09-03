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
// Author: Jan Kotanski <jan.kotanski@desy.de>
// Created on: Sep 3, 2019
//

#include <h5cpp/core/hdf5_capi.hpp>
#include <h5cpp/error/error.hpp>
#include <h5cpp/filter/filter.hpp>
#include <h5cpp/filter/external_filter.hpp>
#include <sstream>

using FilterID = H5Z_filter_t;


namespace hdf5 {
namespace filter {

bool is_filter_available(FilterID id){
  return H5Zfilter_avail(id);
}


ExternalFilter::ExternalFilter(FilterID id, const std::vector<unsigned int> cd_values):
    Filter(id),
    cd_values_(cd_values)
{
}

ExternalFilter::~ExternalFilter()
{}


void ExternalFilter::operator()(const property::DatasetCreationList &dcpl,
                         Availability flag) const
{
  if(! is_filter_available(id())){
    throw std::runtime_error("External filter not available!");
  }
  if(H5Pset_filter(static_cast<hid_t>(dcpl), id(), static_cast<hid_t>(flag),
		   cd_values_.size(), cd_values_.data()) < 0)
    {
      error::Singleton::instance().throw_with_stack("Could not apply external filter!");
    }
}

const std::vector<unsigned int> ExternalFilter::cd_values() const noexcept
{
  return cd_values_;
}


} // namespace filter
} // namespace hdf5
