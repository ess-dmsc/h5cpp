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
// Created on: Sep 14, 2017
//
#pragma once
#include <iostream>
#include <vector>
#include <cstdint>

template<typename PixelT>
class Image
{
  private:
    size_t ny_;
    size_t nx_;
    std::vector<PixelT> data_;
  public:
    Image():
      ny_(0),
      nx_(0),
      data_()
    {}

    Image(size_t ny,size_t nx):
      ny_(ny),
      nx_(nx),
      data_(nx*ny)
    {}

    const PixelT &operator()(size_t i,size_t j) const
    {
       return data_[i*nx_+j];
    }

    PixelT &operator()(size_t i,size_t j)
    {
      return data_[i*nx_+j];
    }

    size_t size() const
    {
      return nx()*ny();
    }

    size_t nx() const
    {
      return nx_;
    }

    size_t ny() const
    {
      return ny_;
    }

    PixelT *data()
    {
      return data_.data();
    }

    const PixelT *data() const
    {
      return data_.data();
    }
};
