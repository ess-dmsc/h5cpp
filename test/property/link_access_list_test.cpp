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
#define BOOST_TEST_MODULE testing link access property list implementation
#include <boost/test/unit_test.hpp>
#include <h5cpp/property/link_access_list.hpp>
#include <h5cpp/property/class.hpp>

namespace pl = hdf5::property;
namespace fs = boost::filesystem;

BOOST_AUTO_TEST_SUITE(LinkAccessList_test)

  BOOST_AUTO_TEST_CASE(test_default_construction)
  {
    pl::LinkAccessList lapl;
    BOOST_CHECK(lapl.get_class() == pl::kLinkAccess);
  }

  BOOST_AUTO_TEST_CASE(test_maximum_link_traversal)
  {
    pl::LinkAccessList lapl;
    BOOST_CHECK_NO_THROW(lapl.maximum_link_traversals(1000));
    BOOST_CHECK_EQUAL(lapl.maximum_link_traversals(),1000);

    BOOST_CHECK_NO_THROW(lapl.maximum_link_traversals(2000));
    BOOST_CHECK_EQUAL(lapl.maximum_link_traversals(),2000);
  }

  BOOST_AUTO_TEST_CASE(test_external_link_prefix)
  {
    pl::LinkAccessList lapl;
    BOOST_CHECK_NO_THROW(lapl.external_link_prefix("/home/wintersb"));
    BOOST_CHECK_EQUAL(lapl.external_link_prefix().string(),"/home/wintersb");
  }

#if H5_VERSION_GE(1,10,0)
  BOOST_AUTO_TEST_CASE(test_collective_metadata_operations)
  {
    pl::LinkAccessList lapl;
    BOOST_CHECK_NO_THROW(lapl.enable_collective_metadata_operations());
    BOOST_CHECK(lapl.collective_metadata_operations());

    BOOST_CHECK_NO_THROW(lapl.disable_collective_metadata_operations());
    BOOST_CHECK(!lapl.collective_metadata_operations());
  }
#endif

BOOST_AUTO_TEST_SUITE_END()
