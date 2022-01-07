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
// Created on: Nov 13, 2017
//

#include <h5cpp/dataspace/view.hpp>
#include <h5cpp/error/error.hpp>
#include <h5cpp/core/utilities.hpp>

namespace hdf5 {
namespace dataspace {

void View::clear() const {
  if (H5Sselect_all(static_cast<hid_t>(space_)) < 0) {
    error::Singleton::instance().throw_with_stack("Failure selecting all elements in the dataspace!");
  }
}

void View::apply(const SelectionList &selections) const {
  for (auto swo: selections)
    swo.selection->apply(space_, swo.operation);
}

View::View(const Dataspace &space) :
    space_(space) {}

View::View(const Dataspace &space, const SelectionList &selections) :
    space_(space) {
  apply(selections);
}

View::View(const Dataspace &space, const Hyperslab &selection) :
    space_(space) {
  SelectionList selections{{SelectionOperation::Set,
                            Selection::SharedPointer(new Hyperslab(selection))}};

  apply(selections);
}

void View::operator()(const SelectionList &selections) const {
  clear();
  apply(selections);
}

void View::operator()(const Hyperslab &slab) const {
  clear();
  SelectionList selections{{SelectionOperation::Set,
                            Selection::SharedPointer(new Hyperslab(slab))}};

  apply(selections);
}

size_t View::size() const {
  hssize_t s = H5Sget_select_npoints(static_cast<hid_t>(space_));
  if (s < 0) {
    error::Singleton::instance().throw_with_stack("Failure retrieving selection size!");
  }
  return signed2unsigned<size_t>(s);
}

} // namespace dataspace
} // namespace hdf5
