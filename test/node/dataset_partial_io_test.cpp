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
// Created on: Oct 11, 2017
//
#include <boost/test/unit_test.hpp>
#include <h5cpp/hdf5.hpp>
#include "../fixture.hpp"

using namespace hdf5;

struct PartialIOFixture : public Fixture
{
    property::LinkCreationList lcpl;
    property::DatasetCreationList dcpl;

    PartialIOFixture():
      Fixture("DatasetPartialIOTest.h5"),
      lcpl(),
      dcpl()
    {
      dcpl.layout(property::DatasetLayout::CHUNKED);
    }
};

BOOST_AUTO_TEST_SUITE(DatasetTest)

BOOST_FIXTURE_TEST_SUITE(PatialIOTest,PartialIOFixture)

BOOST_AUTO_TEST_CASE(test_read_write_scalar_int)
{
  dataspace::Simple space{{0},{dataspace::Simple::UNLIMITED}};
  auto type = datatype::create<int>();
  int write_value = 0,
      read_value = 0;
  dcpl.chunk({1024});

  node::Dataset dset = root_group.create_dataset("data",type,space,lcpl,dcpl);

  dataspace::Hyperslab slab{{0},{1},{1},{1}};

  for(size_t index=0;index<100;index++)
  {
    dset.extent(0,1);
    slab.start(0,index);
    dset.write(write_value,slab);
    dset.read(read_value,slab);
    BOOST_CHECK_EQUAL(write_value,read_value);

  }
}



BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()




