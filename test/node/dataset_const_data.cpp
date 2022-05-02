//
// (c) Copyright 2017 DESY,ESS
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
// Author: Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Oct 23, 2017
//
#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>
#include <array>
#include <cstdint>
#include <h5cpp/contrib/stl/array.hpp>

using namespace hdf5;

template<class Type>
void constData() {
  std::array<const Type,1> SomeData{0};
  node::Dataset dset;
  dset.write(SomeData);
}

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-prototypes"
#endif
void DoNotRun() {
  constData<std::int8_t>();
  constData<std::uint8_t>();
  constData<std::int16_t>();
  constData<std::uint16_t>();
  constData<std::int32_t>();
  constData<std::uint32_t>();
  constData<std::int64_t>();
  constData<std::uint64_t>();
  constData<double>();
  constData<float>();
  constData<char>();
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
