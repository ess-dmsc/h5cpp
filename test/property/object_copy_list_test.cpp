//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5cpp.
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
// Created on: Oct 09, 2017
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test ObjectCopyList and related classes
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <h5cpp/property/object_copy_list.hpp>

using namespace hdf5;
using boost::test_tools::output_test_stream;


BOOST_AUTO_TEST_SUITE(ObjectCopyClassesTest)

BOOST_AUTO_TEST_SUITE(CopyFlagTest)

BOOST_AUTO_TEST_CASE(test_string_representation)
{
  output_test_stream stream;
  stream<<property::CopyFlag::SHALLOW_HIERARCHY;
  BOOST_CHECK(stream.is_equal("SHALLOW_HIERARCHY"));
  stream<<property::CopyFlag::EXPAND_SOFT_LINKS;
  BOOST_CHECK(stream.is_equal("EXPAND_SOFT_LINKS"));
  stream<<property::CopyFlag::EXPAND_EXTERNAL_LINKS;
  BOOST_CHECK(stream.is_equal("EXPAND_EXTERNAL_LINKS"));
  stream<<property::CopyFlag::EXPAND_REFERNCES;
  BOOST_CHECK(stream.is_equal("EXPAND_REFERENCES"));
  stream<<property::CopyFlag::WITHOUT_ATTRIBUTES;
  BOOST_CHECK(stream.is_equal("WITHOUT_ATTRIBUTES"));
  stream<<property::CopyFlag::MERGE_COMMITTED_TYPES;
  BOOST_CHECK(stream.is_equal("MERGE_COMMITTED_TYPES"));
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE_END()



