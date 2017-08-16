//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5pp.
//
// h5cpp is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// h5cpp is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  ee the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with h5cpp.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Aug 14, 2017
//
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/bind.hpp>
#include <object_handle.hpp>
#include <vector>
#include <string>

#include "object_handle_test.hpp"
using namespace boost::unit_test;


void test_default_construction()
  {
    hdf5::ObjectHandle handle;

    BOOST_CHECK(!handle.is_valid());
    BOOST_CHECK_EQUAL(handle.get_type(),hdf5::ObjectHandle::Type::BADOBJECT);
    BOOST_CHECK_THROW(handle.get_reference_count(),std::runtime_error);
    BOOST_CHECK_NO_THROW(handle.close());
  }

test_suite *create_test_suite(hdf5::ObjectHandle::Type type)
{
  std::stringstream suite_name;
  suite_name<<"ObjectHandelTest_"<<type;
  test_suite *suite = BOOST_TEST_SUITE(suite_name.str());
  ObjectHandleTest *test = nullptr;
  switch(type)
  {
    case hdf5::ObjectHandle::Type::FILE:
      test = new FileObjectHandleTest("test.h5");
      break;
    case hdf5::ObjectHandle::Type::DATATYPE:
      test = new DatatypeObjectHandleTest();
      break;
    case hdf5::ObjectHandle::Type::DATASPACE:
      test = new DataspaceObjectHandleTest();
      break;
    case hdf5::ObjectHandle::Type::GROUP:
      test = new GroupObjectHandleTest("object_handle_group_test.h5");
      break;
    case hdf5::ObjectHandle::Type::DATASET:
      test = new DatasetObjectHandleTest("object_handle_dataset_test.h5");
      break;
    case hdf5::ObjectHandle::Type::ATTRIBUTE:
      test = new AttributeObjectHandleTest("object_handle_attribute_test.h5");
      break;
    case hdf5::ObjectHandle::Type::PROPERTY_LIST:
      test = new PropertyListObjectHandleTest();
      break;
    case hdf5::ObjectHandle::Type::PROPERTY_LIST_CLASS:
      test = new PropertyListClassObjectHandleTest();
      break;
    case hdf5::ObjectHandle::Type::ERROR_CLASS:
      test = new ErrorClassObjectHandleTest();
      break;
    case hdf5::ObjectHandle::Type::ERROR_MESSAGE:
      test = new ErrorMessageObjectHandleTest();
      break;
    case hdf5::ObjectHandle::Type::ERROR_STACK:
      test = new ErrorStackObjectHandleTest();
      break;
    default:
      return nullptr;
  }

  suite->add(make_test_case(boost::bind(&ObjectHandleTest::test_copy_assignment,test),
			    "Copy assignment test"));
  suite->add(make_test_case(boost::bind(&ObjectHandleTest::test_move_assignment,test),
			    "Move assignment test"));
  suite->add(make_test_case(boost::bind(&ObjectHandleTest::test_copy_construction,test),
			    "Copy construction test"));
  suite->add(make_test_case(boost::bind(&ObjectHandleTest::test_move_construction,test),
			    "Move construction test"));

  return suite;

}

bool init_function()
{

  framework::master_test_suite().add(BOOST_TEST_CASE(&test_default_construction));
  framework::master_test_suite().add(create_test_suite(hdf5::ObjectHandle::Type::FILE));
  framework::master_test_suite().add(create_test_suite(hdf5::ObjectHandle::Type::DATATYPE));
  framework::master_test_suite().add(create_test_suite(hdf5::ObjectHandle::Type::DATASPACE));
  framework::master_test_suite().add(create_test_suite(hdf5::ObjectHandle::Type::GROUP));
  framework::master_test_suite().add(create_test_suite(hdf5::ObjectHandle::Type::DATASET));
  framework::master_test_suite().add(create_test_suite(hdf5::ObjectHandle::Type::ATTRIBUTE));
  framework::master_test_suite().add(create_test_suite(hdf5::ObjectHandle::Type::PROPERTY_LIST));
  //framework::master_test_suite().add(create_test_suite(hdf5::ObjectHandle::Type::PROPERTY_LIST_CLASS));
  framework::master_test_suite().add(create_test_suite(hdf5::ObjectHandle::Type::ERROR_MESSAGE));
  framework::master_test_suite().add(create_test_suite(hdf5::ObjectHandle::Type::ERROR_CLASS));
  framework::master_test_suite().add(create_test_suite(hdf5::ObjectHandle::Type::ERROR_STACK));

  return true;
}

int main(int argc,char **argv)
{
  return boost::unit_test::unit_test_main(&init_function,argc,argv);

}


