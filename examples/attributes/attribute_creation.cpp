//
// (c) Copyright 2018 DESY,ESS
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
// Created on: Jul 2, 2018
//

#include <h5cpp/hdf5.hpp>

using namespace hdf5;

int main()
{
  file::File file = file::create("attribute_creation.h5",file::AccessFlags::TRUNCATE);
  node::Group root_group = file.root();

  auto author = root_group.attributes.create<std::string>("author");
  author.write("Eugen Wintersberger");

  root_group.attributes.create<int>("index");

  auto tensor_type = datatype::create<double>();
  auto tensor_space = dataspace::Simple(Dimensions{6,6});
  root_group.attributes.create("elasticity",tensor_type,tensor_space);


  return 0;
}
