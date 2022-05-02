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
#include <h5cpp/core/utilities.hpp>
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


ExternalFilter::ExternalFilter(FilterID id,
			       const std::vector<unsigned int> cd_values,
			       const std::string &name):
    Filter(id),
    cd_values_(cd_values),
    name_(name)
{
}

ExternalFilter::ExternalFilter():
    Filter(0),
    cd_values_(0, 0),
    name_("")
{
}


void ExternalFilter::operator()(const property::DatasetCreationList &dcpl,
                         Availability flag) const
{
  if(H5Pset_filter(static_cast<hid_t>(dcpl), id(),
                   signed2unsigned<unsigned>(static_cast<hid_t>(flag)),
		   cd_values_.size(), cd_values_.data()) < 0)
    {
      error::Singleton::instance().throw_with_stack("Could not apply external filter!");
    }
}

const std::vector<unsigned int> ExternalFilter::cd_values() const noexcept
{
  return cd_values_;
}

const std::string ExternalFilter::name() const noexcept
{
  return name_;
}

const std::vector<Availability> ExternalFilters::fill(const property::DatasetCreationList &dcpl,
						      size_t max_cd_number,
						      size_t max_name_size)
{
  std::vector<Availability> flags;
  size_t nfilters = dcpl.nfilters();
  unsigned int flag;
  size_t cd_number = max_cd_number;
  std::vector<char> fname(max_name_size);

  for(unsigned int nf=0; nf != nfilters; nf++)
  {
    std::vector<unsigned int> cd_values(max_cd_number);
    int filter_id = H5Pget_filter(static_cast<hid_t>(dcpl),
			      nf,
			      &flag,
			      &cd_number,
			      cd_values.data(),
			      fname.size(),
			      fname.data(),
			      nullptr);
    if(filter_id < 0)
    {
      std::stringstream ss;
      ss << "Failure to read a parameters of filter ("
	 << nf << ") from " << dcpl.get_class();
      error::Singleton::instance().throw_with_stack(ss.str());
    }
    if(cd_number > max_cd_number)
    {
      std::stringstream ss;
      ss<<"Too many filter parameters in " << dcpl.get_class();
      error::Singleton::instance().throw_with_stack(ss.str());
    }
    cd_values.resize(cd_number);
    if(static_cast<int>(static_cast<Availability>(flag)) != unsigned2signed<int>(flag))
    {
      std::stringstream ss;
      ss<<"Wrong filter flag value in " << dcpl.get_class();
      error::Singleton::instance().throw_with_stack(ss.str());
    }

    Availability fflag = static_cast<Availability>(flag);
    fname[max_name_size - 1] = '\0';
    std::string name(fname.data());
    push_back(ExternalFilter(filter_id, cd_values, name));
    flags.push_back(fflag);
  }
  return flags;
}

} // namespace filter
} // namespace hdf5
