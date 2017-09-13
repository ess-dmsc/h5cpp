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
// Created on: Sep 12, 2017
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testing group creation
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/node/group.hpp>
#include <h5cpp/node/types.hpp>
#include <h5cpp/datatype/factory.hpp>
#include <h5cpp/dataspace/scalar.hpp>
#include <h5cpp/property/link_creation_list.hpp>
#include <h5cpp/property/group_creation_list.hpp>
#include <h5cpp/property/file_creation_list.hpp>
#include <h5cpp/property/file_access_list.hpp>
#include <h5cpp/iterator_config.hpp>

using boost::test_tools::output_test_stream;
using namespace hdf5;

struct TestFixture
{
    file::File file;

    TestFixture():
      file()
    {
      property::FileCreationList fcpl;
      property::FileAccessList fapl;
      fcpl.link_creation_order(property::CreationOrder().enable_indexed());
      fapl.library_version_bounds(property::LibVersion::LATEST,property::LibVersion::LATEST);

      file = file::create("group_test.h5",file::AccessFlags::TRUNCATE,fcpl,fapl);

    }
};

struct NodeIterationFixture : public TestFixture
{
    node::Group root_group;

    NodeIterationFixture():
      TestFixture(),
      root_group(file.root())
    {
      property::LinkCreationList lcpl;
      property::GroupCreationList gcpl;
      gcpl.link_creation_order(property::CreationOrder().enable_indexed());
      root_group.create_group("g1",lcpl,gcpl);
      root_group.create_group("g2",lcpl,gcpl);
      root_group.create_group("g3",lcpl,gcpl);
      root_group.create_dataset("d1",datatype::create<float>(),dataspace::Scalar());
      root_group.create_dataset("d2",datatype::create<int>(),dataspace::Scalar());
    }
};

BOOST_FIXTURE_TEST_SUITE(group_test,TestFixture)

BOOST_AUTO_TEST_CASE(test_root_group)
{
  node::Group root;
  BOOST_CHECK_NO_THROW(root = file.root());
  BOOST_CHECK(root.is_valid());
  BOOST_CHECK_EQUAL(root.type(),node::Type::GROUP);
  BOOST_CHECK_EQUAL(root.links.size(),0);
  BOOST_CHECK_EQUAL(root.nodes.size(),0);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root.path()),"/");
}

BOOST_AUTO_TEST_CASE(test_default_construction)
{
  node::Group group;
  BOOST_CHECK(!group.is_valid());
}

BOOST_AUTO_TEST_CASE(test_group_creation)
{
  node::Group g = file.root();
  BOOST_CHECK_NO_THROW(g.create_group("group_1"));
  BOOST_CHECK_NO_THROW(g.create_group("group_2"));
  BOOST_CHECK_EQUAL(g.nodes.size(),2);
  BOOST_CHECK_EQUAL(g.links.size(),2);

}

BOOST_FIXTURE_TEST_SUITE(group_node_iteration,NodeIterationFixture)

BOOST_AUTO_TEST_CASE(group_index_name_order_access)
{
  BOOST_CHECK_EQUAL(root_group.nodes.size(),5);
  //setup creation order
  root_group.iterator_config().index(hdf5::IterationIndex::NAME);
  root_group.iterator_config().order(hdf5::IterationOrder::DECREASING);

  BOOST_CHECK_EQUAL(root_group.nodes[0].type(),node::Type::GROUP);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.nodes[0].path()),"/g3");
  BOOST_CHECK_EQUAL(root_group.nodes[1].type(),node::Type::GROUP);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.nodes[1].path()),"/g2");
  BOOST_CHECK_EQUAL(root_group.nodes[2].type(),node::Type::GROUP);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.nodes[2].path()),"/g1");
  BOOST_CHECK_EQUAL(root_group.nodes[3].type(),node::Type::DATASET);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.nodes[3].path()),"/d2");
  BOOST_CHECK_EQUAL(root_group.nodes[4].type(),node::Type::DATASET);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.nodes[4].path()),"/d1");
}

BOOST_AUTO_TEST_CASE(group_index_creation_order_access)
{
  BOOST_CHECK_EQUAL(root_group.nodes.size(),5);
  //setup creation order
  root_group.iterator_config().index(hdf5::IterationIndex::CREATION_ORDER);
  root_group.iterator_config().order(hdf5::IterationOrder::INCREASING);

  BOOST_CHECK_EQUAL(root_group.nodes[0].type(),node::Type::GROUP);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.nodes[0].path()),"/g1");
  BOOST_CHECK_EQUAL(root_group.nodes[1].type(),node::Type::GROUP);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.nodes[1].path()),"/g2");
  BOOST_CHECK_EQUAL(root_group.nodes[2].type(),node::Type::GROUP);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.nodes[2].path()),"/g3");
  BOOST_CHECK_EQUAL(root_group.nodes[3].type(),node::Type::DATASET);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.nodes[3].path()),"/d1");
  BOOST_CHECK_EQUAL(root_group.nodes[4].type(),node::Type::DATASET);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.nodes[4].path()),"/d2");
}

BOOST_AUTO_TEST_CASE(group_name_access)
{
  node::Node n;
  BOOST_CHECK_NO_THROW(n=root_group.nodes["g1"]);
  BOOST_CHECK_EQUAL(n.type(),node::Type::GROUP);
  BOOST_CHECK_EQUAL(static_cast<std::string>(n.path()),"/g1");
  BOOST_CHECK_NO_THROW(n=root_group.nodes["d1"]);
  BOOST_CHECK_EQUAL(n.type(),node::Type::DATASET);
  BOOST_CHECK_EQUAL(static_cast<std::string>(n.path()),"/d1");

}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
