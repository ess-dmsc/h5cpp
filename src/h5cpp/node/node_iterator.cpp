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

#include <h5cpp/node/node_iterator.hpp>
#include <h5cpp/node/group.hpp>
#include <h5cpp/core/utilities.hpp>

namespace hdf5 {
namespace node {

NodeIterator::NodeIterator(const Group &group,ssize_t index):
    Iterator(index),
    group_(group),
    current_node_()
{}


NodeIterator NodeIterator::begin(const Group &group)
{
  return NodeIterator(group,0);
}

NodeIterator NodeIterator::end(const Group &group)
{
  return NodeIterator(group,unsigned2signed<ssize_t>(group.nodes.size()));
}

Node NodeIterator::operator*() const
{
  current_node_ = group_.nodes[signed2unsigned<size_t>(index())];
  return current_node_;
}

Node *NodeIterator::operator->()
{
  current_node_ = group_.nodes[signed2unsigned<size_t>(index())];
  return &current_node_;
}

NodeIterator &NodeIterator::operator++()
{
  Iterator::operator++();
  return *this;
}

NodeIterator NodeIterator::operator++(int)
{
  NodeIterator tmp_iter = *this;
  ++(*this);
  return tmp_iter;
}

NodeIterator &NodeIterator::operator--()
{
  Iterator::operator--();
  return *this;
}


NodeIterator NodeIterator::operator--(int)
{
  NodeIterator tmp = *this;
  --(*this);
  return tmp;
}

bool NodeIterator::operator==(const NodeIterator &a) const
{
  //check first if we iterate over the same group
  if(group_.id()!=a.group_.id())
    return false;

  if(index()!=a.index())
    return false;

  return true;
}

bool NodeIterator::operator!=(const NodeIterator &a) const
{
  return !(*this==a);
}

} // namespace node
} // namespace hdf5
