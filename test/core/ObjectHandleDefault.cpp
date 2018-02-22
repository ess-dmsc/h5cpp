
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
// Created on: Aug 14, 2017
//
#include <gtest/gtest.h>
#include <h5cpp/core/object_handle.hpp>
#include <vector>
#include <string>

#include "object_handle_test.hpp"

namespace {
#if GTEST_HAS_PARAM_TEST

using ::testing::TestWithParam;
using ::testing::Values;

class ObjHandleFixture : public TestWithParam<hdf5::ObjectHandle::Type>
{
  public:
    virtual ~ObjHandleFixture()
    {
      delete test_;
    }

    virtual void SetUp()
    {
      std::stringstream ss;
      ss << GetParam();
      name_ = ss.str();

      switch(GetParam())
      {
      case hdf5::ObjectHandle::Type::FILE:
        test_ = new FileObjectHandleTest("test.h5");
        break;
      case hdf5::ObjectHandle::Type::DATATYPE:
        test_ = new DatatypeObjectHandleTest();
        break;
      case hdf5::ObjectHandle::Type::DATASPACE:
        test_ = new DataspaceObjectHandleTest();
        break;
      case hdf5::ObjectHandle::Type::GROUP:
        test_ = new GroupObjectHandleTest("object_handle_group_test.h5");
        break;
      case hdf5::ObjectHandle::Type::DATASET:
        test_ = new DatasetObjectHandleTest("object_handle_dataset_test.h5");
        break;
      case hdf5::ObjectHandle::Type::ATTRIBUTE:
        test_ = new AttributeObjectHandleTest("object_handle_attribute_test.h5");
        break;
      case hdf5::ObjectHandle::Type::PROPERTY_LIST:
        test_ = new PropertyListObjectHandleTest();
        break;
      case hdf5::ObjectHandle::Type::PROPERTY_LIST_CLASS:
        test_ = new PropertyListClassObjectHandleTest();
        break;
      case hdf5::ObjectHandle::Type::ERROR_CLASS:
        test_ = new ErrorClassObjectHandleTest();
        break;
      case hdf5::ObjectHandle::Type::ERROR_MESSAGE:
        test_ = new ErrorMessageObjectHandleTest();
        break;
      case hdf5::ObjectHandle::Type::ERROR_STACK:
        test_ = new ErrorStackObjectHandleTest();
        break;
      default:
        break;
      }
    }

    virtual void TearDown()
    {
      name_.clear();
      delete test_;
      test_ = NULL;
    }

  protected:
    ObjectHandleTest *test_;
    std::string name_;
};

TEST(ObjHandleTest, DefaultConstruction)
{
  hdf5::ObjectHandle handle;

  EXPECT_FALSE(handle.is_valid());
  EXPECT_EQ(handle.get_type(),hdf5::ObjectHandle::Type::BADOBJECT);
  EXPECT_THROW(handle.get_reference_count(),std::runtime_error);
  EXPECT_THROW(handle.close(),std::runtime_error);
}

TEST_P(ObjHandleFixture, Types)
{
  //This line does not help with output :(
  ::testing::Test::RecordProperty("Type", name_);

  test_->test_copy_assignment();
  test_->test_move_assignment();
  test_->test_copy_construction();
  test_->test_move_construction();
  test_->test_close_pathology();
}

INSTANTIATE_TEST_CASE_P(ObjHandleTest, ObjHandleFixture,
                        ::testing::Values(hdf5::ObjectHandle::Type::FILE,
                                          hdf5::ObjectHandle::Type::DATATYPE,
                                          hdf5::ObjectHandle::Type::DATASPACE,
                                          hdf5::ObjectHandle::Type::GROUP,
                                          hdf5::ObjectHandle::Type::DATASET,
                                          hdf5::ObjectHandle::Type::ATTRIBUTE,
                                          hdf5::ObjectHandle::Type::PROPERTY_LIST,
                                          hdf5::ObjectHandle::Type::ERROR_MESSAGE,
                                          hdf5::ObjectHandle::Type::ERROR_CLASS,
                                          hdf5::ObjectHandle::Type::ERROR_STACK));

//  //hdf5::ObjectHandle::Type::PROPERTY_LIST_CLASS));

#else

// Google Test may not support value-parameterized tests with some
// compilers. If we use conditional compilation to compile out all
// code referring to the gtest_main library, MSVC linker will not link
// that library at all and consequently complain about missing entry
// point defined in that library (fatal error LNK1561: entry point
// must be defined). This dummy test keeps gtest_main linked in.
TEST(DummyTest, ValueParameterizedTestsAreNotSupportedOnThisPlatform) {}

#endif  // GTEST_HAS_PARAM_TEST
} // namespace


