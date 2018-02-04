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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 28, 2017
//

#include <gtest/gtest.h>
#include <boost/test/floating_point_comparison.hpp>
#include <h5cpp/property/dataset_creation.hpp>
#include <h5cpp/datatype/factory.hpp>

namespace prop = hdf5::property;
namespace type = hdf5::datatype;

TEST(DatasetCreationList, FillSetValues)
{
  std::stringstream stream;

  stream.str(std::string());
  stream << prop::DatasetFillValueStatus::UNDEFINED;
  EXPECT_EQ(stream.str(), "UNDEFINED");

  stream.str(std::string());
  stream << prop::DatasetFillValueStatus::DEFAULT;
  EXPECT_EQ(stream.str(), "DEFAULT");

  stream.str(std::string());
  stream << prop::DatasetFillValueStatus::USER_DEFINED;
  EXPECT_EQ(stream.str(), "USER_DEFINED");
}

TEST(DatasetCreationList, FillTime)
{
  std::stringstream stream;

  stream.str(std::string());
  stream << prop::DatasetFillTime::IFSET;
  EXPECT_EQ(stream.str(), "IFSET");

  stream.str(std::string());
  stream << prop::DatasetFillTime::ALLOC;
  EXPECT_EQ(stream.str(), "ALLOC");

  stream.str(std::string());
  stream << prop::DatasetFillTime::NEVER;
  EXPECT_EQ(stream.str(), "NEVER");
}

TEST(DatasetCreationList, AllocationTime)
{
  std::stringstream stream;

  stream.str(std::string());
  stream << prop::DatasetAllocTime::DEFAULT;
  EXPECT_EQ(stream.str(), "DEFAULT");

  stream.str(std::string());
  stream << prop::DatasetAllocTime::EARLY;
  EXPECT_EQ(stream.str(), "EARLY");

  stream.str(std::string());
  stream << prop::DatasetAllocTime::INCR;
  EXPECT_EQ(stream.str(), "INCR");

  stream.str(std::string());
  stream << prop::DatasetAllocTime::LATE;
  EXPECT_EQ(stream.str(), "LATE");
}

TEST(DatasetCreationList, Layout)
{
  std::stringstream stream;

  stream.str(std::string());
  stream << prop::DatasetLayout::COMPACT;
  EXPECT_EQ(stream.str(), "COMPACT");

  stream.str(std::string());
  stream << prop::DatasetLayout::CONTIGUOUS;
  EXPECT_EQ(stream.str(), "CONTIGUOUS");

  stream.str(std::string());
  stream << prop::DatasetLayout::CHUNKED;
  EXPECT_EQ(stream.str(), "CHUNKED");

#if H5_VERSION_GE(1, 10, 0)
  stream.str(std::string());
  stream << prop::DatasetLayout::VIRTUAL;
  EXPECT_EQ(stream.str(), "VIRTUAL");
#endif
}

TEST(DatasetCreationList, test_construction)
{
  prop::DatasetCreationList pl;
  EXPECT_TRUE(pl.get_class() == prop::kDatasetCreate);
  EXPECT_EQ(pl.layout(), prop::DatasetLayout::CONTIGUOUS);
  EXPECT_EQ(pl.fill_time(), prop::DatasetFillTime::IFSET);
  EXPECT_EQ(pl.allocation_time(), prop::DatasetAllocTime::LATE);
  EXPECT_EQ(pl.fill_value_status(), prop::DatasetFillValueStatus::DEFAULT);

  auto cl = prop::kDatasetCreate;
  EXPECT_NO_THROW((prop::DatasetCreationList(hdf5::ObjectHandle(H5Pcreate(static_cast<hid_t>(cl))))));

  cl = prop::kGroupCreate;
  EXPECT_THROW((prop::DatasetCreationList(hdf5::ObjectHandle(H5Pcreate(static_cast<hid_t>(cl))))),
               std::runtime_error);
}

TEST(DatasetCreationList, test_layout)
{
  prop::DatasetCreationList pl;
  EXPECT_EQ(pl.layout(), prop::DatasetLayout::CONTIGUOUS);
  EXPECT_NO_THROW(pl.layout(prop::DatasetLayout::CHUNKED));
  EXPECT_EQ(pl.layout(), prop::DatasetLayout::CHUNKED);
  EXPECT_NO_THROW(pl.layout(prop::DatasetLayout::COMPACT));
  EXPECT_EQ(pl.layout(), prop::DatasetLayout::COMPACT);

#if H5_VERSION_GE(1, 10, 0)
  EXPECT_NO_THROW(pl.layout(prop::DatasetLayout::VIRTUAL));
  EXPECT_EQ(pl.layout(), prop::DatasetLayout::VIRTUAL);
#endif

  hdf5::ObjectHandle(static_cast<hid_t>(pl)).close();
  EXPECT_THROW(pl.layout(prop::DatasetLayout::CHUNKED), std::runtime_error);
  EXPECT_THROW(pl.layout(), std::runtime_error);
}

TEST(DatasetCreationList, test_chunk)
{
  prop::DatasetCreationList pl;
  EXPECT_NO_THROW(pl.chunk({10, 100}));

  hdf5::Dimensions c = pl.chunk();
  hdf5::Dimensions e{10, 100};
//  EXPECT_EQ_COLLECTIONS(c.begin(),c.end(),e.begin(),e.end());
  EXPECT_EQ(c, e);

  hdf5::ObjectHandle(static_cast<hid_t>(pl)).close();
  EXPECT_THROW(pl.chunk({1}), std::runtime_error);
  EXPECT_THROW(pl.chunk(), std::runtime_error);
}

TEST(DatasetCreationList, test_fill_time)
{
  prop::DatasetCreationList pl;
  EXPECT_EQ(pl.fill_time(), prop::DatasetFillTime::IFSET);
  EXPECT_NO_THROW(pl.fill_time(prop::DatasetFillTime::ALLOC));
  EXPECT_EQ(pl.fill_time(), prop::DatasetFillTime::ALLOC);
  EXPECT_NO_THROW(pl.fill_time(prop::DatasetFillTime::NEVER));
  EXPECT_EQ(pl.fill_time(), prop::DatasetFillTime::NEVER);

  hdf5::ObjectHandle(static_cast<hid_t>(pl)).close();
  EXPECT_THROW(pl.fill_time(prop::DatasetFillTime::IFSET), std::runtime_error);
  EXPECT_THROW(pl.fill_time(), std::runtime_error);
}

TEST(DatasetCreationList, test_allocation_time)
{
  prop::DatasetCreationList pl;
  EXPECT_EQ(pl.allocation_time(), prop::DatasetAllocTime::LATE);
  EXPECT_NO_THROW(pl.allocation_time(prop::DatasetAllocTime::DEFAULT));
  EXPECT_EQ(pl.allocation_time(), prop::DatasetAllocTime::LATE);
  EXPECT_NO_THROW(pl.allocation_time(prop::DatasetAllocTime::EARLY));
  EXPECT_EQ(pl.allocation_time(), prop::DatasetAllocTime::EARLY);
  EXPECT_NO_THROW(pl.allocation_time(prop::DatasetAllocTime::INCR));
  EXPECT_EQ(pl.allocation_time(), prop::DatasetAllocTime::INCR);

  hdf5::ObjectHandle(static_cast<hid_t>(pl)).close();
  EXPECT_THROW(pl.allocation_time(prop::DatasetAllocTime::LATE), std::runtime_error);
  EXPECT_THROW(pl.allocation_time(), std::runtime_error);
}

TEST(DatasetCreationList, test_fill_value_default)
{
  prop::DatasetCreationList pl;
  EXPECT_NO_THROW(pl.fill_value(1024));
  EXPECT_EQ(pl.fill_value<int>(), 1024);
  EXPECT_EQ(pl.fill_value_status(), prop::DatasetFillValueStatus::USER_DEFINED);

  hdf5::ObjectHandle(static_cast<hid_t>(pl)).close();
  EXPECT_THROW(pl.fill_value(1024), std::runtime_error);
  EXPECT_THROW(pl.fill_value_status(), std::runtime_error);
}

TEST(DatasetCreationList, test_fill_value_custom_type)
{
  prop::DatasetCreationList pl;
  auto set_type = type::create<int>();
  auto get_type = type::create<float>();

  EXPECT_NO_THROW(pl.fill_value(1024, set_type));
  float buffer;
  EXPECT_NO_THROW(buffer = pl.fill_value<float>(get_type));
  EXPECT_NEAR(buffer, float(1024), 0.0001);
}



