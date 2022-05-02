//
// (c) Copyright 2017 DESY, ESS
//               2021 Eugen Wintersberger <eugen.wintersberger@gmail.com>
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
#pragma once
#include <vector>

class HKLPoint
{
  public:
    HKLPoint() = default;
    HKLPoint(int h,int k,int l);
    HKLPoint(const std::initializer_list<int> &init_list);
    HKLPoint(const HKLPoint &) = default;
    HKLPoint(HKLPoint &&) = default;

    int h() const noexcept;
    int k() const noexcept;
    int l() const noexcept;
  private:
    int h_{0};
    int k_{0};
    int l_{0};
};

bool operator==(const HKLPoint& lhs, const HKLPoint& rhs);
bool operator!=(const HKLPoint& lhl ,const HKLPoint& rhs);

class HKLPointList : public std::vector<HKLPoint>
{
  public:
    using std::vector<HKLPoint>::vector;
};

using HKLPoints = std::vector<HKLPointList>;
