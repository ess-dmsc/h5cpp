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

#include <h5cpp/filter/nbit.hpp>
#include <h5cpp/error/error.hpp>

namespace hdf5 {
namespace filter {

NBit::NBit():
    Filter(H5Z_FILTER_NBIT)
{}

NBit::~NBit()
{}

void NBit::operator()(const property::DatasetCreationList &dcpl,
                            Availability) const
{
  if(H5Pset_nbit(static_cast<hid_t>(dcpl))<0)
  {
    error::Singleton::instance().throw_with_stack("Failure to set the nbit filter!");
  }
}

} // namespace filter
} // namespace hdf5
