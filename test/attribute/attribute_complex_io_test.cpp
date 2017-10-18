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
// Created on: Oct 5, 2017
//
#include <gtest/gtest.h>
#include <boost/test/floating_point_comparison.hpp>
#include "attribute_test_fixtures.hpp"
#include <complex>

using namespace hdf5;

namespace hdf5 {
namespace datatype {

template<typename T> class TypeTrait<std::complex<T>>
{
  public:
};

}
}

BOOST_AUTO_TEST_SUITE(AttributeTest)

BOOST_FIXTURE_TEST_SUITE(AttributeComplexIOTest,AttributeFixture)

TEST(TestName,test_complex_scalar)
{

}

TEST(TestName,test_complex_vector)
{

}




