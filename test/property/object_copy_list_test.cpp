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
  stream<<property::CopyFlag::EXPAND_REFERENCES;
  BOOST_CHECK(stream.is_equal("EXPAND_REFERENCES"));
  stream<<property::CopyFlag::WITHOUT_ATTRIBUTES;
  BOOST_CHECK(stream.is_equal("WITHOUT_ATTRIBUTES"));
  stream<<property::CopyFlag::MERGE_COMMITTED_TYPES;
  BOOST_CHECK(stream.is_equal("MERGE_COMMITTED_TYPES"));
}

BOOST_AUTO_TEST_CASE(test_or_operator_1)
{
  property::CopyFlags flags = property::CopyFlag::SHALLOW_HIERARCHY |
                              property::CopyFlag::EXPAND_SOFT_LINKS;
  BOOST_CHECK(flags.shallow_hierarchy());
  BOOST_CHECK(flags.expand_soft_links());
  BOOST_CHECK(!flags.expand_external_links());
  BOOST_CHECK(!flags.expand_references());
  BOOST_CHECK(!flags.without_attributes());
  BOOST_CHECK(!flags.merge_committed_types());
}

BOOST_AUTO_TEST_CASE(test_or_operator_2)
{
  property::CopyFlags flags = property::CopyFlag::EXPAND_SOFT_LINKS |
                              property::CopyFlag::EXPAND_EXTERNAL_LINKS;


  BOOST_CHECK(!flags.shallow_hierarchy());
  BOOST_CHECK(flags.expand_soft_links());
  BOOST_CHECK(flags.expand_external_links());
  BOOST_CHECK(!flags.expand_references());
  BOOST_CHECK(!flags.without_attributes());
  BOOST_CHECK(!flags.merge_committed_types());
}

BOOST_AUTO_TEST_CASE(test_or_operator_3)
{
  property::CopyFlags flags = property::CopyFlag::EXPAND_EXTERNAL_LINKS |
                              property::CopyFlag::EXPAND_REFERENCES;


  BOOST_CHECK(!flags.shallow_hierarchy());
  BOOST_CHECK(!flags.expand_soft_links());
  BOOST_CHECK(flags.expand_external_links());
  BOOST_CHECK(flags.expand_references());
  BOOST_CHECK(!flags.without_attributes());
  BOOST_CHECK(!flags.merge_committed_types());
}

BOOST_AUTO_TEST_CASE(test_or_operator_4)
{
  property::CopyFlags flags = property::CopyFlag::EXPAND_REFERENCES |
                              property::CopyFlag::WITHOUT_ATTRIBUTES;


  BOOST_CHECK(!flags.shallow_hierarchy());
  BOOST_CHECK(!flags.expand_soft_links());
  BOOST_CHECK(!flags.expand_external_links());
  BOOST_CHECK(flags.expand_references());
  BOOST_CHECK(flags.without_attributes());
  BOOST_CHECK(!flags.merge_committed_types());
}

BOOST_AUTO_TEST_CASE(test_or_operator_5)
{
  property::CopyFlags flags = property::CopyFlag::WITHOUT_ATTRIBUTES |
                              property::CopyFlag::MERGE_COMMITTED_TYPES;


  BOOST_CHECK(!flags.shallow_hierarchy());
  BOOST_CHECK(!flags.expand_soft_links());
  BOOST_CHECK(!flags.expand_external_links());
  BOOST_CHECK(!flags.expand_references());
  BOOST_CHECK(flags.without_attributes());
  BOOST_CHECK(flags.merge_committed_types());
}

BOOST_AUTO_TEST_CASE(test_or_operator_6)
{
  property::CopyFlags flags = property::CopyFlag::MERGE_COMMITTED_TYPES |
                              property::CopyFlag::SHALLOW_HIERARCHY;


  BOOST_CHECK(flags.shallow_hierarchy());
  BOOST_CHECK(!flags.expand_soft_links());
  BOOST_CHECK(!flags.expand_external_links());
  BOOST_CHECK(!flags.expand_references());
  BOOST_CHECK(!flags.without_attributes());
  BOOST_CHECK(flags.merge_committed_types());
}

BOOST_AUTO_TEST_SUITE_END()

//=============================================================================
// test suite for the CopyFlags class
//=============================================================================
BOOST_AUTO_TEST_SUITE(CopyFlagsTest)

BOOST_AUTO_TEST_CASE(test_default_construction)
{
  property::CopyFlags flags;
  BOOST_CHECK(!flags.shallow_hierarchy());
  BOOST_CHECK(!flags.expand_soft_links());
  BOOST_CHECK(!flags.expand_external_links());
  BOOST_CHECK(!flags.expand_references());
  BOOST_CHECK(!flags.without_attributes());
  BOOST_CHECK(!flags.merge_committed_types());
}

BOOST_AUTO_TEST_CASE(test_shallow_hierarchy)
{
  property::CopyFlags flags;
  flags.expand_soft_links(true);
  BOOST_CHECK(flags.expand_soft_links());
  flags.expand_soft_links(false);
  BOOST_CHECK(!flags.expand_soft_links());
}

BOOST_AUTO_TEST_CASE(test_expand_soft_links)
{
  property::CopyFlags flags;
  flags.expand_soft_links(true);
  BOOST_CHECK(flags.expand_soft_links());
  flags.expand_soft_links(false);
  BOOST_CHECK(!flags.expand_soft_links());
}

BOOST_AUTO_TEST_CASE(test_expand_external_links)
{
  property::CopyFlags flags;
  flags.expand_external_links(true);
  BOOST_CHECK(flags.expand_external_links());
  flags.expand_external_links(false);
  BOOST_CHECK(!flags.expand_external_links());
}

BOOST_AUTO_TEST_CASE(test_expand_references)
{
  property::CopyFlags flags;
  flags.expand_references(true);
  BOOST_CHECK(flags.expand_references());
  flags.expand_references(false);
  BOOST_CHECK(!flags.expand_references());
}

BOOST_AUTO_TEST_CASE(test_without_attributes)
{
  property::CopyFlags flags;
  flags.without_attributes(true);
  BOOST_CHECK(flags.without_attributes());
  flags.without_attributes(false);
  BOOST_CHECK(!flags.without_attributes());
}

BOOST_AUTO_TEST_CASE(test_merge_committed_types)
{
  property::CopyFlags flags;
  flags.merge_committed_types(true);
  BOOST_CHECK(flags.merge_committed_types());
  flags.merge_committed_types(false);
  BOOST_CHECK(!flags.merge_committed_types());
}

BOOST_AUTO_TEST_CASE(test_unary_or_1)
{
  property::CopyFlags flags;
  flags |= property::CopyFlag::EXPAND_EXTERNAL_LINKS;
  BOOST_CHECK(flags.expand_external_links());
}

BOOST_AUTO_TEST_CASE(test_or_operations_1)
{
  property::CopyFlags flags = property::CopyFlag::EXPAND_EXTERNAL_LINKS |
                              property::CopyFlag::EXPAND_SOFT_LINKS |
                              property::CopyFlag::WITHOUT_ATTRIBUTES ;
  BOOST_CHECK(flags.without_attributes());
  BOOST_CHECK(flags.expand_soft_links());
  BOOST_CHECK(flags.expand_external_links());
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE_END()



