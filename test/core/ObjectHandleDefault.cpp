
//
// (c) Copyright 2017 DESY,ESS
//               2021 Eugen Wintersberger <eugen.wintersberger@gmail.com>
//
// This file is part of h5cpp.
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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 14, 2017
//
#include <catch2/catch.hpp>
#include <h5cpp/core/object_handle.hpp>
#include <string>
#include <vector>

#include "object_handle_test.hpp"

std::shared_ptr<ObjectHandleTest> create_test(hdf5::ObjectHandle::Type type) {
  switch (type) {
    case hdf5::ObjectHandle::Type::FILE:
      return std::make_unique<FileObjectHandleTest>("test.h5");
    case hdf5::ObjectHandle::Type::DATATYPE:
      return std::make_unique<DatatypeObjectHandleTest>();
    case hdf5::ObjectHandle::Type::DATASPACE:
      return std::make_unique<DataspaceObjectHandleTest>();
    case hdf5::ObjectHandle::Type::GROUP:
      return std::make_unique<GroupObjectHandleTest>(
          "object_handle_group_test.h5");
    case hdf5::ObjectHandle::Type::DATASET:
      return std::make_unique<DatasetObjectHandleTest>(
          "object_handle_dataset_test.h5");
    case hdf5::ObjectHandle::Type::ATTRIBUTE:
      return std::make_unique<AttributeObjectHandleTest>(
          "object_handle_attribute_test.h5");
    case hdf5::ObjectHandle::Type::PROPERTY_LIST:
      return std::make_unique<PropertyListObjectHandleTest>();
    case hdf5::ObjectHandle::Type::PROPERTY_LIST_CLASS:
      return std::make_unique<PropertyListClassObjectHandleTest>();
    case hdf5::ObjectHandle::Type::ERROR_CLASS:
      return std::make_unique<ErrorClassObjectHandleTest>();
    case hdf5::ObjectHandle::Type::ERROR_MESSAGE:
      return std::make_unique<ErrorMessageObjectHandleTest>();
    case hdf5::ObjectHandle::Type::ERROR_STACK:
      return std::make_unique<ErrorStackObjectHandleTest>();
    default:
      return nullptr;
  }
}
SCENARIO("testing object handle construction") {
  GIVEN("a default constructed handle") {
    hdf5::ObjectHandle handle;

    REQUIRE_FALSE(handle.is_valid());
    REQUIRE(handle.get_type() == hdf5::ObjectHandle::Type::BADOBJECT);
    REQUIRE_THROWS_AS(handle.get_reference_count(), std::runtime_error);
    REQUIRE_THROWS_AS(handle.close(), std::runtime_error);
  }

  WHEN("trying to construct a handle from an invalid hid_t") {
    THEN("the constructor will fail") {
      REQUIRE_THROWS_AS(hdf5::ObjectHandle(-1), std::runtime_error);
    }
  }
}

TEST_CASE("testing handle behavior for different object types") {
  auto test = GENERATE(create_test(hdf5::ObjectHandle::Type::FILE));

  SECTION("testing operations") {
    test->test_copy_assignment();
    test->test_move_assignment();
    test->test_copy_construction();
    test->test_move_construction();
    test->test_close_pathology();
    test->test_equality();
  }
}


/*
INSTANTIATE_TEST_CASE_P(
    ObjHandleTest,
    ObjHandleFixture,
    ::testing::Values(hdf5::ObjectHandle::Type::FILE,
                      hdf5::ObjectHandle::Type::DATATYPE,
                      hdf5::ObjectHandle::Type::DATASPACE,
                      hdf5::ObjectHandle::Type::GROUP,
                      hdf5::ObjectHandle::Type::DATASET,
                      hdf5::ObjectHandle::Type::ATTRIBUTE,
                      hdf5::ObjectHandle::Type::PROPERTY_LIST,
                      hdf5::ObjectHandle::Type::ERROR_MESSAGE,
                      hdf5::ObjectHandle::Type::ERROR_CLASS,
                      hdf5::ObjectHandle::Type::ERROR_STACK), );
*/
