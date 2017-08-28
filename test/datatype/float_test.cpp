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
// Created on: Aug 23, 2017
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Testing floating point type implementation
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <h5cpp/datatype/factory.hpp>
#include <h5cpp/datatype/float.hpp>

namespace type = hdf5::datatype;

using test_types = boost::mpl::list<float,double,long double>;

BOOST_AUTO_TEST_SUITE(Float_test)

BOOST_AUTO_TEST_CASE_TEMPLATE(test_construction,T,test_types)
{
  auto t = type::create<T>();
  BOOST_CHECK((std::is_same<decltype(t),type::Float>::value));
  BOOST_CHECK(t.get_class()==type::Class::FLOAT);
  BOOST_CHECK_EQUAL(t.size(),sizeof(T));

}
BOOST_AUTO_TEST_SUITE_END()
