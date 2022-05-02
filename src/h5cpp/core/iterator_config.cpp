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
// Created on: Sep 11, 2017
//

#include <h5cpp/core/iterator_config.hpp>

namespace hdf5 {

std::ostream &operator<<(std::ostream &stream,const IterationOrder &order)
{
  switch(order)
  {
    case IterationOrder::Decreasing: return stream<<"DECREASING";
    case IterationOrder::Increasing: return stream<<"INCREASING";
    case IterationOrder::Native: return stream<<"NATIVE";
  }
  return stream;
}

std::ostream &operator<<(std::ostream &stream,const IterationIndex &index)
{
  switch(index)
  {
    case IterationIndex::CreationOrder: return stream<<"CREATION_ORDER";
    case IterationIndex::Name: return stream<<"NAME";
  }
  return stream;
}

IteratorConfig::IteratorConfig():
    order_(IterationOrder::Native),
    index_(IterationIndex::Name),
    lapl_(property::LinkAccessList())
{}

IterationOrder IteratorConfig::order() const noexcept
{
  return order_;
}

void IteratorConfig::order(IterationOrder o) noexcept
{
  order_ = o;
}

IterationIndex IteratorConfig::index() const noexcept
{
  return index_;
}

void IteratorConfig::index(IterationIndex i) noexcept
{
  index_ = i;
}

const property::LinkAccessList &IteratorConfig::link_access_list() const noexcept
{
  return lapl_;
}

void IteratorConfig::link_access_list(const property::LinkAccessList &list)
{
  lapl_ = list;
}



} // namespace hdf5
