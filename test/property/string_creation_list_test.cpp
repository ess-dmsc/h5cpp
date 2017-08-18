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
// Created on: Aug 18, 2017
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Testing string creation property list implementation
#include <boost/test/unit_test.hpp>

#include <h5cpp/property/string_creation_list.hpp>

namespace prop = hdf5::property;
namespace type = hdf5::type;

BOOST_AUTO_TEST_SUITE(StringCreationListTest)

  BOOST_AUTO_TEST_CASE(test_default_construction)
  {
    prop::StringCreationList scl;
    BOOST_CHECK(scl.get_class() == prop::kStringCreate);
  }

  BOOST_AUTO_TEST_CASE(test_encoding)
  {
    prop::StringCreationList scl;
    BOOST_CHECK_NO_THROW(scl.character_encoding(type::CharacterEncoding::ASCII));
    BOOST_CHECK(scl.character_encoding()==type::CharacterEncoding::ASCII);

    BOOST_CHECK_NO_THROW(scl.character_encoding(type::CharacterEncoding::UTF8));
    BOOST_CHECK(scl.character_encoding()==type::CharacterEncoding::UTF8);
  }
BOOST_AUTO_TEST_SUITE_END()
