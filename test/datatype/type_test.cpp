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
//   Martin Shetty <martin.shetty@esss.es>
// Created on: Feb 03, 2018
//

#include <gtest/gtest.h>
#include <h5cpp/datatype/types.hpp>

using namespace hdf5;
using namespace hdf5::datatype;

TEST(DatatypeEnum, TypeClass)
{
  std::stringstream stream;

  stream.str(std::string());
  stream << Class::NONE;
  EXPECT_EQ(stream.str(), "NONE");

  stream.str(std::string());
  stream << Class::INTEGER;
  EXPECT_EQ(stream.str(), "INTEGER");

  stream.str(std::string());
  stream << Class::FLOAT;
  EXPECT_EQ(stream.str(), "FLOAT");

  stream.str(std::string());
  stream << Class::TIME;
  EXPECT_EQ(stream.str(), "TIME");

  stream.str(std::string());
  stream << Class::STRING;
  EXPECT_EQ(stream.str(), "STRING");

  stream.str(std::string());
  stream << Class::BITFIELD;
  EXPECT_EQ(stream.str(), "BITFIELD");

  stream.str(std::string());
  stream << Class::OPAQUE;
  EXPECT_EQ(stream.str(), "OPAQUE");

  stream.str(std::string());
  stream << Class::COMPOUND;
  EXPECT_EQ(stream.str(), "COMPOUND");

  stream.str(std::string());
  stream << Class::REFERENCE;
  EXPECT_EQ(stream.str(), "REFERENCE");

  stream.str(std::string());
  stream << Class::ENUM;
  EXPECT_EQ(stream.str(), "ENUM");

  stream.str(std::string());
  stream << Class::VARLENGTH;
  EXPECT_EQ(stream.str(), "VARLENGTH");

  stream.str(std::string());
  stream << Class::ARRAY;
  EXPECT_EQ(stream.str(), "ARRAY");
}

TEST(DatatypeEnum, Order)
{
  std::stringstream stream;

  stream.str(std::string());
  stream << Order::BE;
  EXPECT_EQ(stream.str(), "BE");

  stream.str(std::string());
  stream << Order::LE;
  EXPECT_EQ(stream.str(), "LE");
}

TEST(DatatypeEnum, Sign)
{
  std::stringstream stream;

  stream.str(std::string());
  stream << Sign::TWOS_COMPLEMENT;
  EXPECT_EQ(stream.str(), "TWOS COMPLEMENT");

  stream.str(std::string());
  stream << Sign::UNSIGNED;
  EXPECT_EQ(stream.str(), "UNSIGNED");
}

TEST(DatatypeEnum, Norm)
{
  std::stringstream stream;

  stream.str(std::string());
  stream << Norm::IMPLIED;
  EXPECT_EQ(stream.str(), "IMPLIED");

  stream.str(std::string());
  stream << Norm::MSBSET;
  EXPECT_EQ(stream.str(), "MSBSET");

  stream.str(std::string());
  stream << Norm::NONE;
  EXPECT_EQ(stream.str(), "NONE");
}

TEST(DatatypeEnum, Pad)
{
  std::stringstream stream;

  stream.str(std::string());
  stream << Pad::BACKGROUND;
  EXPECT_EQ(stream.str(), "BACKGROUND");

  stream.str(std::string());
  stream << Pad::ONE;
  EXPECT_EQ(stream.str(), "ONE");

  stream.str(std::string());
  stream << Pad::ZERO;
  EXPECT_EQ(stream.str(), "ZERO");
}

TEST(DatatypeEnum, StringPad)
{
  std::stringstream stream;

  stream.str(std::string());
  stream << StringPad::NULLPAD;
  EXPECT_EQ(stream.str(), "NULLPAD");

  stream.str(std::string());
  stream << StringPad::NULLTERM;
  EXPECT_EQ(stream.str(), "NULLTERM");

  stream.str(std::string());
  stream << StringPad::SPACEPAD;
  EXPECT_EQ(stream.str(), "SPACEPAD");
}


TEST(DatatypeEnum, Direction)
{
  std::stringstream stream;

  stream.str(std::string());
  stream << Direction::ASCEND;
  EXPECT_EQ(stream.str(), "ASCEND");

  stream.str(std::string());
  stream << Direction::DESCEND;
  EXPECT_EQ(stream.str(), "DESCEND");
}

TEST(DatatypeEnum, CharacterEncoding)
{
  std::stringstream stream;

  stream.str(std::string());
  stream << CharacterEncoding::ASCII;
  EXPECT_EQ(stream.str(), "ASCII");

  stream.str(std::string());
  stream << CharacterEncoding::UTF8;
  EXPECT_EQ(stream.str(), "UTF8");
}
