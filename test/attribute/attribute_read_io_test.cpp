//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5cpp.
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
// Author: Jan Kotanski <jan.kotanski@desy.de>
// Created on: Jun 19, 2018
//
#include <gtest/gtest.h>
#include <h5cpp/hdf5.hpp>
#include <string>

using namespace hdf5;

class AttributeReadIO: public testing::Test
{};

TEST_F(AttributeReadIO, read_string_scalar_20)
{

  auto file = file::create("AttributeReadIO.h5",
			   file::AccessFlags::TRUNCATE);
  auto r = file.root();
  std::string data = "hello";

  datatype::String fixed_type = datatype::String::fixed(20);

  auto a = r.attributes.create("scalar20", fixed_type, dataspace::Scalar());
  a.write(data, fixed_type);
  std::string buffer;
  a.read(buffer); // causes terminate called after throwing an instance of 'std::bad_alloc'
  a.read(buffer, a.datatype());
  std::cout << buffer << std::endl;
  file.close();
}

TEST_F(AttributeReadIO, read_string_scalar_var)
{

  auto file = file::create("AttributeReadIO.h5",
			   file::AccessFlags::TRUNCATE);
  auto r = file.root();
  std::string data = "hello";

  datatype::String var_type = datatype::String::variable();

  auto a2 = r.attributes.create("scalarvar", var_type, dataspace::Scalar());
  a2.write(data, var_type);
  std::string buffer2;
  a2.read(buffer2);
  a2.read(buffer2, a2.datatype());
  std::cout << buffer2 << std::endl;
  file.close();
}

TEST_F(AttributeReadIO, read_string_simple_var)
{

  auto file = file::create("AttributeReadIO.h5",
			   file::AccessFlags::TRUNCATE);
  auto r = file.root();
  std::string data = "hello";

  datatype::String var_type = datatype::String::variable();

  auto a3 = r.attributes.create("simplevar", var_type, dataspace::Simple({1}));
  a3.write(data, var_type);
  std::string buffer3;
  a3.read(buffer3);
  a3.read(buffer3, a3.datatype());
  std::cout << buffer3 << std::endl;
  file.close();
}

TEST_F(AttributeReadIO, read_string_simple_20)
{

  auto file = file::create("AttributeReadIO.h5",
			   file::AccessFlags::TRUNCATE);
  auto r = file.root();
  std::string data = "hello";

  datatype::String fixed_type = datatype::String::fixed(20);

  auto a4 = r.attributes.create("simple20", fixed_type, dataspace::Simple({1}));
  a4.write(data, fixed_type);
  std::string buffer4;
  a4.read(buffer4); // causes terminate called after throwing an instance of 'std::bad_alloc'
  a4.read(buffer4, a4.datatype());
  std::cout << buffer4 << std::endl;

  file.close();
}


TEST_F(AttributeReadIO, read_string_array_simple_20)
{

  auto file = file::create("AttributeReadIO.h5",
			   file::AccessFlags::TRUNCATE);
  auto r = file.root();
  std::string data = "hello";

  datatype::String fixed_type = datatype::String::fixed(20);

  auto a5 = r.attributes.create("simple20x", fixed_type, hdf5::dataspace::Simple({4}));
  a5.write(vec_data, fixed_type);
  std::vector<std::string> buffer5(4);
  a5.read(buffer5); // causes terminate called after throwing an instance of 'std::bad_alloc'
  a5.read(buffer5, a5.datatype());
  std::cout << buffer5[0] << " " << buffer5[1] << " "
	<< buffer5[2] << " " << buffer5[3] << " " << std::endl;

  file.close();
}


TEST_F(AttributeReadIO, read_float_array)
{

  auto file = file::create("AttributeReadIO.h5",
			   file::AccessFlags::TRUNCATE);
  auto r = file.root();
  auto floattype = hdf5::datatype::create<float>();
  auto f6 = r.attributes.create("float", floattype, hdf5::dataspace::Simple({4}));
  f6.write(fvec_data, floattype);
  std::vector<float> buffer6(4);
  f6.read(buffer6);
  f6.read(buffer6, f6.datatype());
  std::cout << buffer6[0] << " " << buffer6[1] << " "
	<< buffer6[2] << " " << buffer6[3] << " " << std::endl;

}
