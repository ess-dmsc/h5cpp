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
#define BOOST_TEST_MODULE testing file creation function
#include <boost/test/unit_test.hpp>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/node/group.hpp>
#include <boost/filesystem.hpp>

using namespace hdf5;
namespace fs = boost::filesystem;

struct GlobalFixture
{
    static const std::vector<std::string> files;
    GlobalFixture();
    ~GlobalFixture();
};

GlobalFixture::GlobalFixture()
{
  for(auto filename: files)
    fs::remove(filename);
}

GlobalFixture::~GlobalFixture()
{}

const std::vector<std::string> GlobalFixture::files = {
    "./test1.h5",
    "./test2.h5"
};

BOOST_GLOBAL_FIXTURE(GlobalFixture);


BOOST_AUTO_TEST_SUITE(FileCreation_test)

BOOST_AUTO_TEST_CASE(test_default)
{
  file::File f;
  BOOST_CHECK_THROW(f.intent(),std::runtime_error);
  BOOST_CHECK_THROW(f.size(),std::runtime_error);
  BOOST_CHECK_THROW(f.flush(file::Scope::GLOBAL),std::runtime_error);
  BOOST_CHECK_THROW(f.flush(file::Scope::LOCAL),std::runtime_error);
  BOOST_CHECK_THROW(f.count_open_objects(file::SearchFlags::ALL),std::runtime_error);
  BOOST_CHECK_THROW(f.root(),std::runtime_error);
  BOOST_CHECK_NO_THROW(f.close());
}

BOOST_AUTO_TEST_CASE(test_no_truncate)
{
  file::File f = file::create(fs::path("./test1.h5"));
  BOOST_CHECK_EQUAL(f.intent(),file::AccessFlags::READWRITE);
  f.close();

  //cannot create another file
  BOOST_CHECK_THROW(file::create("./test1.h5"),std::runtime_error);
}

BOOST_AUTO_TEST_CASE(test_truncation)
{
  file::File f = file::create("./test2.h5");
  BOOST_CHECK_EQUAL(f.intent(),file::AccessFlags::READWRITE);
  f.close();

  //should work
  BOOST_CHECK_NO_THROW(file::create("./test2.h5",file::AccessFlags::TRUNCATE));
}


BOOST_AUTO_TEST_SUITE_END()




