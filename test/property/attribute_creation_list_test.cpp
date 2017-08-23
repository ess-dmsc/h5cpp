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
#define BOOST_TEST_MODULE Test attribute creation property list implementation
#include <boost/test/unit_test.hpp>
#include <h5cpp/property/attribute_creation_list.hpp>
#include <h5cpp/property/class.hpp>
#include <h5cpp/datatype/types.hpp>

namespace pl = hdf5::property;
namespace tp = hdf5::datatype;

BOOST_AUTO_TEST_SUITE(AttributeCreationList_test)

  BOOST_AUTO_TEST_CASE(test_default_construction)
  {
    pl::AttributeCreationList acpl;
    BOOST_CHECK(acpl.get_class() == pl::kAttributeCreate);
  }

  BOOST_AUTO_TEST_CASE(test_character_encoding)
  {
    pl::AttributeCreationList acpl;
    BOOST_CHECK_NO_THROW(acpl.character_encoding(tp::CharacterEncoding::ASCII));
    BOOST_CHECK(acpl.character_encoding()==tp::CharacterEncoding::ASCII);

    BOOST_CHECK_NO_THROW(acpl.character_encoding(tp::CharacterEncoding::UTF8));
    BOOST_CHECK(acpl.character_encoding()==tp::CharacterEncoding::UTF8);
  }

BOOST_AUTO_TEST_SUITE_END()
