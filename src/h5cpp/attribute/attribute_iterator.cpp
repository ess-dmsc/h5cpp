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
// Created on: Oct 5, 2017
//

#include <h5cpp/attribute/attribute_iterator.hpp>
#include <h5cpp/attribute/attribute.hpp>
#include <h5cpp/core/utilities.hpp>
#include <h5cpp/node/node.hpp>

namespace hdf5 {
namespace attribute {

AttributeIterator::AttributeIterator(const AttributeManager &view,ssize_t index):
    Iterator(index),
    manager_(view),
    current_attribute_()
{
  if(*this)
    current_attribute_ = manager_.get()[signed2unsigned<size_t>(Iterator::index())];
}


Attribute AttributeIterator::operator*() const
{
  if(!(*this))
    throw std::runtime_error("Invalid iterator!");

  return current_attribute_;
}

Attribute *AttributeIterator::operator->()
{
  if(!(*this))
    throw std::runtime_error("Invalid iterator!");

  return &current_attribute_;
}

AttributeIterator &AttributeIterator::operator++()
{
  Iterator::operator++();
  if(*this)
    current_attribute_ = manager_.get()[signed2unsigned<size_t>(index())];

  return *this;
}

AttributeIterator AttributeIterator::operator++(int)
{
  AttributeIterator tmp_iter = *this;
  ++(*this);
  return tmp_iter;
}

AttributeIterator &AttributeIterator::operator--()
{
  Iterator::operator--();
  if(*this) current_attribute_ = manager_.get()[signed2unsigned<size_t>(index())];
  return *this;
}


AttributeIterator AttributeIterator::operator--(int)
{
  AttributeIterator tmp = *this;
  --(*this);
  return tmp;
}

AttributeIterator &AttributeIterator::operator+=(ssize_t i)
{
  Iterator::operator+=(i);
  if(*this) current_attribute_ = manager_.get()[signed2unsigned<size_t>(index())];
  return *this;
}

AttributeIterator &AttributeIterator::operator-=(ssize_t i)
{
  Iterator::operator-=(i);
  if(*this) current_attribute_ = manager_.get()[signed2unsigned<size_t>(index())];
  return *this;
}

bool AttributeIterator::operator==(const AttributeIterator &a) const
{
  //check first if we iterate over the same group
  if(manager_.get().node().id()!=a.manager_.get().node().id())
    return false;

  if(index()!=a.index())
    return false;

  return true;
}

bool AttributeIterator::operator!=(const AttributeIterator &a) const
{
  return !(*this==a);
}

} // namespace attribute
} // namespace hdf5
