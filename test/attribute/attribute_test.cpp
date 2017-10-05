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
// Created on: Oct 4, 2017
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testing the Attribute class
#include <boost/test/unit_test.hpp>
#include <h5cpp/file/file.hpp>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/node/group.hpp>
#include <h5cpp/attribute/attribute.hpp>
#include <h5cpp/dataspace/type.hpp>
#include <h5cpp/datatype/types.hpp>

#include "attribute_test_fixtures.hpp"

using namespace hdf5;


BOOST_AUTO_TEST_SUITE(AttributeTest)

BOOST_AUTO_TEST_CASE(test_default_construction)
{
  attribute::Attribute a;
  BOOST_CHECK_THROW(a.datatype(),std::runtime_error);
  BOOST_CHECK_THROW(a.dataspace(),std::runtime_error);
  BOOST_CHECK_THROW(a.name(),std::runtime_error);
  BOOST_CHECK(!a.is_valid());
}

BOOST_FIXTURE_TEST_SUITE(AttributeTestConstruction,AttributeFixture)

BOOST_AUTO_TEST_CASE(test_scalar)
{
  attribute::Attribute a;
  BOOST_CHECK_NO_THROW(a = root_group.attributes.create<int>("test"));
  BOOST_CHECK_EQUAL(a.dataspace().type(),dataspace::Type::SCALAR);
  dataspace::Scalar space(a.dataspace());

  BOOST_CHECK_EQUAL(a.datatype().get_class(),datatype::Class::INTEGER);
  BOOST_CHECK_EQUAL(a.name(),"test");
  BOOST_CHECK_EQUAL(root_group.attributes.size(),1);

  BOOST_CHECK_NO_THROW(a = root_group.attributes.create<float>("test2"));
  BOOST_CHECK_EQUAL(a.dataspace().type(),dataspace::Type::SCALAR);
  BOOST_CHECK_EQUAL(a.datatype().get_class(),datatype::Class::FLOAT);
  BOOST_CHECK_EQUAL(a.name(),"test2");
  BOOST_CHECK_EQUAL(root_group.attributes.size(),2);
}

BOOST_AUTO_TEST_CASE(test_multidim_simple_construction)
{
  attribute::Attribute a;
  BOOST_CHECK_NO_THROW(a = root_group.attributes.create<int>("test",{1}));
  BOOST_CHECK_EQUAL(a.dataspace().size(),1);
  BOOST_CHECK_EQUAL(a.name(),"test");
  BOOST_CHECK_EQUAL(a.dataspace().type(),dataspace::Type::SIMPLE);
  dataspace::Simple space(a.dataspace());
  BOOST_CHECK_EQUAL(space.rank(),1);
  BOOST_CHECK_EQUAL(space.current_dimensions()[0],1);

  BOOST_CHECK_NO_THROW(a = root_group.attributes.create<int>("matrix",{3,4}));
  BOOST_CHECK_EQUAL(a.name(),"matrix");
  space = dataspace::Simple(a.dataspace());
  BOOST_CHECK_EQUAL(space.rank(),2);
  BOOST_CHECK_EQUAL(space.current_dimensions()[0],3);
  BOOST_CHECK_EQUAL(space.current_dimensions()[1],4);

}

BOOST_AUTO_TEST_CASE(test_multidim_construction)
{
  attribute::Attribute a;
  dataspace::Simple space{{3,4}};
  auto type = datatype::create<float>();

  BOOST_CHECK_NO_THROW(a = root_group.attributes.create("test",type,space));
  BOOST_CHECK(root_group.attributes.exists("test"));
  BOOST_CHECK(!root_group.attributes.exists("bla"));
  BOOST_CHECK_EQUAL(root_group.attributes.size(),1);
  BOOST_CHECK_EQUAL(a.name(),"test");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
