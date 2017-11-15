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
#include <h5cpp/filter/shuffle.hpp>


namespace hdf5 {
namespace filter {

Shuffle::Shuffle():
    Filter(H5Z_FILTER_SHUFFLE)
{}

Shuffle::~Shuffle()
{}

void Shuffle::operator()(const property::DatasetCreationList &dcpl,
                         Availability flag) const
{
  if(H5Pset_shuffle(static_cast<hid_t>(dcpl))<0)
  {
    throw std::runtime_error("Failure to set shuffle filter!");
  }
}

} // namespace filter
} // namespace hdf5
