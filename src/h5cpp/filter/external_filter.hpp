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

//!
//! \brief is filter available
//!
//! Checks if external filter is installed
//!
//! \param id the ID of the filter
//! \return status flag if the filter available
//!
DLL_EXPORT bool is_filter_available(FilterID id);

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

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
    //! \param name external filter name
    //!
    ExternalFilter(FilterID id,
                   const std::vector<unsigned int> cd_values,
                   const std::string &name=std::string());
    ExternalFilter();

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
                            Availability flag=Availability::Mandatory) const override;

    //!
    //! \brief compression options
    //!
    //! Provides compression options of the external filter
    //!
    //! \return compression options
    //!
    const std::vector<unsigned int> cd_values() const noexcept;
    //!
    //! \brief compression options
    //!
    //! Provides the external filter name
    //!
    //! \return filter name
    //!
    const std::string name() const noexcept;

  private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif
    std::vector<unsigned int> cd_values_;
    std::string name_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
};

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif
//!
//! \brief utility container for external filters
//!
//! This is a one to one derived type from std::vector in order to provide
//! a convenient container for external filters.
//! The interface is exactly the same as for std::vector.
//!
class DLL_EXPORT ExternalFilters : public std::vector<ExternalFilter> {
#ifdef _MSC_VER
#pragma warning(pop)
#endif
 public:

  //!
  //! \brief apply filter
  //!
  //! Fills a filter list with filters from a particular dataset creation property list.
  //!
  //! \throws std::runtime_error in case of a failure
  //! \param dcpl reference to the dataset creation property list
  //! \param max_cd_number maximal numer of cd_values
  //! \param max_name_size maximal fileter name size
  //! \return filter flags
  //!
  //!
  const std::vector<Availability> fill(const property::DatasetCreationList &dcpl,
				       size_t max_cd_number=16,
				       size_t max_name_size=257);
  //
  // pull in std::vector constructors
  //
  using std::vector<ExternalFilter>::vector;
};


} // namespace filter
} // namespace hdf5
