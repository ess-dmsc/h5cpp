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
#define BOOST_TEST_MODULE testing AccessFlags implementation
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <h5cpp/file/types.hpp>

using boost::test_tools::output_test_stream;
using namespace hdf5;

BOOST_AUTO_TEST_SUITE(AccessFlags_test)

BOOST_AUTO_TEST_CASE(test_output_stream)
{
  output_test_stream stream;
  stream<<file::AccessFlags::EXCLUSIVE;
  BOOST_CHECK(stream.is_equal("EXCLUSIVE"));
  stream<<file::AccessFlags::READONLY;
  BOOST_CHECK(stream.is_equal("READONLY"));
  stream<<file::AccessFlags::READWRITE;
  BOOST_CHECK(stream.is_equal("READWRITE"));
  stream<<file::AccessFlags::TRUNCATE;
  BOOST_CHECK(stream.is_equal("TRUNCATE"));
#if H5_VERSION_GE(1,10,0)
  stream<<file::AccessFlags::SWMR_WRITE;
  BOOST_CHECK(stream.is_equal("SWMR WRITE"));
  stream<<file::AccessFlags::SWMR_READ;
  BOOST_CHECK(stream.is_equal("SWMR READ"));
#endif
}

BOOST_AUTO_TEST_CASE(test_values)
{
  BOOST_CHECK_EQUAL(static_cast<file::AccessFlagsBase>(file::AccessFlags::EXCLUSIVE),
                    H5F_ACC_EXCL);
  BOOST_CHECK_EQUAL(static_cast<file::AccessFlagsBase>(file::AccessFlags::READONLY),
                    H5F_ACC_RDONLY);
  BOOST_CHECK_EQUAL(static_cast<file::AccessFlagsBase>(file::AccessFlags::READWRITE),
                    H5F_ACC_RDWR);
  BOOST_CHECK_EQUAL(static_cast<file::AccessFlagsBase>(file::AccessFlags::TRUNCATE),
                    H5F_ACC_TRUNC);
#if H5_VERSION_GE(1,10,0)
  BOOST_CHECK_EQUAL(static_cast<file::AccessFlagsBase>(file::AccessFlags::SWMR_WRITE),
                    H5F_ACC_SWMR_WRITE);
  BOOST_CHECK_EQUAL(static_cast<file::AccessFlagsBase>(file::AccessFlags::SWMR_READ),
                    H5F_ACC_SWMR_READ);

#endif
}

BOOST_AUTO_TEST_SUITE_END()
