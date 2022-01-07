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
#include <h5cpp/dataspace/selection_manager.hpp>
#include <h5cpp/dataspace/dataspace.hpp>
#include <h5cpp/dataspace/selection.hpp>
#include <h5cpp/error/error.hpp>
#include <h5cpp/core/utilities.hpp>
#include <cassert>

namespace hdf5 {
namespace dataspace {

SelectionManager::SelectionManager(Dataspace &space) :
    space_(space) {}

void SelectionManager::operator()(SelectionOperation op, const Selection &selection) const {
  selection.apply(space_, op);
}

size_t SelectionManager::size() const {
  hssize_t s = H5Sget_select_npoints(static_cast<hid_t>(space_));
  if (s < 0) {
    error::Singleton::instance().throw_with_stack("Failure retrieving selection size!");
  }
  return signed2unsigned<size_t>(s);
}

SelectionType SelectionManager::type() const {
  switch (H5Sget_select_type(static_cast<hid_t>(space_))) {
    case H5S_SEL_ERROR:return SelectionType::None;
    case H5S_SEL_NONE:return SelectionType::None;
    case H5S_SEL_POINTS:return SelectionType::Points;
    case H5S_SEL_HYPERSLABS:return SelectionType::Hyperslab;
    case H5S_SEL_ALL:return SelectionType::All;
    case H5S_SEL_N:assert(false); // Added H5S_SEL_N to silence compiler
  }
  return {};
}

void SelectionManager::all() const {
  if (H5Sselect_all(static_cast<hid_t>(space_)) < 0) {
    error::Singleton::instance().throw_with_stack("Failure selecting all elements in the dataspace!");
  }
}

void SelectionManager::none() const {
  if (H5Sselect_none(static_cast<hid_t>(space_)) < 0) {
    error::Singleton::instance().throw_with_stack("Failure deselecting all elements in the dataspace!");
  }
}

} // namespace dataspace
} // namespace hdf5
