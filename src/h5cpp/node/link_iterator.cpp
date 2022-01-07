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
// Created on: Sep 13, 2017
//

#include <h5cpp/node/link_iterator.hpp>
#include <h5cpp/node/group.hpp>
#include <h5cpp/core/utilities.hpp>

namespace hdf5 {
namespace node {

LinkIterator::LinkIterator(const Group &group,ssize_t index):
    Iterator(index),
    group_(group),
    current_link_()
{
}

LinkIterator LinkIterator::begin(const Group &group)
{
  return LinkIterator(group,0);
}

LinkIterator LinkIterator::end(const Group &group)
{
  return LinkIterator(group,unsigned2signed<ssize_t>(group.links.size()));
}

Link LinkIterator::operator*() const
{
  current_link_ = group_.links[signed2unsigned<size_t>(index())];
  return current_link_;
}

Link *LinkIterator::operator->()
{
  current_link_ = group_.links[signed2unsigned<size_t>(index())];
  return &current_link_;
}

LinkIterator &LinkIterator::operator++()
{
  Iterator::operator++();
  return *this;
}

LinkIterator LinkIterator::operator++(int)
{
  LinkIterator tmp_iter = *this;
  ++(*this);
  return tmp_iter;
}

LinkIterator &LinkIterator::operator--()
{
  Iterator::operator--();
  return *this;
}


LinkIterator LinkIterator::operator--(int)
{
  LinkIterator tmp = *this;
  --(*this);
  return tmp;
}

bool LinkIterator::operator==(const LinkIterator &a) const
{
  //check first if we iterate over the same group
  if(group_.id()!=a.group_.id())
    return false;

  if(index()!=a.index())
    return false;

  return true;
}

bool LinkIterator::operator!=(const LinkIterator &a) const
{
  return !(*this==a);
}

} // namespace node
} // namespace hdf5
