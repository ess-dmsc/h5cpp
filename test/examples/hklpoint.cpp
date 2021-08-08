//
// (c) Copyright 2021 Eugen Wintersberger <eugen.wintersberger@gmail.com>
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
// Created on: Jan 10, 2021
//

#include "hklpoint.hpp"


HKLPoint::HKLPoint(int h, int k, int l) : h_(h), k_(k), l_(l) {}

HKLPoint::HKLPoint(const std::initializer_list<int>& init_list)
    : h_(0), k_(0), l_(0) {
  auto iter = init_list.begin();
  h_ = *iter++;
  k_ = *iter++;
  l_ = *iter;
}

int HKLPoint::h() const noexcept {
  return h_;
}

int HKLPoint::k() const noexcept {
  return k_;
}

int HKLPoint::l() const noexcept {
  return l_;
}

bool operator==(const HKLPoint& lhs, const HKLPoint& rhs) {
  return (lhs.h() == rhs.h()) && (lhs.k() == rhs.k()) && (lhs.l() == rhs.l());
}

bool operator!=(const HKLPoint& lhs, const HKLPoint& rhs) {
  return !(lhs == rhs);
}
