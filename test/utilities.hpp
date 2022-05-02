//
// (c) Copyright 2017 DESY, ESS
//               2020 Eugen Wintersberger <eugen.wintersberger@gmail.com>
//
// This file is part of h5pp.
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
//   Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: 7 Dec, 2020
//
#pragma once
#include <h5cpp/core/object_handle.hpp>

template <typename T>
hid_t to_hid(T&& object) {
  return static_cast<hid_t>(object);
}

/**
 * @brief Utility function closing an object
 *
 * @tparam T type to close
 * @param object const reference to an object
 */
template <typename T>
void close(const T& object) {
  hdf5::ObjectHandle(to_hid(object)).close();
}

#include <vector>

using UChars = std::vector<unsigned char>;

