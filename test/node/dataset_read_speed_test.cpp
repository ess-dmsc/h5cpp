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
#include <h5cpp/core/filesystem.hpp>
#include <h5cpp/dataspace/hyperslab.hpp>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/node/group.hpp>
#ifndef _MSC_VER
#include <sys/time.h>
#endif

using namespace hdf5;

#ifndef _MSC_VER

const static long long unsigned int xdim = 867;
const static long long unsigned int ydim = 700;
const static long long unsigned int nframe = 33;

double delta_time(const struct timeval& start, const struct timeval& stop) {
  return (double)(stop.tv_sec - start.tv_sec) +
         (double)(stop.tv_usec - start.tv_usec) * 0.000001;
}

hdf5::Dimensions current_dimensions(const hdf5::node::Dataset& dataset) {
  hdf5::dataspace::Simple dataspace(dataset.dataspace());
  return dataspace.current_dimensions();
}

using UShorts = std::vector<unsigned short int>;

static std::string filename = "dataset_read_speed.h5";

void create_initial_datafile() {
#if H5_VERSION_GE(1, 10, 0)
  property::FileCreationList fcpl;
  property::FileAccessList fapl;
  fapl.library_version_bounds(property::LibVersion::LATEST,
                              property::LibVersion::LATEST);
  file::File f =
      file::create(filename, file::AccessFlags::TRUNCATE, fcpl, fapl);
#else
  file::File f = file::create(filename, file::AccessFlags::TRUNCATE);
#endif
  property::DatasetCreationList dcpl;
  property::LinkCreationList lcpl;
  property::DatasetAccessList dapl;
  auto root = f.root();

  dataspace::Simple space{
      {0, xdim, ydim},
      {dataspace::Simple::UNLIMITED, dataspace::Simple::UNLIMITED,
       dataspace::Simple::UNLIMITED}};
  dcpl.layout(property::DatasetLayout::CHUNKED);
  dcpl.chunk({1, xdim, ydim});
  node::Dataset data(root, "data", datatype::create<unsigned short int>(),
                     space, lcpl, dcpl, dapl);
  UShorts frame(xdim * ydim);
  dataspace::Hyperslab framespace{{0, 0, 0}, {1, xdim, ydim}};
  for (long long unsigned int i = 0; i != nframe; i++) {
    data.extent(0, 1);
    framespace.offset({i, 0, 0});
    data.write(frame, framespace);
  }
}

SCENARIO("testing read performance") {
  create_initial_datafile();
  GIVEN("The data file with the data to read") {
    auto file = file::open(filename, file::AccessFlags::READONLY);
    auto dataset = file.root().get_dataset("/data");
    auto dims = current_dimensions(dataset);
    auto dtype = dataset.datatype();
    dataspace::Simple dspace = dataset.dataspace();
    UShorts buffer_all(dims[0] * dims[1] * dims[2]);
    UShorts buffer_selection(11 * dims[1] * dims[2]);
    BENCHMARK("selecting the entire dataset block") {
      hdf5::Dimensions frameoffset{0, 0, 0};
      hdf5::Dimensions frameblock{dims[0], dims[1], dims[2]};
      hdf5::dataspace::Hyperslab selected_frames{frameoffset, frameblock};
      return dataset.read(buffer_all, dtype, dspace, selected_frames);
    };
    BENCHMARK("reading the entire dataset") { return dataset.read(buffer_all); };
    BENCHMARK("reading 11 frames with a hyperslab and a memory dataspace of the correct rank") { 
      hdf5::dataspace::Hyperslab selection{{10, 0, 0}, {11, dims[1], dims[2]}};
      dataspace::Simple memory_dataspace(Dimensions({11, dims[1], dims[2]}));
      return dataset.read(buffer_selection, dtype, memory_dataspace, selection);
    };
    BENCHMARK("reading 11 frames with a default dataspace") { 
      hdf5::dataspace::Hyperslab selection{{10, 0, 0}, {11, dims[1], dims[2]}};
      return dataset.read(buffer_selection,  selection);
    };

  }

}
#endif
