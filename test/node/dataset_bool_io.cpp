//
// (c) Copyright 2017 DESY,ESS
//               2021 Eugen Wintersberger <eugen.wintersberger@gmail.com>
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
// Author: Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Oct 24, 2017
//
#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

SCENARIO("testing bool IO") {
  auto f = file::create("DatasetBoolIO.h5", file::AccessFlags::Truncate);
  auto r = f.root();
  auto type = hdf5::datatype::create<bool>();
  hdf5::dataspace::Scalar space;

  GIVEN("a dataset of type bool") {
    auto d = node::Dataset(r, Path("data"), type, space);
    THEN("we can write a boolean value to it") {
      bool write = true;
      REQUIRE_NOTHROW(d.write(write));
      AND_THEN("we can read the value back") {
        bool read = false;
        REQUIRE_NOTHROW(d.read(read));
        REQUIRE(read);
      }
    }
  }
}
