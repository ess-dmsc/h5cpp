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
// Author: Martin Shetty <martin.shetty@esss.se>
// Created on: Oct 25, 2017
//

#include <h5cpp/error/h5c_error.hpp>
#include <sstream>

namespace hdf5 {
namespace error {

H5CError::H5CError(const std::list<Descriptor>& H5CError)
: std::runtime_error("")
, contents_(H5CError)
{
  std::stringstream ss;
  for (auto c : contents_)
    ss << c << "\n";
  what_message_ = ss.str();
}

const char* H5CError::what() const throw()
{
  return what_message_.c_str();
}

const std::list<Descriptor>& H5CError::contents() const
{
  return contents_;
}

bool H5CError::empty() const
{
  return contents_.empty();
}

} // namespace file
} // namespace hdf5
