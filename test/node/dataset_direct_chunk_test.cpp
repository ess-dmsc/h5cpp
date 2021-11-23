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
#include <h5cpp/hdf5.hpp>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/node/group.hpp>
#include <h5cpp/dataspace/hyperslab.hpp>
#include <h5cpp/node/dataset.hpp>
#include <h5cpp/core/filesystem.hpp>

using namespace hdf5;

struct DatasetDirectChunkTest : public testing::Test
{
  unsigned long long xdim = 867;
  unsigned long long ydim = 700;
  unsigned long long sxdim = 17;
  unsigned long long nframe = 33;
  hdf5::file::File f;
  hdf5::node::Group root;
  hdf5::dataspace::Simple space;
  hdf5::dataspace::Simple sspace;
  hdf5::dataspace::Simple memspace;
  hdf5::dataspace::Simple smemspace;
  property::DatasetCreationList dcpl;
  property::LinkCreationList lcpl;
  property::DatasetAccessList dapl;
  std::vector<unsigned short int> frame;
  std::vector<unsigned short int> sframe;
  std::vector<unsigned short int> tframe;

  dataspace::Hyperslab framespace;
  dataspace::Hyperslab sframespace;
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
    memspace = {{xdim, ydim}, {dataspace::Simple::UNLIMITED,
			       dataspace::Simple::UNLIMITED}};

    dcpl.layout(property::DatasetLayout::CHUNKED);
    dcpl.chunk({1, xdim, ydim});
    frame = std::vector<unsigned short int>(xdim * ydim);
    std::generate(frame.begin(), frame.end(), std::rand);
    framespace = dataspace::Hyperslab({{0, 0, 0}, {1, xdim, ydim}});

    sframe = std::vector<unsigned short int>(sxdim);
    for(size_t i = 0; i != sxdim; i++)
      sframe[i] = static_cast<int>(i / 2);
    tframe = std::vector<unsigned short int>(sxdim);
    for(size_t i = 0; i != sxdim; i++)
      tframe[i] = static_cast<int>(i / 4);

    sspace =  {{0, sxdim}, {dataspace::Simple::UNLIMITED,
			   dataspace::Simple::UNLIMITED}};
    sframespace = dataspace::Hyperslab({{0, 0}, {1, sxdim}});
    smemspace = {{sxdim}, {dataspace::Simple::UNLIMITED}};
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

  for(unsigned long long i = 0; i != nframe; i++){
    data1.extent(0, 1);
    data1.write_chunk(frame, {i, 0, 0});
  }

  std::vector<unsigned short int> read_value(xdim * ydim);

  for(unsigned long long i = 0; i != nframe; i++){
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

  for(unsigned long long i = 0; i != nframe; i++){
    data2.extent(0, 1);
    framespace.offset({i, 0, 0});
    dataspace::Dataspace file_space = data2.dataspace();
    file_space.selection(dataspace::SelectionOperation::SET, framespace);
    data2.write(frame, dtype, memspace, file_space, dtpl);
  }

  std::vector<unsigned short int> read_value(xdim * ydim);
  std::uint32_t filter_mask = 0;


  for(unsigned long long i = 0; i != nframe; i++){
    filter_mask = data2.read_chunk(read_value, {i, 0, 0});
    EXPECT_EQ(frame, read_value);
    EXPECT_EQ(filter_mask, H5P_DEFAULT);
  }
}

TEST_F(DatasetDirectChunkTest, read_chunk_deflate)
{

  auto dtype = datatype::create<unsigned short int>();
  property::DatasetCreationList dcpl;
  filter::Deflate filter(2u);
  filter(dcpl);
  dcpl.layout(property::DatasetLayout::CHUNKED);
  dcpl.chunk({1, sxdim});
  node::Dataset data3 = node::Dataset(root,
  				      "data3",
  				      datatype::create<unsigned short int>(),
  				      sspace, lcpl, dcpl, dapl);

  for(unsigned long long i = 0; i != nframe; i++){
    data3.extent(0, 1);
    sframespace.offset({i, 0});
    dataspace::Dataspace file_space = data3.dataspace();
    file_space.selection(dataspace::SelectionOperation::SET, sframespace);
    if(i % 2)
      data3.write(sframe, dtype, smemspace, file_space, dtpl);
    else
      data3.write(tframe, dtype, smemspace, file_space, dtpl);
  }

  unsigned long long tcxdim = data3.chunk_storage_size({0, 0});
  unsigned long long scxdim= data3.chunk_storage_size({1, 0});
  std::vector<unsigned short int> sread_value(scxdim/2);
  std::vector<unsigned short int> tread_value(tcxdim/2);
  std::vector<unsigned short int> scpvalue =  {
					       24184, 49677, 4609, 12288, 49156, 6832,
					       65478, 44127, 151, 40580, 42322, 55254,
					       14696, 2563, 16640};

  std::vector<unsigned short int> tcpvalue =  { 24184, 24675, 128, 1606, 25608, 32866,
						26176, 2054, 24932, 0, 20993, 7424};
  std::uint32_t filter_mask = 0;

  for(unsigned long long i = 0; i != nframe; i++){
    if(i % 2)
      {
	filter_mask = data3.read_chunk(sread_value, {i, 0});
	EXPECT_EQ(scpvalue, sread_value);
      }
    else
      {
	filter_mask = data3.read_chunk(tread_value, {i, 0});
	EXPECT_EQ(tcpvalue, tread_value);
      }

    EXPECT_EQ(filter_mask, H5P_DEFAULT);
  }
}

#endif

TEST_F(DatasetDirectChunkTest, write_chunk_deflate)
{

  auto dtype = datatype::create<unsigned short int>();
  property::DatasetCreationList dcpl;
  filter::Deflate filter(2u);
  filter(dcpl);
  dcpl.layout(property::DatasetLayout::CHUNKED);
  dcpl.chunk({1, sxdim});
  node::Dataset data4 = node::Dataset(root,
				      "data4",
				      datatype::create<unsigned short int>(),
				      sspace, lcpl, dcpl, dapl);


  std::vector<unsigned short int> scpframe =  {24184, 49677, 4609, 12288, 49156, 6832,
					       65478, 44127, 151, 40580, 42322, 55254,
					       14696, 2563, 16640};

  std::vector<unsigned short int> tcpframe =  {24184, 24675, 128, 1606, 25608, 32866,
					       26176, 2054, 24932, 0, 20993, 7424};


  for(unsigned long long i = 0; i != nframe; i++){
    data4.extent(0, 1);
    if(i % 2)
      data4.write_chunk(scpframe, {i, 0});
    else
      data4.write_chunk(tcpframe, {i, 0});
  }
  std::vector<unsigned short int> read_value(sxdim);

  for(unsigned long long i = 0; i != nframe; i++){
    sframespace.offset({i, 0});
    data4.read(read_value, sframespace);
    if(i % 2)
      EXPECT_EQ(sframe, read_value);
    else
      EXPECT_EQ(tframe, read_value);
  }

  auto filters = data4.filters();
  std::vector<unsigned int> cdvalues({2u});
  EXPECT_EQ(filters.size(), 1lu);
  EXPECT_EQ(filters[0].cd_values(), cdvalues);
  EXPECT_EQ(filters[0].id(), static_cast<int>(H5Z_FILTER_DEFLATE));
  EXPECT_EQ(filters[0].name(), "deflate");

}
