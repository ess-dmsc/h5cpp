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
// Author: Jan Kotanski <jan.kotanski@desy.de>
//         Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Nov 12, 2018
//
#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;


SCENARIO("writing dataset with external filter blosclz") {
#if H5_VERSION_GE(1, 10, 0)
  property::FileCreationList fcpl;
  property::FileAccessList fapl;
  fapl.library_version_bounds(property::LibVersion::Latest,
                              property::LibVersion::Latest);
  auto f = file::create("dataset_external_filter.h5", file::AccessFlags::Truncate,
                        fcpl, fapl);
#else
  auto f = file::create("dataset_external_filter.h5", file::AccessFlags::Truncate);
#endif
  auto root = f.root();

  const long long unsigned int xdim = 867;
  const long long unsigned int ydim = 700;
  const long long unsigned int nframe = 33;

  // external filter
  const unsigned int FILTER_BLOSC=32001;
  std::vector<unsigned int> cd_values(7,0);
  /* 0 to 3 (inclusive) param slots are reserved. */
  cd_values[4] = 4;       /* compression level */
  cd_values[5] = 0;       /* 0: shuffle not active, 1: shuffle active */
  cd_values[6] = 0; /* the actual compressor to use, 0: BLOSC_BLOSCLZ */

  filter::ExternalFilter blosc_filter(FILTER_BLOSC, cd_values);

  dataspace::Simple space{{0, xdim, ydim},{dataspace::Simple::unlimited, xdim, ydim}};
  property::LinkCreationList lcpl;
  property::DatasetAccessList dapl;
  property::DatasetTransferList dtpl;
  property::DatasetCreationList dcpl;
  dcpl.layout(property::DatasetLayout::Chunked);
  dcpl.chunk({1, xdim, ydim});
  blosc_filter(dcpl);


  std::vector<int> frame(xdim * ydim, 0);
  std::generate(frame.begin(), frame.end(), [](){return static_cast<int>(std::rand() % 100);});

  dataspace::Hyperslab framespace{{0, 0, 0}, {1, xdim, ydim}};

  GIVEN("an integer dataset") {
    node::Dataset dataset(root, "data1", datatype::create<int>(),
                          space, lcpl, dcpl, dapl);
    WHEN("writing the data with external filter") {
      for (long long unsigned int i = 0; i != nframe; i++) {
        dataset.extent(0, 1);
        framespace.offset(0,i);
        dataset.write(frame, framespace);
      }
      THEN("read the data back") {
        std::vector<int> read_value(xdim * ydim);
        for (long long unsigned int i = 0; i != nframe; i++) {
          framespace.offset({i, 0, 0});
          dataset.read(read_value, framespace);
          REQUIRE(frame == read_value);
          ;
        }
      }
    }
  }
}