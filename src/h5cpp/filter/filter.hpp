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

#include <h5cpp/property/dataset_creation.hpp>
#include <h5cpp/filter/types.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace filter {

//!
//! \brief abstract filter class
//!
//! Base class for all filters. These classes are primarily intended to allow
//! easy configuration of filters. They basically only store the fitlers
//! parameters and apply them to the dataset creation property list.
//!
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif
class DLL_EXPORT Filter
{
  public:
    //!
    //! \brief default constructor
    //!
    //! Required for compliance with STL containers. Can use the default
    //! implementation.
    //!
    Filter();
    Filter(const Filter&) = default;
    virtual ~Filter();

    //!
    //! \brief apply filter
    //!
    //! Applies a filter to a particular dataset creation property list.
    //!
    //! \throws std::runtime_error in case of a failure
    //! \param dcpl reference to the dataset creation property list
    //! \param flag determines the availability requirement for a filter
    //!             which is \e mandatory by default.
    //!
    virtual void operator()(const property::DatasetCreationList &dcpl,
                            Availability flag = Availability::Mandatory) const = 0;

    //!
    //! \brief get the ID of the filter
    //!
    //! Return the actual ID of a filter. As we do not store any particular
    //! HDF5 state in this class this function does not throw and is a
    //! constexpr.
    //!
    FilterID id() const noexcept;

    //!
    //! \brief get the the config flag if encoding enabled
    //!
    //! Return the actual config encoding enabled flag of the filter.
    //!
    virtual bool is_encoding_enabled() const;

    //!
    //! \brief get the the config flag if decoding enabled
    //!
    //! Return the actual config decoding enabled flag of the filter.
    //!
    virtual bool is_decoding_enabled() const;

  protected:
    //!
    //! \brief construtor
    //!
    //! This constructor is protected and only intended to be used by
    //! child classes of Filter.
    //!
    //! \param id the ID of the filter
    Filter(FilterID id);

  private:
    FilterID id_;
};
#ifdef __clang__
#pragma clang diagnostic pop
#endif


} // namespace filter
} // namespace hdf5
