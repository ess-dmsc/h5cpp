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
// Created on: Aug 21, 2017
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testing file creation property list implementatino
#include <boost/test/unit_test.hpp>
#include <h5cpp/property/file_creation_list.hpp>
#include <h5cpp/property/class.hpp>

namespace pl = hdf5::property;

BOOST_AUTO_TEST_SUITE(FileCreationList_test)

  BOOST_AUTO_TEST_CASE(test_default_construction)
  {
    pl::FileCreationList fcpl;
    BOOST_CHECK(fcpl.get_class() == pl::kFileCreate);
  }

  BOOST_AUTO_TEST_CASE(test_user_block)
  {
    pl::FileCreationList fcpl;

    BOOST_CHECK_NO_THROW(fcpl.userblock(1024));
    BOOST_CHECK_EQUAL(fcpl.userblock(),1024);

    //too small
    BOOST_CHECK_THROW(fcpl.userblock(256),std::runtime_error);
    //not a power of two
    BOOST_CHECK_THROW(fcpl.userblock(513),std::runtime_error);
  }

  BOOST_AUTO_TEST_CASE(test_object_offset_size)
  {
    pl::FileCreationList fcpl;
    BOOST_CHECK_EQUAL(fcpl.object_offset_size(),sizeof(hsize_t));
    BOOST_CHECK_NO_THROW(fcpl.object_offset_size(2));
    BOOST_CHECK_EQUAL(fcpl.object_offset_size(),2);
    BOOST_CHECK_NO_THROW(fcpl.object_offset_size(4));
    BOOST_CHECK_EQUAL(fcpl.object_offset_size(),4);
    BOOST_CHECK_NO_THROW(fcpl.object_offset_size(8));
    BOOST_CHECK_EQUAL(fcpl.object_offset_size(),8);
    BOOST_CHECK_NO_THROW(fcpl.object_offset_size(16));
    BOOST_CHECK_EQUAL(fcpl.object_offset_size(),16);

    BOOST_CHECK_THROW(fcpl.object_offset_size(15),std::runtime_error);
    BOOST_CHECK_THROW(fcpl.object_offset_size(25),std::runtime_error);

  }

  BOOST_AUTO_TEST_CASE(test_object_length_size)
  {
    pl::FileCreationList fcpl;
    BOOST_CHECK_EQUAL(fcpl.object_length_size(),sizeof(hsize_t));
    BOOST_CHECK_NO_THROW(fcpl.object_length_size(2));
    BOOST_CHECK_EQUAL(fcpl.object_length_size(),2);
    BOOST_CHECK_NO_THROW(fcpl.object_length_size(4));
    BOOST_CHECK_EQUAL(fcpl.object_length_size(),4);
    BOOST_CHECK_NO_THROW(fcpl.object_length_size(8));
    BOOST_CHECK_EQUAL(fcpl.object_length_size(),8);
    BOOST_CHECK_NO_THROW(fcpl.object_length_size(16));
    BOOST_CHECK_EQUAL(fcpl.object_length_size(),16);

    BOOST_CHECK_THROW(fcpl.object_length_size(15),std::runtime_error);
    BOOST_CHECK_THROW(fcpl.object_length_size(25),std::runtime_error);
  }


BOOST_AUTO_TEST_SUITE_END()
