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

#include "attribute_test_fixtures.hpp"

using namespace hdf5;

class AttributeManagement : public AttributeIterationFixture
{};

TEST_F(AttributeManagement, test_remove_attribute_by_index)
{
  root_.attributes.iterator_config().index(IterationIndex::CREATION_ORDER);
  root_.attributes.iterator_config().order(IterationOrder::INCREASING);
  EXPECT_EQ(root_.attributes.size(),3ul);
  EXPECT_TRUE(root_.attributes.exists("index"));
  EXPECT_NO_THROW(root_.attributes.remove(0));
  EXPECT_EQ(root_.attributes.size(),2ul);
  EXPECT_FALSE(root_.attributes.exists("index"));
}

TEST_F(AttributeManagement, test_remove_attribute_by_name)
{
  EXPECT_EQ(root_.attributes.size(),3ul);
  EXPECT_TRUE(root_.attributes.exists("elasticity"));
  EXPECT_NO_THROW(root_.attributes.remove("elasticity"));
  EXPECT_FALSE(root_.attributes.exists("elasticity"));
  EXPECT_EQ(root_.attributes.size(),2ul);
}

TEST_F(AttributeManagement, test_remove_remains)
{
  EXPECT_EQ(root_.attributes.size(),3ul);
  attribute::Attribute a = root_.attributes["counter"];
  EXPECT_TRUE(a.is_valid());
  EXPECT_NO_THROW(root_.attributes.remove("counter"));
  EXPECT_FALSE(root_.attributes.exists("counter"));
  EXPECT_EQ(root_.attributes.size(),2ul);

  //however an already opened attribute remains alive
  EXPECT_TRUE(a.is_valid());
  EXPECT_EQ(a.name(),"counter");
}

TEST_F(AttributeManagement, test_remove_failure)
{
  EXPECT_THROW(root_.attributes.remove("hello"),
                    std::runtime_error);
  EXPECT_THROW(root_.attributes.remove(3),
                    std::runtime_error);
}

TEST_F(AttributeManagement, test_rename_attribute)
{
  attribute::Attribute a = root_.attributes["counter"];
  EXPECT_NO_THROW(root_.attributes.rename("counter","counter_2"));
  EXPECT_FALSE(root_.attributes.exists("counter"));
  EXPECT_TRUE(root_.attributes.exists("counter_2"));
  EXPECT_EQ(a.name(),"counter_2");
}

TEST_F(AttributeManagement, test_rename_failure)
{
  EXPECT_THROW(root_.attributes.rename("counter_2","hello"),
                    std::runtime_error);
}






