
//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5pp.
//
// h5cpp is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// h5cpp is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  ee the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with h5cpp.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Aug 16, 2017
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Testing property list class implementation
#include <boost/test/unit_test.hpp>
#include <h5cpp/property/class.hpp>
#include <h5cpp/object_handle.hpp>

namespace pl = hdf5::property;

BOOST_AUTO_TEST_SUITE(PropertyListClassTest)

  BOOST_AUTO_TEST_CASE(test_construction)
  {
    pl::Class c(hdf5::ObjectHandle(H5P_ATTRIBUTE_ACCESS));
  }

  BOOST_AUTO_TEST_CASE(test_predefined_classes)
  {
    BOOST_CHECK_EQUAL(pl::kAttributeCreate.name(),"attribute create");
    BOOST_CHECK_EQUAL(pl::kDatasetAccess.name(),"dataset access");
    BOOST_CHECK_EQUAL(pl::kDatasetCreate.name(),"dataset create");
    BOOST_CHECK_EQUAL(pl::kDatasetXfer.name(),"data transfer");
    BOOST_CHECK_EQUAL(pl::kDatatypeAccess.name(),"datatype access");
    BOOST_CHECK_EQUAL(pl::kDatatypeCreate.name(),"datatype create");
    BOOST_CHECK_EQUAL(pl::kFileAccess.name(),"file access");
    BOOST_CHECK_EQUAL(pl::kFileCreate.name(),"file create");
    BOOST_CHECK_EQUAL(pl::kFileMount.name(),"file mount");
    BOOST_CHECK_EQUAL(pl::kGroupAccess.name(),"group access");
    BOOST_CHECK_EQUAL(pl::kGroupCreate.name(),"group create");
    BOOST_CHECK_EQUAL(pl::kLinkAccess.name(),"link access");
    BOOST_CHECK_EQUAL(pl::kLinkCreate.name(),"link create");
    BOOST_CHECK_EQUAL(pl::kObjectCopy.name(),"object copy");
    BOOST_CHECK_EQUAL(pl::kObjectCreate.name(),"object create");
    BOOST_CHECK_EQUAL(pl::kStringCreate.name(),"string create");
  }

  BOOST_AUTO_TEST_CASE(test_equality_operator)
  {
    BOOST_CHECK(pl::kAttributeCreate == pl::kAttributeCreate);
    BOOST_CHECK(pl::kAttributeCreate != pl::kFileAccess);

  }
BOOST_AUTO_TEST_SUITE_END()




