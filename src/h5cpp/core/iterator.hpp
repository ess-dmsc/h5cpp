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
#include <h5cpp/core/windows.hpp>

namespace hdf5{

class DLL_EXPORT Iterator
{
  private:
    //! actual position state of the iterator
    ssize_t index_ {0};

  public:

    //! default constructor
    Iterator();
    explicit Iterator(ssize_t index);
    Iterator(const Iterator &) = default;

    Iterator & operator=(const Iterator&) = default;

    virtual ~Iterator();

    //! increment iterator position
    // prefix
    Iterator &operator++();
    Iterator &operator--();
    // postfix
    Iterator operator++(int);
    Iterator operator--(int);

    Iterator &operator+=(ssize_t i);
    Iterator &operator-=(ssize_t i);

    bool operator==(const Iterator &b) const;
    bool operator<(const Iterator &b) const;
    bool operator<=(const Iterator &b) const;
    bool operator>(const Iterator &b) const;
    bool operator>=(const Iterator &b) const;

    //! get state of the iterator
    ssize_t index() const { return index_; }

};

DLL_EXPORT Iterator operator+(const Iterator&a, ssize_t b);

DLL_EXPORT Iterator operator+(ssize_t a,const Iterator &b);

DLL_EXPORT Iterator operator-(const Iterator &a,ssize_t b);

DLL_EXPORT ssize_t operator-(const Iterator &a,const Iterator &b);

} // namespace hdf5
