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
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Nov 29, 2020
//
#include <cstdlib>

template <typename T>
struct TypeTrait {
  size_t size = 0;
};

#define TYPE_TRAIT(t, s) \
  template <>            \
  struct TypeTrait<t> {  \
    size_t size = s;     \
  }

TYPE_TRAIT(char, 1);
TYPE_TRAIT(unsigned char, 1);
TYPE_TRAIT(short, 2);
TYPE_TRAIT(unsigned short, 2);
TYPE_TRAIT(int, 4);
TYPE_TRAIT(unsigned int, 4);
TYPE_TRAIT(long, 8);
TYPE_TRAIT(unsigned long, 8);
TYPE_TRAIT(long long, 16);
TYPE_TRAIT(unsigned long long, 16);
TYPE_TRAIT(float, 4);
TYPE_TRAIT(double, 8);
TYPE_TRAIT(long double, 16);
