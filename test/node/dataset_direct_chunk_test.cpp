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
#include <h5cpp/node/dataset.hpp>
#include <boost/filesystem.hpp>

using namespace hdf5;
namespace fs = boost::filesystem;

struct DatasetDirectChunkTest : public testing::Test
{
  long long unsigned int xdim = 867;
  long long unsigned int ydim = 700;
  long long unsigned int nframe = 33;
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

  DatasetDirectChunkTest()
  {
#if H5_VERSION_GE(1, 10, 0)
    property::FileCreationList fcpl;
    property::FileAccessList fapl;
    fapl.library_version_bounds(property::LibVersion::LATEST,
                                property::LibVersion::LATEST);
    f = file::create("dataset_direct_chunk.h5", file::AccessFlags::TRUNCATE, fcpl, fapl);
#else
    f = file::create("dataset_direct_chunk.h5", file::AccessFlags::TRUNCATE);
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
  }
};

TEST_F(DatasetDirectChunkTest, write_chunk)
{

  auto dtype = datatype::create<unsigned short int>();
  node::Dataset data1 = node::Dataset(root,
				      "data1",
				      datatype::create<unsigned short int>(),
				      space, lcpl, dcpl, dapl);

  for(long long unsigned int i = 0; i != nframe; i++){
    data1.extent(0, 1);
    data1.write_chunk(frame, {i, 0, 0});
  }

  std::vector<unsigned short int> read_value(xdim * ydim);

  for(long long unsigned int i = 0; i != nframe; i++){
    data1.extent(0, 1);
    framespace.offset({i, 0, 0});
    data1.read(read_value, framespace);
    EXPECT_EQ(frame, read_value);
  }
}


#if H5_VERSION_GE(1,10,2)

TEST_F(DatasetDirectChunkTest, read_chunk)
{

  auto dtype = datatype::create<unsigned short int>();
  node::Dataset data2 = node::Dataset(root,
				      "data2",
				      datatype::create<unsigned short int>(),
				      space, lcpl, dcpl, dapl);

  for(long long unsigned int i = 0; i != nframe; i++){
    data2.extent(0, 1);
    framespace.offset({i, 0, 0});
    dataspace::Dataspace file_space = data2.dataspace();
    file_space.selection(dataspace::SelectionOperation::SET, framespace);
    data2.write(frame, dtype, memspace, file_space, dtpl);
  }

  std::vector<unsigned short int> read_value(xdim * ydim);

  for(long long unsigned int i = 0; i != nframe; i++){
    data2.read_chunk(read_value, {i, 0, 0});
    EXPECT_EQ(frame, read_value);
  }
}

#endif
