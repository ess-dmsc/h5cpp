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
// Created on: Aug 24, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

TEST(Scalar, test_default_construction) {
  dataspace::Scalar space;
  EXPECT_EQ(space.size(), 1);
  EXPECT_EQ(space.type(), dataspace::Type::SCALAR);

  dataspace::Scalar space2(ObjectHandle(H5Screate(H5S_SCALAR)));
  EXPECT_EQ(space2.type(), dataspace::Type::SCALAR);
}

TEST(Scalar, test_bad_construction) {
  dataspace::Dataspace s(ObjectHandle(H5Screate(H5S_SIMPLE)));
  EXPECT_THROW((dataspace::Scalar(s)), std::runtime_error);
}

TEST(Scalar, test_copy_construction) {
  dataspace::Scalar space1;
  dataspace::Scalar space2(space1);
}

TEST(Scalar, test_copy_construction_from_dataspace) {
  dataspace::Scalar space;
  dataspace::Dataspace &dspace = space;
  dataspace::Scalar space2(dspace);
}

TEST(Scalar, test_copy_assignment_from_dataspace) {
  dataspace::Scalar space;
  dataspace::Dataspace &dspace = space;
  dataspace::Scalar space2;

  space2 = dspace;
  EXPECT_EQ(space2.type(), dataspace::Type::SCALAR);
}


