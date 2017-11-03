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

#include <h5cpp/datatype/types.hpp>
#include "attribute_test_fixtures.hpp"
#include <vector>
#include <algorithm>
#include <h5cpp/attribute/attribute_iterator.hpp>

using namespace hdf5;

class AttributeName : public AttributeIterationFixture
{};

TEST_F(AttributeName, test_name_access)
{
  EXPECT_EQ(root_.attributes.size(),3ul);
  EXPECT_EQ(root_.attributes["index"].datatype().get_class(),
                    datatype::Class::INTEGER);
  EXPECT_EQ(root_.attributes["elasticity"].datatype().get_class(),
                    datatype::Class::FLOAT);
  EXPECT_EQ(root_.attributes["counter"].datatype().get_class(),
                    datatype::Class::INTEGER);

}

TEST_F(AttributeName, test_index_access_creation_order_increasing)
{
  EXPECT_EQ(root_.attributes.size(),3ul);
  root_.attributes.iterator_config().index(IterationIndex::CREATION_ORDER);
  root_.attributes.iterator_config().order(IterationOrder::INCREASING);

  EXPECT_EQ(root_.attributes[0].name(),"index");
  EXPECT_EQ(root_.attributes[1].name(),"elasticity");
  EXPECT_EQ(root_.attributes[2].name(),"counter");
}

TEST_F(AttributeName, test_iterator_access_creation_order_increasing)
{
  root_.attributes.iterator_config().index(IterationIndex::CREATION_ORDER);
  root_.attributes.iterator_config().order(IterationOrder::INCREASING);

  std::vector<std::string> ref_names{"index","elasticity","counter"};
  std::vector<std::string> names;

  std::transform(root_.attributes.begin(),
                 root_.attributes.end(),
                 std::back_inserter(names),
                 [](const attribute::Attribute &a) { return a.name();});
  EXPECT_EQ(names, ref_names);

}

TEST_F(AttributeName, test_index_access_creation_order_decreasing)
{
  EXPECT_EQ(root_.attributes.size(),3ul);
  root_.attributes.iterator_config().index(IterationIndex::CREATION_ORDER);
  root_.attributes.iterator_config().order(IterationOrder::DECREASING);

  EXPECT_EQ(root_.attributes[2].name(),"index");
  EXPECT_EQ(root_.attributes[1].name(),"elasticity");
  EXPECT_EQ(root_.attributes[0].name(),"counter");
}

TEST_F(AttributeName, test_iterator_access_creation_order_decreasing)
{
  root_.attributes.iterator_config().index(IterationIndex::CREATION_ORDER);
  root_.attributes.iterator_config().order(IterationOrder::DECREASING);

  std::vector<std::string> ref_names{"counter","elasticity","index"};
  auto iter = ref_names.begin();

  for(auto attribute: root_.attributes)
    EXPECT_EQ(attribute.name(),*iter++);

}

TEST_F(AttributeName, test_index_access_name_order_increasing)
{
  EXPECT_EQ(root_.attributes.size(),3ul);
  root_.attributes.iterator_config().index(IterationIndex::NAME);
  root_.attributes.iterator_config().order(IterationOrder::INCREASING);

  EXPECT_EQ(root_.attributes[2].name(),"index");
  EXPECT_EQ(root_.attributes[1].name(),"elasticity");
  EXPECT_EQ(root_.attributes[0].name(),"counter");
}

TEST_F(AttributeName, test_iterator_access_name_order_increasing)
{
  root_.attributes.iterator_config().index(IterationIndex::NAME);
  root_.attributes.iterator_config().order(IterationOrder::INCREASING);

  std::vector<std::string> ref_names{"counter","elasticity","index"};
  auto ref_iter = ref_names.begin();

  for(auto iter = root_.attributes.begin();iter!=root_.attributes.end();++iter,++ref_iter)
    EXPECT_EQ(iter->name(),*ref_iter);

}

TEST_F(AttributeName, test_index_access_name_order_decreasing)
{
  EXPECT_EQ(root_.attributes.size(),3ul);
  root_.attributes.iterator_config().index(IterationIndex::NAME);
  root_.attributes.iterator_config().order(IterationOrder::DECREASING);

  EXPECT_EQ(root_.attributes[0].name(),"index");
  EXPECT_EQ(root_.attributes[1].name(),"elasticity");
  EXPECT_EQ(root_.attributes[2].name(),"counter");
}

TEST_F(AttributeName, test_iterator_access_name_order_decreasing)
{
  root_.attributes.iterator_config().index(IterationIndex::NAME);
  root_.attributes.iterator_config().order(IterationOrder::DECREASING);

  std::vector<std::string> ref_names{"index","elasticity","counter"};
  auto ref_iter = ref_names.begin();

  auto iter     = root_.attributes.begin();
  auto iter_end = root_.attributes.end();
  while(iter!=iter_end)
  {
    EXPECT_EQ(iter++->name(),*ref_iter++);
  }
}

TEST_F(AttributeName, test_access_failure)
{
  EXPECT_THROW(root_.attributes[3],std::runtime_error);
  EXPECT_THROW(root_.attributes["hello"],std::runtime_error);
}
