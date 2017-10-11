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
// Author: Martin Shetty <martin.shetty@esss.se>
// Created on: Oct 11, 2017
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Testing string data types
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <h5cpp/datatype/factory.hpp>
#include <h5cpp/datatype/string.hpp>
#include <h5cpp/attribute/attribute.hpp>
#include <h5cpp/file/file.hpp>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/node/group.hpp>
#include <h5cpp/dataspace/scalar.hpp>

namespace type = hdf5::datatype;
namespace attr = hdf5::attribute;

struct Fixture
{
    hdf5::file::File file;
    hdf5::node::Group root_group;

    Fixture():
      file(hdf5::file::create("CompoundTest.h5",hdf5::file::AccessFlags::TRUNCATE)),
      root_group(file.root())
    {}
};

using test_types = boost::mpl::list<std::string>;
//                                    std::wstring,
//                                    std::u16string,
//                                    std::u32string>;

BOOST_FIXTURE_TEST_SUITE(String_test,Fixture)

BOOST_AUTO_TEST_CASE(test_construction)
{
  auto t = type::String::fixed(3);
  BOOST_CHECK(t.get_class()==type::Class::STRING);
  BOOST_CHECK_EQUAL(t.size(),3);
  BOOST_CHECK(!t.is_variable_length());

  auto t2 = type::String::variable();
  BOOST_CHECK(t2.get_class()==type::Class::STRING);
  BOOST_CHECK_EQUAL(t2.size(),H5T_VARIABLE);
  BOOST_CHECK(t2.is_variable_length());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_fixed_io,T,test_types)
{
  auto t = type::String::fixed(5);
  hdf5::dataspace::Scalar ds;

  attr::Attribute a = root_group.attributes.create("string", t, ds);
  T write_string("abc");
  a.write(write_string, t);

//  T read1("cba");
//  a.read(read1);
//  BOOST_CHECK_EQUAL(write_string, read1);

//  T read2(6, '\0');
//  a.read(read2);
//  BOOST_CHECK_EQUAL(write_string, read2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_variable_io,T,test_types)
{
  attr::Attribute a = root_group.attributes.create<T>("string");
  T write_string("hello world");
  a.write(write_string);

  T read1("world hello");
  a.read(read1);
  BOOST_CHECK_EQUAL(write_string, read1);

//  T read2(20, '\0');
//  a.read(read2);
//  BOOST_CHECK_EQUAL(write_string, read2);
}

BOOST_AUTO_TEST_SUITE_END()
