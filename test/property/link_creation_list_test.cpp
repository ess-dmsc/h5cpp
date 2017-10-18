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
// Created on: Aug 21, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/property/link_creation_list.hpp>
#include <h5cpp/property/class.hpp>
#include <h5cpp/datatype/types.hpp>

namespace pl = hdf5::property;
namespace tp = hdf5::datatype;

TEST(LinkCreationList, test_default_construction)
{
  pl::LinkCreationList lcpl;
  EXPECT_TRUE(lcpl.get_class() == pl::kLinkCreate);
}

TEST(LinkCreationList, test_intermediate_gruop_creation)
{
  pl::LinkCreationList lcpl;
  EXPECT_NO_THROW(lcpl.enable_intermediate_group_creation());
  EXPECT_TRUE(lcpl.intermediate_group_creation());
  EXPECT_NO_THROW(lcpl.disable_intermediate_group_creation());
  EXPECT_TRUE(lcpl.intermediate_group_creation());
}

TEST(LinkCreationList, test_character_encoding)
{
  pl::LinkCreationList lcpl;
  EXPECT_NO_THROW(lcpl.character_encoding(tp::CharacterEncoding::ASCII));
  EXPECT_TRUE(lcpl.character_encoding() == tp::CharacterEncoding::ASCII);

  EXPECT_NO_THROW(lcpl.character_encoding(tp::CharacterEncoding::UTF8));
  EXPECT_TRUE(lcpl.character_encoding() == tp::CharacterEncoding::UTF8);
}


