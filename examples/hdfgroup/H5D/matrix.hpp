//
// (c) Copyright 2018 Eugen Wintersberger <eugen.wintersberger@gmail.com>
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
// Author: Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Dec 29, 2018
//

#pragma once

#include <array>
#include <cstddef>
#include <iostream>
#include <algorithm>
#include <iomanip>


template<typename T,size_t DIM0,size_t DIM1> class Matrix
{
  public:
    using BufferType = std::array<T,DIM0*DIM1>;
    using value_type = typename BufferType::value_type;
    using iterator = typename BufferType::iterator;
    using const_iterator = typename BufferType::const_iterator;
    using pointer = value_type*;
    using const_pointer = const value_type*;
  private:
    BufferType _buffer;

    size_t offset(size_t i,size_t j) const noexcept
    {
      return i*DIM1+j;
    }
  public:
    Matrix() = default;
    Matrix(const Matrix<T,DIM0,DIM1> &matrix) = default;
    Matrix(Matrix<T,DIM0,DIM1> &&matrix) = default;
    explicit Matrix(value_type fill_value)
    {
      std::fill(begin(),end(),fill_value);
    }

    Matrix<T,DIM0,DIM1> &operator=(const Matrix<T,DIM0,DIM1> &matrix) = default;
    Matrix<T,DIM0,DIM1> &operator=(Matrix<T,DIM0,DIM1> &&matrix) = default;


    iterator begin() noexcept  {return _buffer.begin();}

    iterator end() noexcept { return _buffer.end(); }

    const_iterator begin() const noexcept  {return _buffer.begin();}

    const_iterator end() const noexcept { return _buffer.end();  }

    value_type operator()(size_t i,size_t j) const
    {
      return _buffer[offset(i,j)];
    }

    value_type &operator()(size_t i,size_t j)
    {
      return _buffer[offset(i,j)];
    }

    pointer data() noexcept { return _buffer.data(); }
    const_pointer data() const noexcept { return _buffer.data(); }
};

template<typename T,size_t DIM0,size_t DIM1>
std::ostream &operator<<(std::ostream &stream,const Matrix<T,DIM0,DIM1> &matrix)
{
  for(size_t i=0;i<DIM0;i++)
  {
    stream<<"[";
    for(size_t j=0;j<DIM1;j++)
    {
      stream<<" "<<std::setw(3)<<matrix(i,j);
    }
    stream<<"]"<<std::endl;
  }
  return stream;
}
