//
// (c) Copyright 2017 DESY,ESS
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
// Created on: Nov 17, 2017
//
#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

SCENARIO("testing a chunked dataset") {
  auto f = file::create("chunked_dataset_test.h5", file::AccessFlags::Truncate);
  auto type = datatype::create<int>();
  dataspace::Simple space{{0, 1024}, {dataspace::Simple::UNLIMITED, 1024}};

  WHEN("using a constructor") {
    node::ChunkedDataset dataset(f.root(), "data", type, space, {1024, 1024});
    THEN("we can check the dataset creation list") {
      property::DatasetCreationList dcpl = dataset.creation_list();
      REQUIRE(dcpl.layout() == property::DatasetLayout::Chunked);
    }
  }
}
