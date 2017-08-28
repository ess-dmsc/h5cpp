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
// Created on: Aug 28, 2017
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testing dataset creation property list implementation
#include <boost/test/unit_test.hpp>
#include <h5cpp/property/dataset_creation_list.hpp>

namespace prop = hdf5::property;

BOOST_AUTO_TEST_SUITE(DatasetCreationList_test)

BOOST_AUTO_TEST_CASE(test_construction)
{
  prop::DatasetCreationList pl;
  BOOST_CHECK(pl.get_class()==prop::kDatasetCreate);
  BOOST_CHECK_EQUAL(pl.layout(),prop::DatasetLayout::CONTIGUOUS);
  BOOST_CHECK_EQUAL(pl.fill_time(),prop::DatasetFillTime::IFSET);
  BOOST_CHECK_EQUAL(pl.allocation_time(),prop::DatasetAllocTime::LATE);
  BOOST_CHECK_EQUAL(pl.fill_value_status(),prop::DatasetFillValueStatus::DEFAULT);
}

BOOST_AUTO_TEST_CASE(test_layout)
{
  prop::DatasetCreationList pl;
  BOOST_CHECK_EQUAL(pl.layout(),prop::DatasetLayout::CONTIGUOUS);
  BOOST_CHECK_NO_THROW(pl.layout(prop::DatasetLayout::CHUNKED));
  BOOST_CHECK_EQUAL(pl.layout(),prop::DatasetLayout::CHUNKED);
  BOOST_CHECK_NO_THROW(pl.layout(prop::DatasetLayout::COMPACT));
  BOOST_CHECK_EQUAL(pl.layout(),prop::DatasetLayout::COMPACT);
}

BOOST_AUTO_TEST_CASE(test_chunk)
{
  prop::DatasetCreationList pl;
  BOOST_CHECK_NO_THROW(pl.chunk({10,100}));

  hdf5::Dimensions c = pl.chunk();
  hdf5::Dimensions e{10,100};
  BOOST_CHECK_EQUAL_COLLECTIONS(c.begin(),c.end(),e.begin(),e.end());
}

BOOST_AUTO_TEST_CASE(test_fill_time)
{
  prop::DatasetCreationList pl;
  BOOST_CHECK_EQUAL(pl.fill_time(),prop::DatasetFillTime::IFSET);
  BOOST_CHECK_NO_THROW(pl.fill_time(prop::DatasetFillTime::ALLOC));
  BOOST_CHECK_EQUAL(pl.fill_time(),prop::DatasetFillTime::ALLOC);
  BOOST_CHECK_NO_THROW(pl.fill_time(prop::DatasetFillTime::NEVER));
  BOOST_CHECK_EQUAL(pl.fill_time(),prop::DatasetFillTime::NEVER);

}

BOOST_AUTO_TEST_CASE(test_allocation_time)
{
  prop::DatasetCreationList pl;
  BOOST_CHECK_EQUAL(pl.allocation_time(),prop::DatasetAllocTime::LATE);
  BOOST_CHECK_NO_THROW(pl.allocation_time(prop::DatasetAllocTime::DEFAULT));
  BOOST_CHECK_EQUAL(pl.allocation_time(),prop::DatasetAllocTime::LATE);
  BOOST_CHECK_NO_THROW(pl.allocation_time(prop::DatasetAllocTime::EARLY));
  BOOST_CHECK_EQUAL(pl.allocation_time(),prop::DatasetAllocTime::EARLY);
  BOOST_CHECK_NO_THROW(pl.allocation_time(prop::DatasetAllocTime::INCR));
  BOOST_CHECK_EQUAL(pl.allocation_time(),prop::DatasetAllocTime::INCR);
}

BOOST_AUTO_TEST_CASE(test_fill_value_default)
{
  prop::DatasetCreationList pl;
  BOOST_CHECK_NO_THROW(pl.fill_value(1024));
  BOOST_CHECK_EQUAL(pl.fill_value<int>(),1024);
  BOOST_CHECK_EQUAL(pl.fill_value_status(),prop::DatasetFillValueStatus::USER_DEFINED);
}


BOOST_AUTO_TEST_SUITE_END()
