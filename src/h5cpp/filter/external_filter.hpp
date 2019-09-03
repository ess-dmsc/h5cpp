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
// Author: Jan Kotanski <jan.kotanski@desy.de>
// Created on: Sep 3, 2019
//
#pragma once

#include <h5cpp/filter/filter.hpp>

using FilterID = H5Z_filter_t;

namespace hdf5 {
namespace filter {

class DLL_EXPORT ExternalFilter : public Filter
{
  public:
    //!
    //! \brief construtor
    //!
    //! This constructor of External Filter.
    //!
    //! \param id the ID of the filter
    //! \param cd_values is a vector with compression options.
    //!
    ExternalFilter(FilterID id, const std::vector<unsigned int> cd_values);
    ExternalFilter() = delete;
    ~ExternalFilter();

    //!
    //! \brief apply filter
    //!
    //! Applies a filter to a particular dataset creation property list.
    //!
    //! \throws std::runtime_error in case of a failure
    //! \param dcpl reference to the dataset creation property list
    //! \param flag determines the availability requirement for a filter
    //!             which is \i mandatory by default.
    //!
    virtual void operator()(const property::DatasetCreationList &dcpl,
                            Availability flag=Availability::MANDATORY) const;

    //!
    //! \brief compression options
    //!
    //! Provdies compression options of the external filter
    //!
    //! \return compression options
    //!
    const std::vector<unsigned int> cd_values() const noexcept;

  private:
    const std::vector<unsigned int> cd_values_;
};


} // namespace filter
} // namespace hdf5
