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

namespace { 
static const long long unsigned int xdim = 867;
static const long long unsigned int ydim = 700;
static const long long unsigned int sxdim = 17;
static const long long unsigned int nframe = 33;

using UShorts = std::vector<unsigned short int>;

/**
 * @brief create a Simple dataspace with unlimited dimension
 * 
 * @param current the current dimensions for the dataspace
 * @return hdf5::dataspace::Simple new instance
 */
static hdf5::dataspace::Simple unlimited_space(const hdf5::Dimensions& current) {
  using hdf5::dataspace::Simple;
  hdf5::Dimensions limits(current.size());
  std::fill(std::begin(limits), std::end(limits), Simple::unlimited);

  return Simple(current, limits);
}

}


SCENARIO("testing dataset access via chunks") {
#if H5_VERSION_GE(1, 10, 0)
  property::FileCreationList fcpl;
  property::FileAccessList fapl;
  fapl.library_version_bounds(property::LibVersion::Latest,
                              property::LibVersion::Latest);
  auto f = file::create("dataset_direct_chunk.h5", file::AccessFlags::Truncate,
                        fcpl, fapl);
#else
  auto f = file::create("dataset_direct_chunk.h5", file::AccessFlags::Truncate);
#endif
  auto root = f.root();
  auto space = unlimited_space({0, xdim, ydim});
  auto sspace = unlimited_space({0, sxdim});
  auto smemspace = unlimited_space({sxdim});
  auto memspace = unlimited_space({xdim, ydim});

  property::LinkCreationList lcpl;
  property::DatasetAccessList dapl;
  property::DatasetTransferList dtpl;
  property::DatasetCreationList dcpl;
  dcpl.layout(property::DatasetLayout::Chunked);
  dcpl.chunk({1, xdim, ydim});

  UShorts frame(xdim * ydim);
  std::generate(frame.begin(), frame.end(), std::rand);

  dataspace::Hyperslab framespace{{0, 0, 0}, {1, xdim, ydim}};
  dataspace::Hyperslab sframespace{{0, 0}, {1, sxdim}};

  UShorts sframe(sxdim);
  for (size_t i = 0; i != sxdim; i++)
    sframe[i] = static_cast<unsigned short>(i / 2);

  UShorts tframe(sxdim);
  for (size_t i = 0; i != sxdim; i++)
    tframe[i] = static_cast<unsigned short>(i / 4);

  GIVEN("an integer dataset") {
    node::Dataset dataset(root, "data1", datatype::create<unsigned short int>(),
                          space, lcpl, dcpl, dapl);
    WHEN("writting the data with with_chunk") {
      for (long long unsigned int i = 0; i != nframe; i++) {
        dataset.extent(0, 1);
        dataset.write_chunk(frame, {i, 0, 0});
      }
      THEN("we can read the data back with selections") {
        UShorts read_value(xdim * ydim);
        for (long long unsigned int i = 0; i != nframe; i++) {
          framespace.offset({i, 0, 0});
          dataset.read(read_value, framespace);
          REQUIRE(frame == read_value);
        }
      }
    }
  }

#if H5_VERSION_GE(1, 10, 2)
  GIVEN("a new dataset") { 

  }
/*

TEST_F(DatasetDirectChunkTest, read_chunk) {
  auto dtype = datatype::create<unsigned short int>();
  node::Dataset data2 =
      node::Dataset(root, "data2", datatype::create<unsigned short int>(),
                    space, lcpl, dcpl, dapl);

  for (long long unsigned int i = 0; i != nframe; i++) {
    data2.extent(0, 1);
    framespace.offset({i, 0, 0});
    dataspace::Dataspace file_space = data2.dataspace();
    file_space.selection(dataspace::SelectionOperation::Set, framespace);
    data2.write(frame, dtype, memspace, file_space, dtpl);
  }

  std::vector<unsigned short int> read_value(xdim * ydim);
  std::uint32_t filter_mask = 0;

  for (long long unsigned int i = 0; i != nframe; i++) {
    filter_mask = data2.read_chunk(read_value, {i, 0, 0});
    EXPECT_EQ(frame, read_value);
    EXPECT_EQ(filter_mask, property::kDefault);
  }
}

TEST_F(DatasetDirectChunkTest, read_chunk_deflate) {
  auto dtype = datatype::create<unsigned short int>();
  property::DatasetCreationList dcpl;
  filter::Deflate filter(2u);
  filter(dcpl);
  dcpl.layout(property::DatasetLayout::Chunked);
  dcpl.chunk({1, sxdim});
  node::Dataset data3 =
      node::Dataset(root, "data3", datatype::create<unsigned short int>(),
                    sspace, lcpl, dcpl, dapl);

  for (long long unsigned int i = 0; i != nframe; i++) {
    data3.extent(0, 1);
    sframespace.offset({i, 0});
    dataspace::Dataspace file_space = data3.dataspace();
    file_space.selection(dataspace::SelectionOperation::Set, sframespace);
    if (i % 2)
      data3.write(sframe, dtype, smemspace, file_space, dtpl);
    else
      data3.write(tframe, dtype, smemspace, file_space, dtpl);
  }

  long long unsigned int tcxdim = data3.chunk_storage_size({0, 0});
  long long unsigned int scxdim = data3.chunk_storage_size({1, 0});
  std::vector<unsigned short int> sread_value(scxdim / 2);
  std::vector<unsigned short int> tread_value(tcxdim / 2);
  std::vector<unsigned short int> scpvalue = {
      24184, 49677, 4609,  12288, 49156, 6832, 65478, 44127,
      151,   40580, 42322, 55254, 14696, 2563, 16640};

  std::vector<unsigned short int> tcpvalue = {24184, 24675, 128,   1606,
                                              25608, 32866, 26176, 2054,
                                              24932, 0,     20993, 7424};
  std::uint32_t filter_mask = 0;

  for (long long unsigned int i = 0; i != nframe; i++) {
    if (i % 2) {
      filter_mask = data3.read_chunk(sread_value, {i, 0});
      EXPECT_EQ(scpvalue, sread_value);
    } else {
      filter_mask = data3.read_chunk(tread_value, {i, 0});
      EXPECT_EQ(tcpvalue, tread_value);
    }

    EXPECT_EQ(filter_mask, property::kDefault);
  }
}
*/
#endif
}

/*
TEST_F(DatasetDirectChunkTest, write_chunk_deflate) {
  auto dtype = datatype::create<unsigned short int>();
  property::DatasetCreationList dcpl;
  filter::Deflate filter(2u);
  filter(dcpl);
  dcpl.layout(property::DatasetLayout::Chunked);
  dcpl.chunk({1, sxdim});
  node::Dataset data4 =
      node::Dataset(root, "data4", datatype::create<unsigned short int>(),
                    sspace, lcpl, dcpl, dapl);

  std::vector<unsigned short int> scpframe = {
      24184, 49677, 4609,  12288, 49156, 6832, 65478, 44127,
      151,   40580, 42322, 55254, 14696, 2563, 16640};

  std::vector<unsigned short int> tcpframe = {24184, 24675, 128,   1606,
                                              25608, 32866, 26176, 2054,
                                              24932, 0,     20993, 7424};

  for (long long unsigned int i = 0; i != nframe; i++) {
    data4.extent(0, 1);
    if (i % 2)
      data4.write_chunk(scpframe, {i, 0});
    else
      data4.write_chunk(tcpframe, {i, 0});
  }
  std::vector<unsigned short int> read_value(sxdim);

  for (long long unsigned int i = 0; i != nframe; i++) {
    sframespace.offset({i, 0});
    data4.read(read_value, sframespace);
    if (i % 2)
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
*/
