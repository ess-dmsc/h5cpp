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
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 25, 2017
//
#include <h5cpp/dataspace/selection.hpp>
#include <h5cpp/error/error.hpp>

namespace hdf5 {
namespace dataspace {

Selection::~Selection() {}

Dataspace operator||(const Dataspace &space, const SelectionList &selections) {
  Dataspace new_space(space);

  for (auto swo: selections)
    new_space.selection(swo.operation, *swo.selection);

  return new_space;
}

} // namespace dataspace
} // namespace hdf5
