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
#define BOOST_TEST_MODULE testing Scope flags implementation
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <h5cpp/file/types.hpp>

using boost::test_tools::output_test_stream;
using namespace hdf5;

BOOST_AUTO_TEST_SUITE(Scope_test)

BOOST_AUTO_TEST_CASE(test_string_representation)
{
  output_test_stream stream;
  stream<<file::Scope::GLOBAL;
  BOOST_CHECK(stream.is_equal("GLOBAL"));
  stream<<file::Scope::LOCAL;
  BOOST_CHECK(stream.is_equal("LOCAL"));
}

BOOST_AUTO_TEST_CASE(test_values)
{
  BOOST_CHECK_EQUAL(static_cast<file::ScopeBase>(file::Scope::LOCAL),
                    H5F_SCOPE_LOCAL);
  BOOST_CHECK_EQUAL(static_cast<file::ScopeBase>(file::Scope::GLOBAL),
                     H5F_SCOPE_GLOBAL);
}

BOOST_AUTO_TEST_SUITE_END()
