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
// Created on: Oct 6, 2017
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testing compound data type
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <h5cpp/datatype/compound.hpp>
#include <h5cpp/datatype/float.hpp>
#include <h5cpp/datatype/factory.hpp>

using namespace hdf5;

struct complex_struct
{
  double real;
  double imag;

};

BOOST_AUTO_TEST_SUITE(CompoundTest)

BOOST_AUTO_TEST_CASE(test_default_construction)
{
  datatype::Compound type;
  BOOST_CHECK_THROW(type.field_index("real"),std::runtime_error);
  BOOST_CHECK_THROW(type.field_index(0),std::runtime_error);

}

BOOST_AUTO_TEST_CASE(test_complex_number)
{
  datatype::Compound type(sizeof(complex_struct));
  BOOST_CHECK_NO_THROW(type.insert("real",HOFFSET(complex_struct,real),datatype::create<double>()));
  BOOST_CHECK_NO_THROW(type.insert("imag",HOFFSET(complex_struct,imag),datatype::create<double>()));
}

BOOST_AUTO_TEST_CASE(test_pixel_type)
{

}

BOOST_AUTO_TEST_SUITE_END()



