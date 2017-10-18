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
// Created on: Oct 5, 2017
//

#include <gtest/gtest.h>
#include "attribute_test_fixtures.hpp"

using namespace hdf5;

BOOST_AUTO_TEST_SUITE(AttributeTest)

BOOST_FIXTURE_TEST_SUITE(AttributeManagementTest,AttributeIterationFixture)

TEST(TestName,test_remove_attribute_by_index)
{
  root_group.attributes.iterator_config().index(IterationIndex::CREATION_ORDER);
  root_group.attributes.iterator_config().order(IterationOrder::INCREASING);
  EXPECT_EQ(root_group.attributes.size(),3);
  EXPECT_TRUE(root_group.attributes.exists("index"));
  EXPECT_NO_THROW(root_group.attributes.remove(0));
  EXPECT_EQ(root_group.attributes.size(),2);
  EXPECT_FALSE(root_group.attributes.exists("index"));
}

TEST(TestName,test_remove_attribute_by_name)
{
  EXPECT_EQ(root_group.attributes.size(),3);
  EXPECT_TRUE(root_group.attributes.exists("elasticity"));
  EXPECT_NO_THROW(root_group.attributes.remove("elasticity"));
  EXPECT_FALSE(root_group.attributes.exists("elasticity"));
  EXPECT_EQ(root_group.attributes.size(),2);
}

TEST(TestName,test_remove_remains)
{
  EXPECT_EQ(root_group.attributes.size(),3);
  attribute::Attribute a = root_group.attributes["counter"];
  EXPECT_TRUE(a.is_valid());
  EXPECT_NO_THROW(root_group.attributes.remove("counter"));
  EXPECT_FALSE(root_group.attributes.exists("counter"));
  EXPECT_EQ(root_group.attributes.size(),2);

  //however an already opened attribute remains alive
  EXPECT_TRUE(a.is_valid());
  EXPECT_EQ(a.name(),"counter");
}

TEST(TestName,test_remove_failure)
{
  EXPECT_THROW(root_group.attributes.remove("hello"),
                    std::runtime_error);
  EXPECT_THROW(root_group.attributes.remove(3),
                    std::runtime_error);
}

TEST(TestName,test_rename_attribute)
{
  attribute::Attribute a = root_group.attributes["counter"];
  EXPECT_NO_THROW(root_group.attributes.rename("counter","counter_2"));
  EXPECT_FALSE(root_group.attributes.exists("counter"));
  EXPECT_TRUE(root_group.attributes.exists("counter_2"));
  EXPECT_EQ(a.name(),"counter_2");
}

TEST(TestName,test_rename_failure)
{
  EXPECT_THROW(root_group.attributes.rename("counter_2","hello"),
                    std::runtime_error);
}






