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
// Created on: Nov 20, 2017
//

#include <h5cpp/node/recursive_link_iterator.hpp>
#include <h5cpp/node/group.hpp>

namespace hdf5 {
namespace node {

RecursiveLinkIterator::RecursiveLinkIterator(const Group &current_group):
    current_group_(current_group),
    current_iterator_(current_group_.links.begin()),
    parent_iterator_()
{
}

RecursiveLinkIterator::RecursiveLinkIterator(const Group &current_group,
                                             RecursiveLinkIterator parent_iterator):
    current_group_(current_group),
    current_iterator_(current_group_.links.begin()),
    parent_iterator_(IteratorPointer(new RecursiveLinkIterator(parent_iterator)))
{
}

RecursiveLinkIterator RecursiveLinkIterator::begin(const Group &current_group)
{
  return RecursiveLinkIterator(current_group);
}

RecursiveLinkIterator RecursiveLinkIterator::end(const Group &current_group)
{
  RecursiveLinkIterator iter(current_group);
  iter.current_iterator_ = current_group.links.end();

  return iter;
}


Link RecursiveLinkIterator::operator*() const
{
  return *current_iterator_;
}

Link *RecursiveLinkIterator::operator->()
{
  return current_iterator_.operator->();
}

RecursiveLinkIterator &RecursiveLinkIterator::operator++()
{

  //if we are currently sitting on a group we have to enter the group if it
  // has some links attached to it
  if(current_iterator_->is_resolvable() &&
     (**current_iterator_).type() == Type::Group)
  {
    Group new_top(**current_iterator_);
    if(new_top.links.size())
    {
      *this =  RecursiveLinkIterator(new_top,*this);
      return *this; //we can return here
    }
  }

  ++current_iterator_; //increment the current iterator
  while((current_iterator_ == current_group_.links.end()) && parent_iterator_)
  {
      *this = *parent_iterator_;
      ++current_iterator_; //move on to the next element in the parent
  }
  return *this;
}

RecursiveLinkIterator RecursiveLinkIterator::operator++(int)
{
  RecursiveLinkIterator tmp_iter = *this;
  ++(*this);
  return tmp_iter;
}



bool RecursiveLinkIterator::operator==(const RecursiveLinkIterator &rhs) const
{
  return (current_iterator_ == rhs.current_iterator_) &&
         (current_group_    == rhs.current_group_   ) &&
         (parent_iterator_  == rhs.parent_iterator_ );

}

bool RecursiveLinkIterator::operator!=(const RecursiveLinkIterator &rhs) const
{
  return !(*this == rhs);
}

} // namespace node
} // namespace hdf5
