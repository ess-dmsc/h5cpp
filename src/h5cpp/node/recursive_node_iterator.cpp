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
// Created on: Nov 17, 2017
//

#include <h5cpp/node/recursive_node_iterator.hpp>
#include <h5cpp/node/group.hpp>

namespace hdf5 {
namespace node {

RecursiveNodeIterator::RecursiveNodeIterator(const Group &current_group):
    current_group_(current_group),
    current_iterator_(current_group_.nodes.begin()),
    parent_iterator_()
{
}

RecursiveNodeIterator::RecursiveNodeIterator(const Group &current_group,
                                             RecursiveNodeIterator parent_iterator):
    current_group_(current_group),
    current_iterator_(current_group_.nodes.begin()),
    parent_iterator_(IteratorPointer(new RecursiveNodeIterator(parent_iterator)))
{
}

RecursiveNodeIterator RecursiveNodeIterator::begin(const Group &current_group)
{
  return RecursiveNodeIterator(current_group);
}

RecursiveNodeIterator RecursiveNodeIterator::end(const Group &current_group)
{
  RecursiveNodeIterator iter(current_group);
  iter.current_iterator_ = current_group.nodes.end();

  return iter;
}


Node RecursiveNodeIterator::operator*() const
{
  return *current_iterator_;
}

Node *RecursiveNodeIterator::operator->()
{
  return current_iterator_.operator->();
}

RecursiveNodeIterator &RecursiveNodeIterator::operator++()
{
  //
  // if we are actually on a group node we have to enter the node if
  // it has children
  //
  if(current_iterator_->type()==Type::Group)
  {
    Group new_top(*current_iterator_);
    if(new_top.nodes.size())
    {
      *this =  RecursiveNodeIterator(new_top,*this);
      return *this;
    }
  }

  ++current_iterator_; // increment the current node iterator
  while((current_iterator_ == current_group_.nodes.end()) && parent_iterator_)
  {
      *this = *parent_iterator_;
      ++current_iterator_; //move on to the next element in the parent
  }

  return *this;
}

RecursiveNodeIterator RecursiveNodeIterator::operator++(int)
{
  RecursiveNodeIterator tmp_iter = *this;
  ++(*this);
  return tmp_iter;
}



bool RecursiveNodeIterator::operator==(const RecursiveNodeIterator &rhs) const
{
  return (current_iterator_ == rhs.current_iterator_) &&
         (current_group_    == rhs.current_group_   ) &&
         (parent_iterator_  == rhs.parent_iterator_ );

}

bool RecursiveNodeIterator::operator!=(const RecursiveNodeIterator &rhs) const
{
  return !(*this == rhs);
}

} // namespace node
} // namespace hdf5
