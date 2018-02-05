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
// Author: 
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Feb 03, 2018
//

#include <gtest/gtest.h>
#include <h5cpp/dataspace/type.hpp>

using namespace hdf5;
using namespace hdf5::dataspace;

TEST(DataspaceEnum, Type) {
  std::stringstream stream;

  stream.str(std::string());
  stream << Type::SCALAR;
  EXPECT_EQ(stream.str(), "SCALAR");

  stream.str(std::string());
  stream << Type::SIMPLE;
  EXPECT_EQ(stream.str(), "SIMPLE");

  stream.str(std::string());
  stream << Type::NODATA;
  EXPECT_EQ(stream.str(), "NODATA");
}

TEST(DataspaceEnum, SelectionType) {
  std::stringstream stream;

  stream.str(std::string());
  stream << SelectionType::NONE;
  EXPECT_EQ(stream.str(), "NONE");

  stream.str(std::string());
  stream << SelectionType::POINTS;
  EXPECT_EQ(stream.str(), "POINTS");

  stream.str(std::string());
  stream << SelectionType::HYPERSLAB;
  EXPECT_EQ(stream.str(), "HYPERSLAB");

  stream.str(std::string());
  stream << SelectionType::ALL;
  EXPECT_EQ(stream.str(), "ALL");
}

TEST(DataspaceEnum, SelectionOperation) {
  std::stringstream stream;

  stream.str(std::string());
  stream << SelectionOperation::SET;
  EXPECT_EQ(stream.str(), "SET");

  stream.str(std::string());
  stream << SelectionOperation::OR;
  EXPECT_EQ(stream.str(), "OR");

  stream.str(std::string());
  stream << SelectionOperation::AND;
  EXPECT_EQ(stream.str(), "AND");

  stream.str(std::string());
  stream << SelectionOperation::XOR;
  EXPECT_EQ(stream.str(), "XOR");

  stream.str(std::string());
  stream << SelectionOperation::NOTB;
  EXPECT_EQ(stream.str(), "NOTB");

  stream.str(std::string());
  stream << SelectionOperation::NOTA;
  EXPECT_EQ(stream.str(), "NOTA");

  stream.str(std::string());
  stream << SelectionOperation::APPEND;
  EXPECT_EQ(stream.str(), "APPEND");

  stream.str(std::string());
  stream << SelectionOperation::PREPEND;
  EXPECT_EQ(stream.str(), "PREPEND");
}
