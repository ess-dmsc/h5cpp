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
// Created on: Aug 24, 2017
//

#include <stdexcept>
#include <h5cpp/dataspace/dataspace.hpp>

namespace hdf5 {
namespace dataspace {

Dataspace::Dataspace(Type type):
    handle_(ObjectHandle(H5Screate(static_cast<H5S_class_t>(type))))
{}

void Dataspace::close()
{
  handle_.close();
}

hssize_t Dataspace::size() const
{
  hssize_t s = H5Sget_simple_extent_npoints(static_cast<hid_t>(*this));
  if(s<0)
  {
    throw std::runtime_error("Failure retrieving the number of elements in the dataspace!");
  }
  return s;
}

Type Dataspace::type() const
{
  H5S_class_t buffer = H5Sget_simple_extent_type(static_cast<hid_t>(*this));
  if(buffer == H5S_NO_CLASS)
  {
    throw std::runtime_error("Failure to retrieve the dataspace type!");
  }

  return static_cast<Type>(buffer);

}

} // namespace dataspace
} // namespace hdf5
