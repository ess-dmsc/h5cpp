
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
#define BOOST_TEST_MODULE Testing object creation property list implementation
#include <boost/test/unit_test.hpp>
#include <h5cpp/property/object_creation_list.hpp>
#include <h5cpp/property/class.hpp>

namespace pl = hdf5::property;

BOOST_AUTO_TEST_SUITE(ObjectCreationListTest)

  BOOST_AUTO_TEST_CASE(default_construction)
  {
    pl::ObjectCreationList ocpl;
    BOOST_CHECK(ocpl.get_class()==pl::kObjectCreate);
  }

  BOOST_AUTO_TEST_CASE(test_time_tracking)
  {
    pl::ObjectCreationList ocpl;
    BOOST_CHECK_NO_THROW(ocpl.enable_time_tracking());
    BOOST_CHECK(ocpl.time_tracking());

    BOOST_CHECK_NO_THROW(ocpl.disable_time_tracking());
    BOOST_CHECK(!ocpl.time_tracking());
  }

  BOOST_AUTO_TEST_CASE(test_attribute_creation_order)
  {
    pl::ObjectCreationList ocpl;

    BOOST_CHECK_NO_THROW(ocpl.attribute_creation_order(pl::CreationOrder().enable_tracked()));
    BOOST_CHECK(ocpl.attribute_creation_order().tracked());
    BOOST_CHECK(!ocpl.attribute_creation_order().indexed());

    BOOST_CHECK_NO_THROW(ocpl.attribute_creation_order(pl::CreationOrder().enable_indexed()));
    BOOST_CHECK(ocpl.attribute_creation_order().tracked());
    BOOST_CHECK(ocpl.attribute_creation_order().indexed());
  }

  BOOST_AUTO_TEST_CASE(test_attribute_storage_threshold)
  {
    pl::ObjectCreationList ocpl;
    BOOST_CHECK_NO_THROW(ocpl.attribute_storage_thresholds(100,50));
    BOOST_CHECK_EQUAL(ocpl.attribute_storage_maximum_compact(),100);
    BOOST_CHECK_EQUAL(ocpl.attribute_storage_minimum_dense(),50);

    BOOST_CHECK_THROW(ocpl.attribute_storage_thresholds(50,100),
                      std::runtime_error);
  }


BOOST_AUTO_TEST_SUITE_END()
