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
#pragma once

#include <stdexcept>

namespace hdf5{

class Iterator
{
  private:
    //! actual position state of the iterator
    ssize_t index_;

  public:

    //! default constructor
    Iterator();
    explicit Iterator(ssize_t index);
    Iterator(const Iterator &) = default;

    Iterator & operator=(const Iterator&) = default;

    virtual ~Iterator();

    //! increment iterator position
    Iterator &operator++();
    Iterator &operator--();
    Iterator &operator+=(ssize_t i);
    Iterator &operator-=(ssize_t i);


    bool operator<(const Iterator &b) const;
    bool operator<=(const Iterator &b) const;
    bool operator>(const Iterator &b) const;
    bool operator>=(const Iterator &b) const;

    //! get state of the iterator
    ssize_t index() const { return index_; }

};



Iterator &operator+(const Iterator&a,ssize_t b);

Iterator operator+(ssize_t a,const Iterator &b);

Iterator operator-(const Iterator &a,ssize_t b);

ssize_t operator-(const Iterator &a,const Iterator &b);

} // namespace hdf5
