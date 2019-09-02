//
// (c) Copyright 2019 Eugen Wintersberger <eugen.wintersberger@gmail.com>
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
// Created on: Sep 1, 2019
//
#pragma once

#include <h5cpp/hdf5.hpp>
#include <complex>

namespace hdf5  {
namespace datatype {


/**
 * @brief datatype trait for complex numbers
 *
 * This trait creates a HDF5 datatype to store complex numbers. Complex
 * numbers are stored in a compound data type with to fields of name
 *
 * - real - storing the real part
 * - imag - storing the imaginary part
 *
 * \tparam T the base type for the C++ complex number type
 */
template<typename T>
class Trait<std::complex<T>>
{
  private:
    /**
     * internal data structure equivalent of a complex number class
     * - used to determine the memory layout.
     */
    struct complex_struct {
        T real;
        T imag;
    };
  public:
    using Type = std::complex<T>;
    using TypeClass = Compound;

    /**
     * @brief create a compound type for complex numbers
     *
     * @return a compound data type for complex numbers
     */
    static TypeClass create(const Type& = Type())
    {
      auto base_type= Trait<T>::create();
      auto complex = Compound::create(sizeof(complex_struct));
      complex.insert("real", HOFFSET(complex_struct, real), base_type);
      complex.insert("imag", HOFFSET(complex_struct, imag), base_type);
      return complex;
    }

};


} // end of namespace datatype
} // end of namespace hdf5