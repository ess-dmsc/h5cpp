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
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Testing link creation property list implementation
#include <boost/test/unit_test.hpp>
#include <h5cpp/property/link_creation_list.hpp>
#include <h5cpp/property/class.hpp>
#include <h5cpp/type/types.hpp>

namespace pl = hdf5::property;
namespace tp = hdf5::type;

BOOST_AUTO_TEST_SUITE(LinkCreationList_test)

  BOOST_AUTO_TEST_CASE(test_default_construction)
  {
    pl::LinkCreationList lcpl;
    BOOST_CHECK(lcpl.get_class() == pl::kLinkCreate);
  }

  BOOST_AUTO_TEST_CASE(test_intermediate_gruop_creation)
  {
    pl::LinkCreationList lcpl;
    BOOST_CHECK_NO_THROW(lcpl.enable_intermediate_group_creation());
    BOOST_CHECK(lcpl.intermediate_group_creation());
    BOOST_CHECK_NO_THROW(lcpl.disable_intermediate_group_creation());
    BOOST_CHECK(lcpl.intermediate_group_creation());
  }

  BOOST_AUTO_TEST_CASE(test_character_encoding)
  {
    pl::LinkCreationList lcpl;
    BOOST_CHECK_NO_THROW(lcpl.character_encoding(tp::CharacterEncoding::ASCII));
    BOOST_CHECK(lcpl.character_encoding() == tp::CharacterEncoding::ASCII);

    BOOST_CHECK_NO_THROW(lcpl.character_encoding(tp::CharacterEncoding::UTF8));
    BOOST_CHECK(lcpl.character_encoding() == tp::CharacterEncoding::UTF8);
  }

BOOST_AUTO_TEST_SUITE_END()
