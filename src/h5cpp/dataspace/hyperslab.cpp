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
#include <h5cpp/dataspace/hyperslab.hpp>
#include <h5cpp/error/error.hpp>

namespace hdf5 {
namespace dataspace {

#define THROW_IF_DEFAULT_CONSTRUCTED(msg)\
  if(rank()==0) \
  {\
    throw std::runtime_error(msg);\
  }

Hyperslab::Hyperslab() :
    Selection(),
    start_(),
    stride_(),
    count_(),
    block_() {}

Hyperslab::~Hyperslab() {}

Hyperslab::Hyperslab(size_t rank) :
    Selection(),
    start_(rank),
    stride_(rank),
    count_(rank),
    block_(rank) {
  std::fill(start_.begin(), start_.end(), 0);
  std::fill(stride_.begin(), stride_.end(), 1);
  std::fill(block_.begin(), block_.end(), 0);
  std::fill(count_.begin(), count_.end(), 0);
}

Hyperslab::Hyperslab(const Dimensions &offset,
                     const Dimensions &block,
                     const Dimensions &count,
                     const Dimensions &stride) :
    Selection(),
    start_(offset),
    stride_(stride),
    count_(count),
    block_(block) {}

Hyperslab::Hyperslab(const Dimensions &offset, const Dimensions &block) :
    Selection(),
    start_(offset),
    stride_(offset.size()),
    count_(offset.size()),
    block_(block) {
  std::fill(stride_.begin(), stride_.end(), 1ul);
  std::fill(count_.begin(), count_.end(), 1ul);
}

Hyperslab::Hyperslab(const Dimensions &offset, const Dimensions &count,
                     const Dimensions &stride) :
    Selection(),
    start_(offset),
    stride_(stride),
    count_(count),
    block_(offset.size()) {
  std::fill(block_.begin(), block_.end(), 1ul);
}

size_t Hyperslab::rank() const noexcept {
  return start_.size();
}

void Hyperslab::offset(size_t index, size_t value) {
  THROW_IF_DEFAULT_CONSTRUCTED("Cannot set start value for a default "
                                   "constructed Hyperslab!")
  check_dimension_index(index, "start");

  start_[index] = value;
}

void Hyperslab::offset(const Dimensions &values) {
  THROW_IF_DEFAULT_CONSTRUCTED("Cannot set start values for a default "
                                   "constructed Hyperslab!")

  check_container_size(values, "start");
  start_ = values;
}

const Dimensions &Hyperslab::offset() const {
  THROW_IF_DEFAULT_CONSTRUCTED("Cannot get start values for a default "
                                   "constructed Hyperslab!")
  return start_;
}

void Hyperslab::stride(size_t index, size_t value) {
  THROW_IF_DEFAULT_CONSTRUCTED("Cannot set stride value for a default "
                                   "constructed Hyperslab!")
  check_dimension_index(index, "stride");

  stride_[index] = value;
}

void Hyperslab::stride(const Dimensions &values) {
  THROW_IF_DEFAULT_CONSTRUCTED("Cannot set stride values for a default "
                                   "constructed Hyperslab!")
  check_container_size(values, "stride");
  stride_ = values;
}

const Dimensions &Hyperslab::stride() const {
  THROW_IF_DEFAULT_CONSTRUCTED("Cannot get stride values for a default "
                                   "constructed Hyperslab!")
  return stride_;
}

void Hyperslab::count(size_t index, size_t value) {
  THROW_IF_DEFAULT_CONSTRUCTED("Cannot set count value for a default "
                                   "constructed Hyperslab!")
  check_dimension_index(index, "count");

  count_[index] = value;
}

void Hyperslab::count(const Dimensions &values) {
  THROW_IF_DEFAULT_CONSTRUCTED("Cannot set count values for a default "
                                   "constructed Hyperslab!")
  check_container_size(values, "count");
  count_ = values;
}

const Dimensions &Hyperslab::count() const {
  THROW_IF_DEFAULT_CONSTRUCTED("Cannot get count values for a default "
                                   "constructed Hyperslab!")
  return count_;
}

void Hyperslab::block(size_t index, size_t value) {
  THROW_IF_DEFAULT_CONSTRUCTED("Cannot set block value for a default "
                                   "constructed Hyperslab!")
  check_dimension_index(index, "block");
  block_[index] = value;
}

void Hyperslab::block(const Dimensions &values) {
  THROW_IF_DEFAULT_CONSTRUCTED("Cannot set block values for a default "
                                   "constructed Hyperslab!")
  check_container_size(values, "block");
  block_ = values;

}

const Dimensions &Hyperslab::block() const {
  THROW_IF_DEFAULT_CONSTRUCTED("Cannot get block values for a default "
                                   "constructed Hyperslab!")
  return block_;
}

void Hyperslab::apply(const Dataspace &space, SelectionOperation ops) const {
  if (H5Sselect_hyperslab(static_cast<hid_t>(space),
                          static_cast<H5S_seloper_t>(ops),
                          start_.data(), stride_.data(), count_.data(),
                          block_.data()) < 0) {
    error::Singleton::instance().throw_with_stack("Failure applying hyperslab selection to the "
                                                      "dataspace");
  }
}

SelectionType Hyperslab::type() const {
  return SelectionType::Hyperslab;
}

size_t Hyperslab::size() const {
  if(rank() == 0)
    return 0;
  size_t size = 1ul;
  Dimensions dims = block();
  Dimensions cnt = count();
  for(Dimensions::size_type i = 0; i != dims.size(); i++)
    size *= dims[i] * cnt[i];
  return size;
}

Dimensions Hyperslab::dimensions() const {
  Dimensions dims = block();
  Dimensions cnt = count();
  for(Dimensions::size_type i = 0; i != dims.size(); i++)
    dims[i] *= cnt[i];
  return dims;
}

Dataspace operator||(const Dataspace &space, const Hyperslab &selection) {
  Dataspace new_space(space);
  new_space.selection(SelectionOperation::Set, selection);
  return new_space;
}

SelectionList operator|(const Hyperslab &a, const Hyperslab &b) {
  return {{SelectionOperation::Set, Selection::SharedPointer(new Hyperslab(a))},
          {SelectionOperation::Or, Selection::SharedPointer(new Hyperslab(b))}
  };
}

SelectionList &operator|(SelectionList &selections, const Hyperslab &b) {
  selections.push_back({SelectionOperation::Set,
                        Selection::SharedPointer(new Hyperslab(b))});
  return selections;
}

} // namespace dataspace
} // namespace hdf5
