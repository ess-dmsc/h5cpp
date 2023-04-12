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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 14, 2017
//

#include "object_handle_test.hpp"
#ifdef H5CPP_CATCH2_V2
#include <catch2/catch.hpp>
#else
#include <catch2/catch_all.hpp>
#endif

ObjectHandleTest::ObjectHandleTest(hdf5::ObjectHandle::Type type)
    : type_(type) {}

ObjectHandleTest::~ObjectHandleTest() {}

void ObjectHandleTest::test_copy_construction() {
  hdf5::ObjectHandle handle(this->create_object());
  REQUIRE(handle.is_valid());
  REQUIRE(handle.get_type() == get_type());
  REQUIRE(handle.get_reference_count() == 1);

  hdf5::ObjectHandle handle2(handle);
  REQUIRE(handle.is_valid());
  REQUIRE(handle2.is_valid());
  REQUIRE(handle.get_reference_count() == 2);
  REQUIRE(handle2.get_reference_count() == 2);
}

void ObjectHandleTest::test_move_construction() {
  hdf5::ObjectHandle handle(create_object());
  hdf5::ObjectHandle handle2(std::move(handle));
  REQUIRE(handle2.is_valid());
  REQUIRE(handle2.get_reference_count() == 1);
}

void ObjectHandleTest::test_copy_assignment() {
  hdf5::ObjectHandle handle(create_object());
  hdf5::ObjectHandle handle2;

  handle2 = handle;
  REQUIRE(handle.is_valid());
  REQUIRE(handle2.is_valid());
  REQUIRE(handle.get_reference_count() == 2);
  REQUIRE(handle2.get_reference_count() == 2);

  handle = handle2;
  REQUIRE(handle.is_valid());
  REQUIRE(handle2.is_valid());
  REQUIRE(handle.get_reference_count() == 2);
  REQUIRE(handle2.get_reference_count() == 2);
}

void ObjectHandleTest::test_move_assignment() {
  hdf5::ObjectHandle handle(create_object());
  hdf5::ObjectHandle handle2;

  handle2 = std::move(handle);
  REQUIRE_FALSE(handle.is_valid());
  REQUIRE(handle2.is_valid());
  REQUIRE(handle2.get_reference_count() == 1);

  hdf5::ObjectHandle handle3 = handle2;
  handle2 = std::move(handle3);
  REQUIRE_FALSE(handle3.is_valid());
  REQUIRE(handle2.is_valid());
  REQUIRE(handle2.get_reference_count() == 1);
}

void ObjectHandleTest::test_close_pathology() {
  hdf5::ObjectHandle handle(create_object());
  REQUIRE_NOTHROW(handle.close());
  REQUIRE_THROWS_AS(handle.close(), std::runtime_error);

  hdf5::ObjectHandle* h2 = new hdf5::ObjectHandle(create_object());
  REQUIRE(h2->is_valid());
  REQUIRE_NOTHROW(h2->close());
  REQUIRE_NOTHROW((delete h2));
}

void ObjectHandleTest::test_equality() {
  hdf5::ObjectHandle handle(create_object());
  hdf5::ObjectHandle handle2 = handle;
  hdf5::ObjectHandle handle3;

  REQUIRE(handle == handle2);
  REQUIRE(handle != handle3);

  REQUIRE_FALSE(handle != handle2);
  REQUIRE_FALSE(handle == handle3);
}
