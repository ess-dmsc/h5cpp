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
#include "utilities.hpp"
#include "../../utilities.hpp"

using namespace hdf5;

SCENARIO("testing pniio bool compatibility") {
  auto file =
      file::open("../../pniio_test_boolattr.h5", file::AccessFlags::ReadOnly);
  auto root = file.root();

  GIVEN("a datast with a scalar dataspace storing a true value") {
    auto dataset = node::get_dataset(root, "ds_bool_scalar_true");
    AND_GIVEN("a bool buffer") {
      bool buffer;
      WHEN("reading the data to the buffer") {
        dataset.read(buffer);
        THEN("the buffer must be true") { REQUIRE(buffer); }
      }
    }
    AND_GIVEN("an EBool buffer") {
      datatype::EBool buffer;
      WHEN("reading the data") {
        // does not work because of a bug similar to #309, #347
        // dstrue.read(buffer);
        dataset.read(buffer, dataset.datatype(), dataspace::Simple{{1}},
                     dataset.dataspace());
        THEN("the buffer must be TRUE") {
          REQUIRE(buffer == datatype::EBool::True);
        }
      }
    }
  }

  GIVEN("as dataset with a scalar datspace storing a false value") {
    auto dataset = node::get_dataset(root, "ds_bool_scalar_false");
    AND_GIVEN("a bool read buffer") {
      bool buffer;
      WHEN("reading the dataset to the buffer") {
        dataset.read(buffer);
        THEN("the buffer must be false") { REQUIRE_FALSE(buffer); }
      }
    }
    AND_GIVEN("an EBool buffer") {
      datatype::EBool buffer;
      WHEN("reading the dataset to the buffer") {
        // does not work because of a bug similar to #309, #347
        // dsfalse.read(buffer2);
        dataset.read(buffer, dataset.datatype(), dataspace::Simple{{1}},
                     dataset.dataspace());
        THEN("the buffer must be FALSE") {
          REQUIRE(buffer == datatype::EBool::False);
        }
      }
    }
  }

  GIVEN("a dataset storing a bool array") {
    auto dataset = node::get_dataset(root, "ds_bool_array");
    THEN("the datasets' datatype must be of class INTEGER") {
      REQUIRE(dataset.datatype().get_class() == datatype::Class::Integer);
      AND_THEN("the size of the datasets' datatype must be 1") {
        REQUIRE(dataset.datatype().size() == 1);
      }
    }
    AND_GIVEN("a unsigned char vector buffer") {
      UChars buffer(4);
      WHEN("reading the dataset to the buffer") {
        dataset.read(buffer);
        THEN("the result must be {0, 1, 1, 0}") {
          REQUIRE_THAT(buffer, Catch::Matchers::Equals(UChars{0, 1, 1, 0}));
        }
      }
    }
    AND_GIVEN("an EBool vector buffer") {
      EBools buffer(4);
      WHEN("reading the dataset to the buffer") {
        dataset.read(buffer, dataset.datatype(), dataspace::Simple{{4}},
                     dataset.dataspace());
        THEN("the result must be {FALSE, TRUE, TRUE, FALSE}") {
          EBools expected{datatype::EBool::False, datatype::EBool::True,
                          datatype::EBool::True, datatype::EBool::False};
          REQUIRE_THAT(buffer, Catch::Matchers::Equals(expected));
        }
      }
    }
  }
}
