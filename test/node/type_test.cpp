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
// Created on: Sep 11, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

TEST(NodeType, test_string_representation)
{
  std::stringstream stream;

  stream.str(std::string());
  stream<<node::Type::DATASET;
  EXPECT_EQ(stream.str(), "DATASET");

  stream.str(std::string());
  stream<<node::Type::DATATYPE;
  EXPECT_EQ(stream.str(), "DATATYPE");

  stream.str(std::string());
  stream<<node::Type::GROUP;
  EXPECT_EQ(stream.str(), "GROUP");

  stream.str(std::string());
  stream<<node::Type::UNKNOWN;
  EXPECT_EQ(stream.str(), "UNKNOWN");
}

TEST(NodeType, test_values)
{
  EXPECT_EQ(static_cast<H5O_type_t>(node::Type::DATASET),
                    H5O_TYPE_DATASET);
  EXPECT_EQ(static_cast<H5O_type_t>(node::Type::UNKNOWN),
                    H5O_TYPE_UNKNOWN);
  EXPECT_EQ(static_cast<H5O_type_t>(node::Type::DATATYPE),
                    H5O_TYPE_NAMED_DATATYPE);
  EXPECT_EQ(static_cast<H5O_type_t>(node::Type::GROUP),
                    H5O_TYPE_GROUP);
}


