//
// (c) Copyright 2018 DESY,ESS
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
// Author: Jan Kotanski <jan,kotanski@desy.de>
//         Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Jul 2, 2018
//
#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>
#include "../../utilities.hpp"
#include "utilities.hpp"

using namespace hdf5;

SCENARIO("testing h5py compatiable booleans") {
  auto h5py_file =
      file::open("../../h5py_test_boolattr.h5", file::AccessFlags::ReadOnly);
  auto root_group = h5py_file.root();

  // =========================================================================
  // reading a single true value from a dataset with a scalar dataspace
  // =========================================================================
  GIVEN("given a dataset with a scalar dataspace storing true") {
    auto dataset = node::get_dataset(root_group, "ds_bool_scalar_true");
    THEN("the class of the datasets' datatype is ENUM") {
      REQUIRE(dataset.datatype().get_class() == datatype::Class::Enum);
      AND_THEN("the dataset has a bloolean datatype") {
        REQUIRE(datatype::is_bool(datatype::Enum(dataset.datatype())));
      }
    }
    AND_GIVEN("given a scalar bool buffer") {
      bool buffer;
      WHEN("reading the data") {
        dataset.read(buffer);
        THEN("the content of the read buffer must be true") { REQUIRE(buffer); }
      }
    }
    AND_GIVEN("and given a scalar EBools buffer") {
      datatype::EBool buffer;
      WHEN("reading the data from the dataset") {
        dataset.read(buffer);
        THEN("the result must be true") { REQUIRE(static_cast<bool>(buffer) == true); }
        THEN("the result must be 1") { REQUIRE(buffer == 1); }
        THEN("the result must be EBool::True") {
          REQUIRE(buffer == datatype::EBool::True);
        }
      }
    }
  }

  // ==========================================================================
  // reading a single false value from a dataset with a scalar dataspace
  // ==========================================================================
  GIVEN("a dataset with a scalar dataspace and one false value stored") {
    auto dataset = node::get_dataset(root_group, "ds_bool_scalar_false");
    AND_GIVEN("a scalar bool buffer") {
      bool buffer;
      WHEN("reading the data") {
        dataset.read(buffer);
        THEN("the content of the read buffer must be false") {
          REQUIRE_FALSE(buffer);
        }
      }
    }
    AND_GIVEN("a scalar EBool buffer") {
      datatype::EBool buffer;
      WHEN("reading the data from the dataset") {
        dataset.read(buffer);
        THEN("the result must be false") { REQUIRE_FALSE(buffer); }
        THEN("the result must be 0") { REQUIRE(buffer == 0); }
        THEN("the result must be EBool::False") {
          REQUIRE(buffer == datatype::EBool::False);
        }
      }
    }
  }

  // ==========================================================================
  // reading a single true value from a dataset with a simple dataspace
  // ==========================================================================
  GIVEN("a dataspace with a simple dataspace and one true value stored") {
    auto dataset = node::get_dataset(root_group, "ds_bool_simple_true");
    AND_GIVEN("a bool read buffer") {
      bool buffer;
      WHEN("reading the data") {
        dataset.read(buffer);
        THEN("the content of the read buffer must be true") { REQUIRE(buffer); }
      }
    }
    AND_GIVEN("an EBool read buffer") {
      datatype::EBool buffer;
      WHEN("reading the data") {
        dataset.read(buffer);
        THEN("the result must be true") { REQUIRE(static_cast<bool>(buffer) == true); }
        THEN("the result must be 1") { REQUIRE(buffer == 1); }
        THEN("the result must be EBool::True") {
          REQUIRE(buffer == datatype::EBool::True);
        }
      }
    }
  }

  // ==========================================================================
  // reading a single false value froma dataset with a simple dataspace
  // ==========================================================================
  GIVEN("a datapsace with a simple dataspace and one false value stored") {
    auto dataset = node::get_dataset(root_group, "ds_bool_simple_false");
    AND_GIVEN("a bool read buffer") {
      bool buffer;
      WHEN("reading the data") {
        dataset.read(buffer);
        THEN("the content of the read buffer must be false") {
          REQUIRE_FALSE(buffer);
        }
      }
    }
    AND_GIVEN("an EBool read buffer") {
      datatype::EBool buffer;
      WHEN("reading the data") {
        dataset.read(buffer);
        THEN("the result must be false") { REQUIRE_FALSE(buffer); }
        THEN("the result must be 0") { REQUIRE(buffer == 0); }
        THEN("the result must be EBool::False") {
          REQUIRE(buffer == datatype::EBool::False);
        }
      }
    }
  }

  // ============================================================================
  // testing reading boolean array data from a dataset
  // ============================================================================
  GIVEN("a dataset storing an array of bools") {
    auto dataset = node::get_dataset(root_group, "ds_bool_array");
    THEN("the datasets' data type will be ENUM") {
      REQUIRE(dataset.datatype().get_class() == datatype::Class::Enum);
      AND_THEN("the size of the datatype will be 1") {
        REQUIRE(dataset.datatype().size() == 1ul);
      }
    }

    // --------------------------------------------------------------------------
    // reading the data to an unsigned char vector
    //
    // This is a workaround as there is no implementation for std::vector<bool>
    // --------------------------------------------------------------------------
    AND_GIVEN("a unsigned char vector read buffer") {
      UChars buffer(4);
      WHEN("reading the data from the dataset") {
        dataset.read(buffer);
        THEN("the result will be as expected") {
          UChars expected = {0, 1, 1, 0};
          REQUIRE_THAT(buffer, Catch::Matchers::Equals(expected));
        }
      }
    }
    // --------------------------------------------------------------------------
    // reading the data to an EBool vector
    // --------------------------------------------------------------------------
    AND_GIVEN("a EBool vector read buffer") {
      EBools buffer(4);
      WHEN("reading the data from the dataset") {
        dataset.read(buffer);
        THEN("the result will be {FALSE, TRUE, TRUE, FALSE} ") {
          EBools expected{datatype::EBool::False, datatype::EBool::True,
                          datatype::EBool::True, datatype::EBool::False};
          REQUIRE_THAT(buffer, Catch::Matchers::Equals(expected));
        }
      }
    }
  }
}

