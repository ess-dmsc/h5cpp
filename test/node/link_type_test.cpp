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

TEST(Link, test_string_representation)
{
  std::stringstream stream;

  stream.str(std::string());
  stream<<node::LinkType::ERROR;
  EXPECT_EQ(stream.str(),  "ERROR");

  stream.str(std::string());
  stream<<node::LinkType::EXTERNAL;
  EXPECT_EQ(stream.str(), "EXTERNAL");

  stream.str(std::string());
  stream<<node::LinkType::HARD;
  EXPECT_EQ(stream.str(), "HARD");

  stream.str(std::string());
  stream<<node::LinkType::SOFT;
  EXPECT_EQ(stream.str(), "SOFT");
}

TEST(Link, test_value)
{
  EXPECT_EQ(static_cast<H5L_type_t>(node::LinkType::ERROR),
                    H5L_TYPE_ERROR);
  EXPECT_EQ(static_cast<H5L_type_t>(node::LinkType::HARD),
                      H5L_TYPE_HARD);
  EXPECT_EQ(static_cast<H5L_type_t>(node::LinkType::SOFT),
                      H5L_TYPE_SOFT);
  EXPECT_EQ(static_cast<H5L_type_t>(node::LinkType::EXTERNAL),
                      H5L_TYPE_EXTERNAL);

}


