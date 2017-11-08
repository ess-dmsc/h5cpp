
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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Aug 17, 2017
//
#include <gtest/gtest.h>
#include <h5cpp/property/group_creation.hpp>
#include <h5cpp/property/property_class.hpp>

namespace pl = hdf5::property;

TEST(GroupCreationList, test_construction)
{
  pl::GroupCreationList gcpl;
  EXPECT_TRUE(gcpl.get_class()==pl::kGroupCreate);
}

TEST(GroupCreationList, test_local_heap_size_hint)
{
  pl::GroupCreationList gcpl;
  EXPECT_NO_THROW(gcpl.local_heap_size_hint(1024));
  EXPECT_EQ(gcpl.local_heap_size_hint(),1024ul);

  EXPECT_NO_THROW(gcpl.local_heap_size_hint(512ul));
  EXPECT_EQ(gcpl.local_heap_size_hint(),512ul);
}

TEST(GroupCreationList, test_estimated_number_of_links)
{
  pl::GroupCreationList gcpl;
  EXPECT_NO_THROW(gcpl.estimated_number_of_links(10));
  EXPECT_EQ(gcpl.estimated_number_of_links(),10ul);
  EXPECT_NO_THROW(gcpl.estimated_number_of_links(33));
  EXPECT_EQ(gcpl.estimated_number_of_links(),33ul);

}

TEST(GroupCreationList, test_estimated_link_name_length)
{
  pl::GroupCreationList gcpl;
  EXPECT_NO_THROW(gcpl.estimated_link_name_length(100));
  EXPECT_EQ(gcpl.estimated_link_name_length(),100ul);

  EXPECT_NO_THROW(gcpl.estimated_link_name_length(64));
  EXPECT_EQ(gcpl.estimated_link_name_length(),64ul);
}

TEST(GroupCreationList, test_link_creation_order)
{
  pl::GroupCreationList gcpl;
  EXPECT_NO_THROW(gcpl.link_creation_order(pl::CreationOrder().enable_indexed()));
  pl::CreationOrder flags = gcpl.link_creation_order();
  EXPECT_TRUE(flags.tracked());
  EXPECT_TRUE(flags.indexed());

  EXPECT_NO_THROW(gcpl.link_creation_order(pl::CreationOrder().enable_tracked()));
  flags = gcpl.link_creation_order();
  EXPECT_TRUE(flags.tracked());
  EXPECT_FALSE(flags.indexed());

}

TEST(GroupCreationList, test_link_storage_threshold)
{
  pl::GroupCreationList gcpl;
  EXPECT_NO_THROW(gcpl.link_storage_thresholds(100,60));
  EXPECT_EQ(gcpl.link_storage_maximum_compact(),100ul);
  EXPECT_EQ(gcpl.link_storage_minimum_dense(),60ul);

  EXPECT_THROW(gcpl.link_storage_thresholds(60,100),std::runtime_error);
}
