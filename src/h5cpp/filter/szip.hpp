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

#include <h5cpp/filter/filter.hpp>

namespace hdf5 {
namespace filter {

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif
class DLL_EXPORT SZip : public Filter
{
  private:
    unsigned int options_mask_;
    unsigned int pixels_per_block_;
  public:
    SZip();
    SZip(unsigned int options_mask, unsigned int pixels_per_block);
    ~SZip() override;

    unsigned int options_mask() const noexcept;

    void options_mask(unsigned int options_mask);

    unsigned int pixels_per_block() const noexcept;

    void pixels_per_block(unsigned int pixels_per_block);

    virtual void operator()(const property::DatasetCreationList &dcpl,
                            Availability flag=Availability::Mandatory) const override;

    // Selects entropy coding method
    static const unsigned int ec_option_mask;
    // Selects nearest neighbor coding method.
    static const unsigned int nn_option_mask;
};
#ifdef __clang__
#pragma clang diagnostic pop
#endif

} // namespace filter
} // namespace hdf5
