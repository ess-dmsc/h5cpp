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

SCENARIO("testing read performance") {
#if H5_VERSION_GE(1, 10, 0)
  property::FileCreationList fcpl;
  property::FileAccessList fapl;
  fapl.library_version_bounds(property::LibVersion::LATEST,
                              property::LibVersion::LATEST);
  file::File f = file::create("dataset_read_speed.h5",
                              file::AccessFlags::TRUNCATE, fcpl, fapl);
#else
  file::File f =
      file::create("dataset_read_speed.h5", file::AccessFlags::TRUNCATE);
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

  GIVEN("the timepoints") {
    double time0, time1;
    AND_GIVEN("a new datafile") {
      auto f0 =
          file::open("dataset_read_speed.h5", file::AccessFlags::READONLY);
      auto r0 = f0.root();
      auto d0 = r0.get_dataset("/data");
      auto dims = current_dimensions(d0);
      auto dtype = d0.datatype();
      UShorts buffer(dims[0] * dims[1] * dims[2]);

      WHEN("selecting the entire dataset block") {
        hdf5::Dimensions frameoffset{0, 0, 0};
        hdf5::Dimensions frameblock{dims[0], dims[1], dims[2]};
        hdf5::dataspace::Hyperslab selected_frames{frameoffset, frameblock};
        dataspace::Simple dspace = d0.dataspace();
        struct timeval start, stop;
        gettimeofday(&start, NULL);
        d0.read(buffer, dtype, dspace, selected_frames);
        gettimeofday(&stop, NULL);
        time0 = delta_time(start,stop);
      }
      WHEN("reading the entire dataset") {
        struct timeval start, stop;
        gettimeofday(&start, NULL);
        d0.read(buffer);
        gettimeofday(&stop, NULL);
        time1 = delta_time(start, stop);
      }
    }
    THEN("we expect") {
      UNSCOPED_INFO("reading with selection "<<time0);
      UNSCOPED_INFO("reading without selection "<<time1);
      REQUIRE(14 * time1 > time0);
      REQUIRE(14 * time0 > time1);
    }
  }

  /*
  TEST_F(DatasetReadSpeedTest, read_hyperslab) {
    struct timeval stime1;
    struct timeval etime1;
    struct timeval stime0;
    struct timeval etime0;

    file::File f0 =
        file::open("dataset_read_speed.h5", file::AccessFlags::READONLY);
    auto root0 = f0.root();
    auto dataset0 = root0.get_dataset("/data");
    hdf5::dataspace::Simple dataspace(dataset0.dataspace());
    const auto dims = dataspace.current_dimensions();
    std::vector<unsigned short int> buffer(11 * dims[1] * dims[2]);
    auto datatype = dataset0.datatype();

    hdf5::Dimensions frameoffset{10, 0, 0};
    hdf5::Dimensions frameblock{11, dims[1], dims[2]};
    hdf5::dataspace::Hyperslab selected_frames{frameoffset, frameblock};
    dataspace::Simple dataspace0(Dimensions({11, dims[1], dims[2]}));
    // time0
    gettimeofday(&stime0, NULL);
    dataset0.read(buffer, datatype, dataspace0, selected_frames);
    gettimeofday(&etime0, NULL);
    f0.close();

    file::File f1 =
        file::open("dataset_read_speed.h5", file::AccessFlags::READONLY);
    auto root1 = f1.root();
    auto dataset1 = root1.get_dataset("/data");
    // time1
    gettimeofday(&stime1, NULL);
    dataset1.read(buffer, selected_frames);
    gettimeofday(&etime1, NULL);
    f1.close();

    double time0 = delta_time(stime0, etime0);
    double time1 = delta_time(stime1, etime1);

    EXPECT_GT(14 * time1, time0);
    EXPECT_GT(14 * time0, time1);
  }
  */
}
#endif
