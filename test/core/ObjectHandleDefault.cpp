
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
#include <memory>
#include <string>
#include <vector>

#include "object_handle_test.hpp"

std::shared_ptr<ObjectHandleTest> create_test(hdf5::ObjectHandle::Type type) {
  using ptr_type = std::shared_ptr<ObjectHandleTest>;
  switch (type) {
    case hdf5::ObjectHandle::Type::File:
      return std::make_shared<FileObjectHandleTest>("test.h5");
    case hdf5::ObjectHandle::Type::Datatype:
      return std::make_shared<DatatypeObjectHandleTest>();
    case hdf5::ObjectHandle::Type::Dataspace:
      return std::make_shared<DataspaceObjectHandleTest>();
    case hdf5::ObjectHandle::Type::Group:
      return std::make_shared<GroupObjectHandleTest>("object_handle_group_test.h5");
    case hdf5::ObjectHandle::Type::Dataset:
      return std::make_shared<DatasetObjectHandleTest>("object_handle_dataset_test.h5");
    case hdf5::ObjectHandle::Type::Attribute:
      return std::make_shared<AttributeObjectHandleTest>(
          std::string{"object_handle_attribute_test.h5"});
    case hdf5::ObjectHandle::Type::PropertyList:
      return std::make_shared<PropertyListObjectHandleTest>();
    case hdf5::ObjectHandle::Type::PropertyListClass:
      return std::make_shared<PropertyListClassObjectHandleTest>();
    case hdf5::ObjectHandle::Type::ErrorClass:
      return std::make_shared<ErrorClassObjectHandleTest>();
    case hdf5::ObjectHandle::Type::ErrorMessage:
      return std::make_shared<ErrorMessageObjectHandleTest>();
    case hdf5::ObjectHandle::Type::ErrorStack:
      return std::make_shared<ErrorStackObjectHandleTest>();
    default:
      return ptr_type(nullptr);
  }
}
SCENARIO("testing object handle construction") {
  GIVEN("a default constructed handle") {
    hdf5::ObjectHandle handle;

    REQUIRE_FALSE(handle.is_valid());
    REQUIRE(handle.get_type() == hdf5::ObjectHandle::Type::BadObject);
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
  using Type = hdf5::ObjectHandle::Type;
  auto test = GENERATE(
      //create_test(Type::File),          create_test(Type::Datatype),
      //create_test(Type::Dataspace),     create_test(Type::Group),
      //create_test(Type::Dataset),       
      create_test(Type::Attribute),
      create_test(Type::PropertyList), create_test(Type::ErrorMessage),
      create_test(Type::ErrorClass),   create_test(Type::ErrorStack));

  SECTION("testing operations") {
      test->test_copy_assignment();
      test->test_move_assignment();
      test->test_copy_construction();
      test->test_move_construction();
      test->test_close_pathology();
      test->test_equality();
  }
}
