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
// Authors:
//         Eugen Wintersberger <eugen.wintersberger@desy.de>
//         Jan Kotanski <jan.kotanski@desy.de>
// Created on: Dec 20, 2020
//
#pragma once

#include <iostream>
#include <h5cpp/filter/filter.hpp>

namespace hdf5 {
namespace filter {




#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif
class DLL_EXPORT ScaleOffset : public Filter
{
  public:

    //!
    //! @brief character set encoding used by string types and links
    //!
    enum class ScaleType: std::underlying_type<H5Z_SO_scale_type_t>::type {
      //! floating-point type, using variable MinBits method
      FloatDScale = H5Z_SO_FLOAT_DSCALE,
      //! floating-point type, using fixed MinBits method
      FloatEScale = H5Z_SO_FLOAT_ESCALE,
      //! integer type
      Int = H5Z_SO_INT
    };
    //!
    //! \brief default constructor
    //!
    ScaleOffset();
    //!
    //! \brief constructor with scale type and scale factor
    //!
    ScaleOffset(ScaleOffset::ScaleType scale_type, int scale_factor);
    ~ScaleOffset() override;

    //!
    //! \brief get scale type
    //!
    ScaleOffset::ScaleType scale_type() const noexcept;

    //!
    //! \brief set scale type
    //!
    void scale_type(ScaleOffset::ScaleType scale_type);

    //!
    //! \brief get scale factor
    //!
    int scale_factor() const noexcept;

    //!
    //! \brief set scale factor
    //!
    void scale_factor(int scale_factor);

    virtual void operator()(const property::DatasetCreationList &dcpl,
                            Availability flag=Availability::Mandatory) const override;
  private:
    ScaleOffset::ScaleType scale_type_;
    int scale_factor_;

};
#ifdef __clang__
#pragma clang diagnostic pop
#endif



//!
//! @brief stream output operator for CharacterEncoding enumerations
//!
//! @param stream reference to an output stream
//! @param scale_type reference to the scala type to write
//! @return modified output stream
//!
DLL_EXPORT std::ostream &operator<<(std::ostream &stream, const ScaleOffset::ScaleType &scale_type);


} // namespace filter
} // namespace hdf5
