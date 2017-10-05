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
#include <boost/test/unit_test.hpp>
#include <h5cpp/datatype/types.hpp>
#include "attribute_test_fixtures.hpp"
#include <vector>
#include <algorithm>
#include <h5cpp/attribute/attribute_iterator.hpp>

using namespace hdf5;

BOOST_AUTO_TEST_SUITE(AttributeTest)

BOOST_FIXTURE_TEST_SUITE(AttributeAccessTest,AttributeIterationFixture)

BOOST_AUTO_TEST_CASE(test_name_access)
{
  BOOST_CHECK_EQUAL(root_group.attributes.size(),3);
  BOOST_CHECK_EQUAL(root_group.attributes["index"].datatype().get_class(),
                    datatype::Class::INTEGER);
  BOOST_CHECK_EQUAL(root_group.attributes["elasticity"].datatype().get_class(),
                    datatype::Class::FLOAT);
  BOOST_CHECK_EQUAL(root_group.attributes["counter"].datatype().get_class(),
                    datatype::Class::INTEGER);

}

BOOST_AUTO_TEST_CASE(test_index_access_creation_order_increasing)
{
  BOOST_CHECK_EQUAL(root_group.attributes.size(),3);
  root_group.attributes.iterator_config().index(IterationIndex::CREATION_ORDER);
  root_group.attributes.iterator_config().order(IterationOrder::INCREASING);

  BOOST_CHECK_EQUAL(root_group.attributes[0].name(),"index");
  BOOST_CHECK_EQUAL(root_group.attributes[1].name(),"elasticity");
  BOOST_CHECK_EQUAL(root_group.attributes[2].name(),"counter");
}

BOOST_AUTO_TEST_CASE(test_iterator_access_creation_order_increasing)
{
  root_group.attributes.iterator_config().index(IterationIndex::CREATION_ORDER);
  root_group.attributes.iterator_config().order(IterationOrder::INCREASING);

  std::vector<std::string> ref_names{"index","elasticity","counter"};
  std::vector<std::string> names;

  std::transform(root_group.attributes.begin(),
                 root_group.attributes.end(),
                 std::back_inserter(names),
                 [](const attribute::Attribute &a) { return a.name();});
  BOOST_CHECK_EQUAL_COLLECTIONS(names.begin(),names.end(),
                                ref_names.begin(),ref_names.end());

}

BOOST_AUTO_TEST_CASE(test_index_access_creation_order_decreasing)
{
  BOOST_CHECK_EQUAL(root_group.attributes.size(),3);
  root_group.attributes.iterator_config().index(IterationIndex::CREATION_ORDER);
  root_group.attributes.iterator_config().order(IterationOrder::DECREASING);

  BOOST_CHECK_EQUAL(root_group.attributes[2].name(),"index");
  BOOST_CHECK_EQUAL(root_group.attributes[1].name(),"elasticity");
  BOOST_CHECK_EQUAL(root_group.attributes[0].name(),"counter");
}

BOOST_AUTO_TEST_CASE(test_iterator_access_creation_order_decreasing)
{
  root_group.attributes.iterator_config().index(IterationIndex::CREATION_ORDER);
  root_group.attributes.iterator_config().order(IterationOrder::DECREASING);

  std::vector<std::string> ref_names{"counter","elasticity","index"};
  auto iter = ref_names.begin();

  for(auto attribute: root_group.attributes)
    BOOST_CHECK_EQUAL(attribute.name(),*iter++);

}

BOOST_AUTO_TEST_CASE(test_index_access_name_order_increasing)
{
  BOOST_CHECK_EQUAL(root_group.attributes.size(),3);
  root_group.attributes.iterator_config().index(IterationIndex::NAME);
  root_group.attributes.iterator_config().order(IterationOrder::INCREASING);

  BOOST_CHECK_EQUAL(root_group.attributes[2].name(),"index");
  BOOST_CHECK_EQUAL(root_group.attributes[1].name(),"elasticity");
  BOOST_CHECK_EQUAL(root_group.attributes[0].name(),"counter");
}

BOOST_AUTO_TEST_CASE(test_iterator_access_name_order_increasing)
{
  root_group.attributes.iterator_config().index(IterationIndex::NAME);
  root_group.attributes.iterator_config().order(IterationOrder::INCREASING);

  std::vector<std::string> ref_names{"counter","elasticity","index"};
  auto ref_iter = ref_names.begin();

  for(auto iter = root_group.attributes.begin();iter!=root_group.attributes.end();++iter,++ref_iter)
    BOOST_CHECK_EQUAL(iter->name(),*ref_iter);

}

BOOST_AUTO_TEST_CASE(test_index_access_name_order_decreasing)
{
  BOOST_CHECK_EQUAL(root_group.attributes.size(),3);
  root_group.attributes.iterator_config().index(IterationIndex::NAME);
  root_group.attributes.iterator_config().order(IterationOrder::DECREASING);

  BOOST_CHECK_EQUAL(root_group.attributes[0].name(),"index");
  BOOST_CHECK_EQUAL(root_group.attributes[1].name(),"elasticity");
  BOOST_CHECK_EQUAL(root_group.attributes[2].name(),"counter");
}

BOOST_AUTO_TEST_CASE(test_iterator_access_name_order_decreasing)
{
  root_group.attributes.iterator_config().index(IterationIndex::NAME);
  root_group.attributes.iterator_config().order(IterationOrder::DECREASING);

  std::vector<std::string> ref_names{"index","elasticity","counter"};
  auto ref_iter = ref_names.begin();

  auto iter     = root_group.attributes.begin();
  auto iter_end = root_group.attributes.end();
  while(iter!=iter_end)
  {
    BOOST_CHECK_EQUAL(iter++->name(),*ref_iter++);
  }
}

BOOST_AUTO_TEST_CASE(test_access_failure)
{
  BOOST_CHECK_THROW(root_group.attributes[3],std::runtime_error);
  BOOST_CHECK_THROW(root_group.attributes["hello"],std::runtime_error);
}



BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
