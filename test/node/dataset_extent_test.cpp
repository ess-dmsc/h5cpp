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
// Created on: Sep 12, 2017
//
#include <boost/test/unit_test.hpp>
#include <h5cpp/hdf5.hpp>
#include "../fixture.hpp"

using namespace hdf5;

struct TestExtentFixture : public Fixture
{
    node::Dataset fin_data;
    node::Dataset inf_data;
    dataspace::Simple sspace;

    TestExtentFixture():
      Fixture("DatasetTestExtent.h5"),
      fin_data(),
      inf_data()
    {
      auto type = datatype::create<int>();
      property::DatasetCreationList dcpl;
      property::LinkCreationList lcpl;
      property::DatasetAccessList dapl;

      dcpl.layout(property::DatasetLayout::CHUNKED);
      dcpl.chunk({1024});

      dataspace::Simple fin_space({0},{4096});
      fin_data = root_group.create_dataset("fin_data",type,fin_space,lcpl,dcpl,dapl);

      dataspace::Simple inf_space({0},{dataspace::Simple::UNLIMITED});
      inf_data = root_group.create_dataset("inf_data",type,inf_space,lcpl,dcpl,dapl);
    }
};

BOOST_AUTO_TEST_SUITE(DatasetTest)

BOOST_FIXTURE_TEST_SUITE(TestExtent,TestExtentFixture)

BOOST_AUTO_TEST_CASE(test_infinite_extent_absolut)
{
  sspace = inf_data.dataspace();
  BOOST_CHECK_EQUAL(sspace.current_dimensions()[0],0);
  BOOST_CHECK_NO_THROW(inf_data.extent({1000}));
  BOOST_CHECK_NO_THROW(sspace = inf_data.dataspace());
  sspace = inf_data.dataspace();
  BOOST_CHECK_EQUAL(sspace.current_dimensions()[0],1000);
}

BOOST_AUTO_TEST_CASE(test_infinite_extent_relative)
{
  sspace = inf_data.dataspace();
  BOOST_CHECK_EQUAL(sspace.current_dimensions()[0],0);
  BOOST_CHECK_NO_THROW(inf_data.extent(0,123));
  sspace = inf_data.dataspace();
  BOOST_CHECK_EQUAL(sspace.current_dimensions()[0],123);

  BOOST_CHECK_THROW(inf_data.extent(0,-1000),std::runtime_error);
  BOOST_CHECK_THROW(inf_data.extent(1,100),std::runtime_error);
}

BOOST_AUTO_TEST_CASE(test_finite_extent_absolute)
{
  BOOST_CHECK_NO_THROW(fin_data.extent({100}));
  sspace = fin_data.dataspace();
  BOOST_CHECK_EQUAL(sspace.current_dimensions()[0],100);

  BOOST_CHECK_THROW(fin_data.extent({100000}),std::runtime_error);
}

BOOST_AUTO_TEST_CASE(test_finite_extent_relative)
{
  BOOST_CHECK_NO_THROW(fin_data.extent(0,100));
  sspace = fin_data.dataspace();
  BOOST_CHECK_EQUAL(sspace.current_dimensions()[0],100);

  BOOST_CHECK_THROW(fin_data.extent(0,-1000000),std::runtime_error);
  BOOST_CHECK_THROW(fin_data.extent(1,100),std::runtime_error);
  BOOST_CHECK_THROW(fin_data.extent(0,100000),std::runtime_error);
}



BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()



