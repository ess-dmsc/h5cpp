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
// Created on: Aug 22, 2017
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testing file mount property list implementation
#include <boost/test/unit_test.hpp>
#include <h5cpp/property/file_mount_list.hpp>
#include <h5cpp/property/class.hpp>

namespace pl = hdf5::property;

BOOST_AUTO_TEST_SUITE(FileMountList_test)

BOOST_AUTO_TEST_CASE(test_default_construction)
{
  pl::FileMountList fmpl;
  BOOST_CHECK(fmpl.get_class() == pl::kFileMount);
}

BOOST_AUTO_TEST_SUITE_END()
