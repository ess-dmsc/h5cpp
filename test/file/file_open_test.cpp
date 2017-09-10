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
// Created on: Sep 10, 2017
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testing open creation function
#include <boost/test/unit_test.hpp>
#include <h5cpp/file/functions.hpp>
#include <boost/filesystem.hpp>

using namespace hdf5;
namespace fs = boost::filesystem;

struct GlobalFixture
{
    GlobalFixture();
    ~GlobalFixture();
};

GlobalFixture::GlobalFixture()
{
  fs::remove("file_open.h5");

  property::FileCreationList fcpl;
  property::FileAccessList fapl;
#if H5_VERSION_GE(1,10,0)
  //need this for SWMR
  fapl.library_version_bounds(property::LibVersion::LATEST,property::LibVersion::LATEST);
#endif
  file::create("file_open.h5",file::AccessFlags::TRUNCATE,fcpl,fapl);
}

GlobalFixture::~GlobalFixture()
{

}

BOOST_GLOBAL_FIXTURE(GlobalFixture);

BOOST_AUTO_TEST_SUITE(FileOpen_test)

BOOST_AUTO_TEST_CASE(test_open_default)
{
  file::File f = file::open("file_open.h5");
  BOOST_CHECK_EQUAL(f.intent(),file::AccessFlags::READONLY);
}

BOOST_AUTO_TEST_CASE(test_open_readwrite)
{
  file::File f = file::open("file_open.h5",file::AccessFlags::READWRITE);
  BOOST_CHECK_EQUAL(f.intent(),file::AccessFlags::READWRITE);
}

#if H5_VERSION_GE(1,10,0)

BOOST_AUTO_TEST_CASE(test_open_swmr_read)
{
  file::File f = file::open("file_open.h5",file::AccessFlags::SWMR_READ);
  BOOST_CHECK_EQUAL(f.intent(),file::AccessFlags::SWMR_READ);
}

BOOST_AUTO_TEST_CASE(test_open_swmr_write)
{
  file::File f = file::open("file_open.h5",
                             file::AccessFlags::READWRITE | file::AccessFlags::SWMR_WRITE);


  BOOST_CHECK_EQUAL(static_cast<file::AccessFlagsBase>(f.intent()),
                    file::AccessFlags::SWMR_WRITE|file::AccessFlags::READWRITE  );

}

#endif


BOOST_AUTO_TEST_SUITE_END()




