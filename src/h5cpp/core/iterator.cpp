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

#include <h5cpp/core/iterator.hpp>

namespace hdf5 {

Iterator::Iterator():
    index_(0)
{}

Iterator::Iterator(ssize_t index):
    index_(index)
{}

Iterator::~Iterator()
{}

Iterator &Iterator::operator++()
{
  index_++;
  return *this;
}

Iterator &Iterator::operator--()
{
  index_--;
  return *this;
}

Iterator Iterator::operator++(int)
{
  Iterator tmp(*this);
  operator++();
  return tmp;
}

Iterator Iterator::operator--(int)
{
  Iterator tmp(*this);
  operator--();
  return tmp;
}

Iterator &Iterator::operator+=(ssize_t i)
{
  index_ += i;
  return *this;
}


Iterator &Iterator::operator-=(ssize_t i)
{
  index_ -= i;
  return *this;
}

bool Iterator::operator==(const Iterator &b) const
{
  return index_ == b.index_;
}

bool Iterator::operator<(const Iterator &b) const
{
  return index_ < b.index_;
}

bool Iterator::operator<=(const Iterator &b) const
{
  return index_ <= b.index_;
}

bool Iterator::operator>(const Iterator &b) const
{
  return index_ > b.index_;
}

bool Iterator::operator>=(const Iterator &b) const
{
  return index_ >= b.index_;
}

Iterator operator+(const Iterator&a,ssize_t b)
{
  Iterator iter = a;
  iter += b;
  return iter;
}

Iterator operator+(ssize_t a,const Iterator &b)
{
  return b+a;
}


Iterator operator-(const Iterator &a,ssize_t b)
{
  Iterator iter = a;
  iter -= b;
  return iter;
}

ssize_t operator-(const Iterator &a,const Iterator &b)
{
  return a.index() - b.index();
}

} // namespace hdf5
