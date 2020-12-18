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
// Created on: Sep 3, 2019
//
#include <gtest/gtest.h>

#include <h5cpp/hdf5.hpp>

using namespace hdf5;

TEST(ExternalFilterTest, lz4_construction)
{
  const unsigned int FILTER_LZ4 = 32004;
  filter::ExternalFilter filter(FILTER_LZ4, {0u, 0u});
  EXPECT_EQ(filter.id(), static_cast<int>(FILTER_LZ4));
  std::vector<unsigned int> cdvalues({0u, 0u});
  EXPECT_EQ(filter.cd_values(), cdvalues);
}

TEST(ExternalFilterTest, bitshufflelz4_construction)
{
  property::DatasetCreationList dcpl;
  const unsigned int FILTER_BITSHUFFLE = 32008;
  std::vector<unsigned int> cdvalues({0u, 2u});
  filter::ExternalFilter bfilter(FILTER_BITSHUFFLE, {0u, 2u});

  EXPECT_EQ(bfilter.cd_values(), cdvalues);
  EXPECT_EQ(bfilter.id(), static_cast<int>(FILTER_BITSHUFFLE));
  if(filter::is_filter_available(FILTER_BITSHUFFLE)){
    EXPECT_NO_THROW(bfilter(dcpl));

    filter::ExternalFilters filters;
    auto flags = filters.fill(dcpl);
    EXPECT_EQ(filters.size(), 1lu);
    EXPECT_EQ(flags.size(), 1lu);
    EXPECT_EQ(flags[0], filter::Availability::MANDATORY);
    EXPECT_EQ(filters[0].cd_values(), cdvalues);
    EXPECT_EQ(filters[0].id(), static_cast<int>(FILTER_BITSHUFFLE));
    EXPECT_EQ(filters[0].name(),
	      "bitshuffle; see https://github.com/kiyo-masui/bitshuffle");
  }
}

TEST(ExternalFilterTest, deflate_application)
{
  property::DatasetCreationList dcpl;
  std::vector<unsigned int> cdvalues({8u});
  filter::ExternalFilter filter(H5Z_FILTER_DEFLATE, {8u});

  filter(dcpl);
  filter::ExternalFilters filters;
  auto flags = filters.fill(dcpl);
  // EXPECT_EQ(H5Pget_nfilters(static_cast<hid_t>(dcpl)), 1);
  EXPECT_EQ(filters.size(), 1lu);
  EXPECT_EQ(flags.size(), 1lu);
  EXPECT_EQ(flags[0], filter::Availability::MANDATORY);
  EXPECT_EQ(filters[0].cd_values(), cdvalues);
  EXPECT_EQ(filters[0].id(), static_cast<int>(H5Z_FILTER_DEFLATE));
  EXPECT_EQ(filters[0].name(), "deflate");
}
