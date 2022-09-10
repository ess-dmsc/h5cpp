//
// (c) Copyright 2021 eugen.wintersberger@gmail.com, DESY, ESS
//
// This file is part of h5cpp
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
//
// ===========================================================================
//
// Created on: Aug 8, 2021
//     Author: Eugen Wintersberger <eugen.wintersberger@gmail.com>
//
#pragma once

#include <limits>
#include <type_traits>
#include <utility>
#include <stdexcept>

/**
 * @brief convert unsigned to signed integers
 * 
 * This operation shows up quite often in the library and causes warnings for 
 * virtually all compilers. This template function tries to provide a clean
 * implementation of such a conversion and throws an error if it would fail.
 * 
 * Compile time errors are produced if the types are 
 * 
 * @tparam TType the unsigned source type
 * @tparam SType signed target type
 * @param source_value universal reference to the unsigned source value
 * @return new instance of TType 
 * @throw std::range_error if the source value does not fit into the positive 
 *                         range of the target signed integer
 */
template<typename TType, typename SType>
TType unsigned2signed(SType &&source_value) { 
  using stripped_source_t = typename std::remove_reference<SType>::type;
  using stripped_target_t = typename std::remove_reference<TType>::type;
  // provide compile time errors if types are not appropriate
  static_assert(std::is_integral<stripped_target_t>::value &&
                std::is_signed<stripped_target_t>::value,
                "target type must be a signed integral type");
  static_assert(std::is_integral<stripped_source_t>::value && 
                std::is_unsigned<stripped_source_t>::value, 
                "source type must be an unsigned integral type");

  using target_limits = std::numeric_limits<stripped_target_t>;
  // if the source value is smaller than the maximum positive value of the 
  // signed target type
  if(source_value <= static_cast<stripped_source_t>(target_limits::max())) {
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsign-conversion"
#endif
    return static_cast<TType>(std::forward<SType>(source_value));
#ifdef __clang__
#pragma clang diagnostic pop
#endif
  } else { 
    throw std::range_error("unsigned source value is too large for signed type");
  }
}

template<typename TType, typename SType>
TType signed2unsigned(SType &&source_value) { 
  using stripped_source_t = typename std::remove_reference<SType>::type;
  using stripped_target_t = typename std::remove_reference<TType>::type;
  // provide compile time errors if types are not appropriate
  static_assert(std::is_integral<stripped_source_t>::value &&
                std::is_signed<stripped_source_t>::value,
                "source type must be an unsigned integral type");
  static_assert(std::is_integral<stripped_target_t>::value && 
                std::is_unsigned<stripped_target_t>::value, 
                "target type must be a signed integral type");

  using target_limits = std::numeric_limits<stripped_target_t>;
  if(source_value < 0) { 
	  throw std::range_error("input value is < 0 -> cannot be converted to unsigned");
  }
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wsign-conversion"
#endif
  if(static_cast<stripped_target_t>(source_value) <= target_limits::max()) {
	  return static_cast<stripped_target_t>(std::forward<SType>(source_value));
#ifdef __clang__
#pragma clang diagnostic pop
#endif
  } else { 
	  throw std::range_error("signed input value does not fit into the requested unsigned target type");
  }

}
