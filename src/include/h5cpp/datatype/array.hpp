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
// Created on: Oct 20, 2017
//
#pragma once

#include "datatype.hpp"
#include "../types.hpp"


namespace hdf5 {
namespace datatype {

//!
//! \brief array datatype
//!
//! This datatype allows storing multidimensional data as a single element
//! in an dataspace layout. Typical applications would be to use this for
//! tensors and vectors.
class Array : public Datatype
{
  public:
    Array();
    Array(const Dimensions &dims);

    //!
    //! \brief get dimensions
    //!
    //! Returns an instance of Dimensions with the number of elements along
    //! each dimension.
    //!
    //! \throws std::runtime_error in case of a failure
    //!
    Dimensions dimensions() const;
    size_t rank() const;


};

class VLengthArray : public Datatype
{
};

} // namespace datatype
} // namespace hdf5
