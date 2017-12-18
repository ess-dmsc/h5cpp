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
// Created on: Oct 4, 2017
//

#include <h5cpp/attribute/attribute.hpp>
#include <h5cpp/dataspace/type.hpp>
#include <h5cpp/datatype/types.hpp>

#include "../fixture.hpp"

using namespace hdf5;

class Attribute : public BasicFixture
{};

TEST_F(Attribute, test_default_construction)
{
  attribute::Attribute a;
  EXPECT_THROW(a.datatype(),std::runtime_error);
  EXPECT_THROW(a.dataspace(),std::runtime_error);
  EXPECT_THROW(a.name(),std::runtime_error);
  EXPECT_FALSE(a.is_valid());
}

TEST_F(Attribute, test_scalar)
{
  attribute::Attribute a;
  EXPECT_NO_THROW(a = root_.attributes.create<int>("test"));
  EXPECT_EQ(a.dataspace().type(),dataspace::Type::SCALAR);
  EXPECT_EQ(a.parent_link().path(),"/");
  dataspace::Scalar space(a.dataspace());


  EXPECT_EQ(a.datatype().get_class(),datatype::Class::INTEGER);
  EXPECT_EQ(a.name(),"test");
  EXPECT_EQ(root_.attributes.size(),1ul);

  EXPECT_NO_THROW(a = root_.attributes.create<float>("test2"));
  EXPECT_EQ(a.dataspace().type(),dataspace::Type::SCALAR);
  EXPECT_EQ(a.datatype().get_class(),datatype::Class::FLOAT);
  EXPECT_EQ(a.name(),"test2");
  EXPECT_EQ(root_.attributes.size(),2ul);
}

TEST_F(Attribute, test_multidim_simple_construction)
{
  attribute::Attribute a;
  EXPECT_NO_THROW(a = root_.attributes.create<int>("test",{1}));
  EXPECT_EQ(a.dataspace().size(),1L);
  EXPECT_EQ(a.name(),"test");
  EXPECT_EQ(a.dataspace().type(),dataspace::Type::SIMPLE);
  dataspace::Simple space(a.dataspace());
  EXPECT_EQ(space.rank(),1);
  EXPECT_EQ(space.current_dimensions()[0],1ul);

  EXPECT_NO_THROW(a = root_.attributes.create<int>("matrix",{3,4}));
  EXPECT_EQ(a.name(),"matrix");
  space = dataspace::Simple(a.dataspace());
  EXPECT_EQ(space.rank(),2);
  EXPECT_EQ(space.current_dimensions()[0],3ul);
  EXPECT_EQ(space.current_dimensions()[1],4ul);

}

TEST_F(Attribute, test_multidim_construction)
{
  attribute::Attribute a;
  dataspace::Simple space{{3,4}};
  auto type = datatype::create<float>();

  EXPECT_NO_THROW(a = root_.attributes.create("test",type,space));
  EXPECT_TRUE(root_.attributes.exists("test"));
  EXPECT_FALSE(root_.attributes.exists("bla"));
  EXPECT_EQ(root_.attributes.size(),1ul);
  EXPECT_EQ(a.name(),"test");
}


TEST_F(Attribute,test_create_from_scalar_value)
{
  auto a = root_.attributes.create_from("test",float(23.4));
  float buffer;
  a.read(buffer);
  EXPECT_EQ(buffer,23.4f);
}

TEST_F(Attribute,test_create_from_vector)
{
  using AttributeData = std::vector<double>;
  AttributeData data{1,2,3,4,5};
  auto a = root_.attributes.create_from("test",data);
  AttributeData buffer(data.size());
  a.read(buffer);
  EXPECT_EQ(buffer,data);
}




