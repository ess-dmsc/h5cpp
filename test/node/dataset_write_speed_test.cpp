//
// (c) Copyright 2017 DESY,ESS
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
// Created on: Nov 12, 2018
//

#include <gtest/gtest.h>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/node/group.hpp>
#include <h5cpp/dataspace/hyperslab.hpp>
#include <h5cpp/core/filesystem.hpp>
#ifndef _MSC_VER
#include <sys/time.h>
#endif

using namespace hdf5;

struct DatasetWriteSpeedTest : public testing::Test
{
  unsigned long long xdim = 867;
  unsigned long long ydim = 700;
  unsigned long long nframe = 33;
  hdf5::file::File f;
  hdf5::node::Group root;
  hdf5::dataspace::Simple space;
  hdf5::dataspace::Simple fullspace;
  hdf5::dataspace::Simple memspace;
  property::DatasetCreationList dcpl;
  property::LinkCreationList lcpl;
  property::DatasetAccessList dapl;
  std::vector<unsigned short int> frame;
  std::vector<unsigned short int> allframes;

  dataspace::Hyperslab framespace;
  property::DatasetTransferList dtpl;

  DatasetWriteSpeedTest()
  {
#if H5_VERSION_GE(1, 10, 0)
    property::FileCreationList fcpl;
    property::FileAccessList fapl;
    fapl.library_version_bounds(property::LibVersion::LATEST,
                                property::LibVersion::LATEST);
    f = file::create("dataset_write_speed.h5", file::AccessFlags::TRUNCATE, fcpl, fapl);
#else
    f = file::create("dataset_write_speed.h5", file::AccessFlags::TRUNCATE);
#endif
    root = f.root();
    space =  {{0, xdim, ydim}, {dataspace::Simple::UNLIMITED,
				dataspace::Simple::UNLIMITED,
				dataspace::Simple::UNLIMITED}};
    fullspace =  {{nframe, xdim, ydim}, {dataspace::Simple::UNLIMITED,
				dataspace::Simple::UNLIMITED,
				dataspace::Simple::UNLIMITED}};
    memspace = {{xdim, ydim}, {dataspace::Simple::UNLIMITED,
			       dataspace::Simple::UNLIMITED}};

    dcpl.layout(property::DatasetLayout::CHUNKED);
    dcpl.chunk({1, xdim, ydim});
    frame = std::vector<unsigned short int>(xdim * ydim);
    std::generate(frame.begin(), frame.end(), std::rand);
    framespace = dataspace::Hyperslab({{0, 0, 0}, {1, xdim, ydim}});

    allframes = std::vector<unsigned short int>(nframe * xdim * ydim);
    std::generate(allframes.begin(), allframes.end(), std::rand);
  }

protected:
  virtual void SetUp()
  {
    }

  virtual void TearDown() {
    fs::remove("dataset_write_speed.h5");
  }
};

#ifndef _MSC_VER
TEST_F(DatasetWriteSpeedTest, write_hyperslab)
{
  struct timeval stime1;
  struct timeval etime1;
  struct timeval stime0;
  struct timeval etime0;

  auto dtype = datatype::create<unsigned short int>();
  node::Dataset data0 = node::Dataset(root, "data0", dtype, space, lcpl, dcpl, dapl);
  gettimeofday(&stime0, NULL);
  for(unsigned long long i = 0; i != nframe; i++){
    data0.extent(0, 1);
    framespace.offset({i, 0, 0});
    dataspace::Dataspace file_space = data0.dataspace();
    file_space.selection(dataspace::SelectionOperation::SET, framespace);
    data0.write(frame, dtype, memspace, file_space, dtpl);
  }
  gettimeofday(&etime0, NULL);

  node::Dataset data1 = node::Dataset(root,
				      "data1",
				      datatype::create<unsigned short int>(),
				      space,lcpl,dcpl,dapl);


  gettimeofday(&stime1, NULL);

  for(unsigned long long i = 0; i != nframe; i++){
    data1.extent(0, 1);
    framespace.offset({i, 0, 0});

    data1.write(frame, framespace);
  }
  gettimeofday(&etime1, NULL);

  double time0 = (double)(etime0.tv_sec - stime0.tv_sec)
    + (double)(etime0.tv_usec - stime0.tv_usec)*0.000001;
  double time1 = (double)(etime1.tv_sec - stime1.tv_sec)
    + (double)(etime1.tv_usec - stime1.tv_usec)*0.000001;

  // std::cerr << time0 <<  std::endl;
  // std::cerr << time1 <<  std::endl;
  EXPECT_GT(14 * time1, time0);
  EXPECT_GT(14 * time0, time1);

  std::vector<unsigned short int> read_value(xdim * ydim);

  for(unsigned long long i = 0; i != nframe; i++){
    data1.extent(0, 1);
    framespace.offset({i, 0, 0});
    data1.read(read_value, framespace);
    EXPECT_EQ(frame, read_value);
  }

}


TEST_F(DatasetWriteSpeedTest, write)
{
  struct timeval stime1;
  struct timeval etime1;
  struct timeval stime0;
  struct timeval etime0;

  auto dtype = datatype::create<unsigned short int>();
  node::Dataset data2 = node::Dataset(root, "data2", dtype, space, lcpl, dcpl, dapl);
  gettimeofday(&stime0, NULL);
  for(unsigned long long i = 0; i != nframe; i++){
    data2.extent(0, 1);
    framespace.offset({i, 0, 0});
    dataspace::Dataspace file_space = data2.dataspace();
    file_space.selection(dataspace::SelectionOperation::SET, framespace);
    data2.write(frame, dtype, memspace, file_space, dtpl);
  }
  gettimeofday(&etime0, NULL);

  node::Dataset data3 = node::Dataset(root,
				      "data3",
				      datatype::create<unsigned short int>(),
				      fullspace, lcpl, dcpl, dapl);

  gettimeofday(&stime1, NULL);

  data3.write(allframes);
  gettimeofday(&etime1, NULL);

  double time0 = (double)(etime0.tv_sec - stime0.tv_sec)
    + (double)(etime0.tv_usec - stime0.tv_usec)*0.000001;
  double time1 = (double)(etime1.tv_sec - stime1.tv_sec)
    + (double)(etime1.tv_usec - stime1.tv_usec)*0.000001;

  // std::cerr << time0 <<  std::endl;
  // std::cerr << time1 <<  std::endl;
  EXPECT_GT(14 * time1, time0);
  EXPECT_GT(14 * time0, time1);

  std::vector<unsigned short int> read_value(xdim * ydim);

  for(unsigned long long i = 0; i != nframe; i++){
    data3.extent(0, 1);
    framespace.offset({i, 0, 0});
    data3.read(read_value, framespace);
    auto first = allframes.begin() + i * xdim * ydim;
    auto last = allframes.begin() + (i + 1) * xdim * ydim;
    std::vector<unsigned short int> buffer(first, last);
    EXPECT_EQ(buffer, read_value);
  }

}

#endif
