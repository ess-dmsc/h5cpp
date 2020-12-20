//
// (c) Copyright 2017 DESY,ESS
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
// Authors:
//         Eugen Wintersberger <eugen.wintersberger@desy.de>
//         Jan Kotanski <jan.kotanski@desy.de>
// Created on: Dec 20, 2020
//
#include <gtest/gtest.h>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

TEST(SZipTest,construction)
{
  filter::SZip filter;
  EXPECT_EQ(filter.id(),H5Z_FILTER_SZIP);
}

TEST(SZipTest,application)
{
  filter::SZip szip(filter::SZip::EC_OPTION_MASK,16);
  property::DatasetCreationList dcpl;

  filter::ExternalFilters filters;
  std::vector<unsigned int> cdvalues({133, 16});
  if(filter::is_filter_available(H5Z_FILTER_SZIP)){
    szip(dcpl);
    auto flags = filters.fill(dcpl);
    // EXPECT_EQ(H5Pget_nfilters(static_cast<hid_t>(dcpl)), 1);
    EXPECT_EQ(szip.id(), static_cast<int>(H5Z_FILTER_SZIP));
    EXPECT_EQ(szip.is_decoding_enabled(), true);
    EXPECT_EQ(szip.is_encoding_enabled(), true);
    
    EXPECT_EQ(dcpl.nfilters(), 1lu);
    EXPECT_EQ(filters.size(), 1lu);
    EXPECT_EQ(H5Pget_nfilters(static_cast<hid_t>(dcpl)),1);
    EXPECT_EQ(filters.size(), 1lu);
    EXPECT_EQ(flags.size(), 1lu);
    EXPECT_EQ(flags[0], filter::Availability::OPTIONAL);
    EXPECT_EQ(filters[0].cd_values(), cdvalues);
    EXPECT_EQ(filters[0].is_decoding_enabled(), true);
    EXPECT_EQ(filters[0].is_encoding_enabled(), true);
    EXPECT_EQ(filters[0].id(), static_cast<int>(H5Z_FILTER_SZIP));
    EXPECT_EQ(filters[0].name(), "szip");
    
  }
  EXPECT_EQ(szip.options_mask(), filter::SZip::EC_OPTION_MASK);
  EXPECT_EQ(szip.pixels_per_block(), 16);
  szip.options_mask(filter::SZip::NN_OPTION_MASK);
  EXPECT_EQ(szip.options_mask(), filter::SZip::NN_OPTION_MASK);
  szip.pixels_per_block(32);
  EXPECT_EQ(szip.pixels_per_block(), 32);
}
