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
// Created on: Nov 6, 2017
//
#pragma once

#include <h5cpp/filter/filter.hpp>

namespace hdf5 {
namespace filter {

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif
class DLL_EXPORT Shuffle : public Filter
{
  public:
    //!
    //! \brief default constructor
    //!
    Shuffle();

    ~Shuffle() override;

    virtual void operator()(const property::DatasetCreationList &dcpl,
                            Availability flag = Availability::Mandatory) const override;

};
#ifdef __clang__
#pragma clang diagnostic pop
#endif

} // namespace filter
} // namespace hdf5
