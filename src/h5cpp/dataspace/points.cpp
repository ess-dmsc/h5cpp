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
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 25, 2017
//
#include <h5cpp/dataspace/points.hpp>
#include <h5cpp/error/error.hpp>
#include <sstream>

namespace hdf5
{
namespace dataspace
{

Points::Points() :
    Selection() {}

Points::~Points() {}

Points::Points(size_t rank)
    : Selection()
      , rank_(rank) {}


Points::Points(const std::vector<std::vector<hsize_t>>& coord_set)
{
  if (!coord_set.empty())
    rank_ = coord_set.front().size();
  add_set(coord_set);
}

size_t Points::rank() const
{
  return rank_;
}

size_t Points::points() const
{
  if (rank_)
    return coordinates_.size() / rank_;
  return 0;
}

void Points::add_set(const std::vector<std::vector<hsize_t>>& coord_set)
{
  for (const auto& coords : coord_set)
    add(coords);
}


void Points::add(const std::vector<hsize_t>& coords)
{
  if (coords.size() != rank_)
  {
    std::stringstream ss;
    ss << "Adding coordinate of rank=" << coords.size()
       << " to point selection of rank=" << rank_;
    throw (std::runtime_error(ss.str()));
  }
  coordinates_.insert(coordinates_.end(), coords.begin(), coords.end());
}

void Points::apply(const Dataspace& space,
                   SelectionOperation ops) const
{
  if (0 > H5Sselect_elements(static_cast<hid_t>(space),
                             static_cast<H5S_seloper_t>(ops),
                             points(), coordinates_.data()))
  {
    error::Singleton::instance().throw_with_stack("Could not apply point selection to dataspace");
  }

}

} // namespace dataspace
} // namespace hdf5
