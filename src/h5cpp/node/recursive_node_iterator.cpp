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
// Created on: Nov 17, 2017
//

#include <h5cpp/node/recursive_node_iterator.hpp>
#include <h5cpp/node/group.hpp>

namespace hdf5 {
namespace node {

RecursiveNodeIterator::RecursiveNodeIterator(const Group &current_group):
    current_group_(current_group),
    current_iterator_(current_group_.nodes.begin()),
    current_node_(),
    parent_iterator_()
{
  if(*this)
    current_node_ = *current_iterator_;
}

RecursiveNodeIterator::RecursiveNodeIterator(const Group &current_group,
                                             RecursiveNodeIterator parent_iterator):
    current_group_(current_group),
    current_iterator_(current_group_.nodes.begin()),
    current_node_(),
    parent_iterator_(IteratorPointer(new RecursiveNodeIterator(parent_iterator)))
{
  if(*this)
    current_node_ = *current_iterator_;
}


Node RecursiveNodeIterator::operator*() const
{
  if(!(*this))
    throw std::runtime_error("Invalid iterator!");

  return current_node_;
}

Node *RecursiveNodeIterator::operator->()
{
  if(!(*this))
    throw std::runtime_error("Invalid iterator!");

  return &current_node_;
}

RecursiveNodeIterator &RecursiveNodeIterator::operator++()
{
  if(current_node_.type()==Type::GROUP)
  {
    Group new_top(current_node_);
    if(new_top.nodes.size())
    {
      *this =  RecursiveNodeIterator(new_top,*this);
      return *this;
    }
  }

  current_iterator_++;
  if(current_iterator_)
    current_node_ = *current_iterator_;
  else
  {
    //we have reached the end of the current iterator and go back to
    //the parent iterator
    *this = *parent_iterator_;
    ++current_iterator_;
    if(current_iterator_)
      current_node_ = *current_iterator_;

  }


  return *this;
}

RecursiveNodeIterator RecursiveNodeIterator::operator++(int)
{
  RecursiveNodeIterator tmp_iter = *this;
  ++(*this);
  return tmp_iter;
}



bool RecursiveNodeIterator::operator==(const RecursiveNodeIterator &a) const
{
  return true;
}

bool RecursiveNodeIterator::operator!=(const RecursiveNodeIterator &a) const
{
  return false;
}

} // namespace node
} // namespace hdf5
