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
// Created on: Sep 8, 2017
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testing SearchFlags implementation
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <h5cpp/file/types.hpp>

using boost::test_tools::output_test_stream;
using namespace hdf5;

BOOST_AUTO_TEST_SUITE(SearchFlags_test)

BOOST_AUTO_TEST_CASE(test_output_stream)
{
  output_test_stream stream;
  stream<<file::SearchFlags::ALL;
  BOOST_CHECK(stream.is_equal("ALL"));
  stream<<file::SearchFlags::ATTRIBUTE;
  BOOST_CHECK(stream.is_equal("ATTRIBUTE"));
  stream<<file::SearchFlags::DATASET;
  BOOST_CHECK(stream.is_equal("DATASET"));
  stream<<file::SearchFlags::DATATYPE;
  BOOST_CHECK(stream.is_equal("DATATYPE"));
  stream<<file::SearchFlags::FILE;
  BOOST_CHECK(stream.is_equal("FILE"));
  stream<<file::SearchFlags::GROUP;
  BOOST_CHECK(stream.is_equal("GROUP"));
  stream<<file::SearchFlags::LOCAL;
  BOOST_CHECK(stream.is_equal("LOCAL"));
}

BOOST_AUTO_TEST_CASE(test_or_all_flags)
{
  BOOST_CHECK_EQUAL(file::SearchFlags::ATTRIBUTE | file::SearchFlags::DATASET,
                    H5F_OBJ_ATTR | H5F_OBJ_DATASET);

  BOOST_CHECK_EQUAL(file::SearchFlags::DATASET | file::SearchFlags::GROUP,
                    H5F_OBJ_DATASET | H5F_OBJ_GROUP);
}

BOOST_AUTO_TEST_CASE(test_or_left_three)
{
  BOOST_CHECK_EQUAL(file::SearchFlags::ATTRIBUTE | file::SearchFlags::DATASET |
                    file::SearchFlags::DATATYPE,
                    H5F_OBJ_ATTR | H5F_OBJ_DATASET | H5F_OBJ_DATATYPE);
}

BOOST_AUTO_TEST_CASE(test_values)
{
  BOOST_CHECK_EQUAL(static_cast<file::SearchFlagsBase>(file::SearchFlags::ALL),
                    H5F_OBJ_ALL);
  BOOST_CHECK_EQUAL(static_cast<file::SearchFlagsBase>(file::SearchFlags::ATTRIBUTE),
                      H5F_OBJ_ATTR);
  BOOST_CHECK_EQUAL(static_cast<file::SearchFlagsBase>(file::SearchFlags::DATASET),
                      H5F_OBJ_DATASET);
  BOOST_CHECK_EQUAL(static_cast<file::SearchFlagsBase>(file::SearchFlags::DATATYPE),
                      H5F_OBJ_DATATYPE);
  BOOST_CHECK_EQUAL(static_cast<file::SearchFlagsBase>(file::SearchFlags::FILE),
                      H5F_OBJ_FILE);
  BOOST_CHECK_EQUAL(static_cast<file::SearchFlagsBase>(file::SearchFlags::GROUP),
                        H5F_OBJ_GROUP);
  BOOST_CHECK_EQUAL(static_cast<file::SearchFlagsBase>(file::SearchFlags::LOCAL),
                        H5F_OBJ_LOCAL);
}

BOOST_AUTO_TEST_SUITE_END()
