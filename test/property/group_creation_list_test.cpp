
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
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testing group creation property list implementation
#include <boost/test/unit_test.hpp>
#include <h5cpp/property/group_creation_list.hpp>
#include <h5cpp/property/class.hpp>

namespace pl = hdf5::property;

BOOST_AUTO_TEST_SUITE(GroupCreation_test)

  BOOST_AUTO_TEST_CASE(test_construction)
  {
    pl::GroupCreationList gcpl;
    BOOST_CHECK(gcpl.get_class()==pl::kGroupCreate);
  }

  BOOST_AUTO_TEST_CASE(test_local_heap_size_hint)
  {
    pl::GroupCreationList gcpl;
    BOOST_CHECK_NO_THROW(gcpl.local_heap_size_hint(1024));
    BOOST_CHECK_EQUAL(gcpl.local_heap_size_hint(),1024);

    BOOST_CHECK_NO_THROW(gcpl.local_heap_size_hint(512));
    BOOST_CHECK_EQUAL(gcpl.local_heap_size_hint(),512);
  }

  BOOST_AUTO_TEST_CASE(test_estimated_number_of_links)
  {
    pl::GroupCreationList gcpl;
    BOOST_CHECK_NO_THROW(gcpl.estimated_number_of_links(10));
    BOOST_CHECK_EQUAL(gcpl.estimated_number_of_links(),10);
    BOOST_CHECK_NO_THROW(gcpl.estimated_number_of_links(33));
    BOOST_CHECK_EQUAL(gcpl.estimated_number_of_links(),33);

  }

  BOOST_AUTO_TEST_CASE(test_estimated_link_name_length)
  {
    pl::GroupCreationList gcpl;
    BOOST_CHECK_NO_THROW(gcpl.estimated_link_name_length(100));
    BOOST_CHECK_EQUAL(gcpl.estimated_link_name_length(),100);

    BOOST_CHECK_NO_THROW(gcpl.estimated_link_name_length(64));
    BOOST_CHECK_EQUAL(gcpl.estimated_link_name_length(),64);
  }

  BOOST_AUTO_TEST_CASE(test_link_creation_order)
  {
    pl::GroupCreationList gcpl;
    BOOST_CHECK_NO_THROW(gcpl.link_creation_order(pl::CreationOrder().enable_indexed()));
    pl::CreationOrder flags = gcpl.link_creation_order();
    BOOST_CHECK(flags.tracked());
    BOOST_CHECK(flags.indexed());

    BOOST_CHECK_NO_THROW(gcpl.link_creation_order(pl::CreationOrder().enable_tracked()));
    flags = gcpl.link_creation_order();
    BOOST_CHECK(flags.tracked());
    BOOST_CHECK(!flags.indexed());

  }

  BOOST_AUTO_TEST_CASE(test_maximum_links_for_compact_group)
  {
    pl::GroupCreationList gcpl;
    BOOST_CHECK_NO_THROW(gcpl.maximum_links_for_compact_group(100));
    BOOST_CHECK_EQUAL(gcpl.maximum_links_for_compact_group(),100);

    BOOST_CHECK_NO_THROW(gcpl.maximum_links_for_compact_group(45));
    BOOST_CHECK_EQUAL(gcpl.maximum_links_for_compact_group(),45);
  }

  BOOST_AUTO_TEST_CASE(test_minimum_links_for_dense_group)
  {
    pl::GroupCreationList gcpl;
    BOOST_CHECK_NO_THROW(gcpl.minimum_links_for_dense_group(5));
    BOOST_CHECK_EQUAL(gcpl.minimum_links_for_dense_group(),5);

    BOOST_CHECK_NO_THROW(gcpl.minimum_links_for_dense_group(4));
    BOOST_CHECK_EQUAL(gcpl.minimum_links_for_dense_group(),4);
  }

BOOST_AUTO_TEST_SUITE_END()
