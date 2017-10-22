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
// Created on: Oct 22, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/dataspace/dataspace.hpp>

using namespace hdf5;
using namespace hdf5::dataspace;

TEST(Dataspace, default_construction)
{
  Dataspace space;
  EXPECT_THROW(space.size(), std::runtime_error);
  EXPECT_THROW(space.type(), std::runtime_error);
//  EXPECT_EQ(space.type(), Type::NODATA);
  EXPECT_FALSE(space.is_valid());
}

TEST(Dataspace, copy_construction)
{
//  Dataspace space1;
//  Dataspace space2(space1);
}

TEST(Dataspace, copy_construction_from_dataspace)
{
//  Dataspace space;
//  Dataspace &dspace = space;
//  Dataspace space2(dspace);
}

TEST(Dataspace, copy_assignment_from_dataspace)
{
//  Dataspace space;
//  Dataspace &dspace = space;
//  Dataspace space2;

//  space2 = dspace;
//  EXPECT_EQ(space2.type(),Type::SCALAR);
}


