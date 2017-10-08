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
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testing dataset class
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <h5cpp/datatype/datatype.hpp>
#include <h5cpp/property/dataset_creation_list.hpp>
#include <h5cpp/property/dataset_access_list.hpp>
#include <h5cpp/property/link_creation_list.hpp>
#include <h5cpp/property/link_access_list.hpp>
#include <h5cpp/dataspace/simple.hpp>
#include <h5cpp/dataspace/scalar.hpp>
#include <h5cpp/node/dataset.hpp>
#include "../fixture.hpp"

using namespace hdf5;

struct DatasetFixture : public Fixture
{
    DatasetFixture():
      Fixture("DatasetTest.h5")
    {}
};


BOOST_AUTO_TEST_SUITE(DatasetTest)

BOOST_FIXTURE_TEST_SUITE(DatasetCreation,DatasetFixture)

BOOST_AUTO_TEST_CASE(test_default_construction)
{
  node::Dataset dset;

  BOOST_CHECK_THROW(dset.dataspace(),std::runtime_error);
  BOOST_CHECK_THROW(dset.datatype(),std::runtime_error);
  BOOST_CHECK_THROW(dset.extent({10,100}),std::runtime_error);
}

BOOST_AUTO_TEST_CASE(test_scalar_dataset)
{
  node::Dataset dset = root_group.create_dataset("data",datatype::create<int>(),
                                                 dataspace::Scalar());

  BOOST_CHECK_EQUAL(dset.dataspace().type(),dataspace::Type::SCALAR);
  BOOST_CHECK_EQUAL(dset.datatype().get_class(),datatype::Class::INTEGER);

  BOOST_CHECK_THROW(dset.extent({10}),std::runtime_error);
}

BOOST_AUTO_TEST_CASE(test_extensible_dataset_infinite)
{
  dataspace::Simple space({0},{dataspace::Simple::UNLIMITED});
  auto type = datatype::create<float>();
  property::DatasetCreationList dcpl;
  dcpl.layout(property::DatasetLayout::CHUNKED);
  dcpl.chunk({1024});

  node::Dataset dset = root_group.create_dataset("data",type,space,
                                                 property::LinkCreationList(),dcpl);

  for(size_t index=0;index<10;index++)
  {
    dset.extent({index});
    dataspace::Simple new_space = dset.dataspace();
    BOOST_CHECK_EQUAL(new_space.current_dimensions()[0],index);

  }

}

BOOST_AUTO_TEST_CASE(test_extensible_dataset_finite)
{
  dataspace::Simple space({0},{2048});
  auto type = datatype::create<float>();
  property::DatasetCreationList dcpl;
  dcpl.layout(property::DatasetLayout::CHUNKED);
  dcpl.chunk({1024});

  node::Dataset dset = root_group.create_dataset("data",type,space,
                                                  property::LinkCreationList(),dcpl);

  BOOST_CHECK_NO_THROW(dset.extent({512}));
  BOOST_CHECK_EQUAL(dataspace::Simple(dset.dataspace()).current_dimensions()[0],512);
  BOOST_CHECK_THROW(dset.extent({40000}),std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()





