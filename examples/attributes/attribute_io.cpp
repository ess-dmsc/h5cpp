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

void author_attribute(const node::Node node)
{
  //
  // single shot attribute creation and writing
  //
  node.attributes.create<std::string>("author").write("Eugen Wintersberger");

  //
  // reading data from the attribute
  //
  auto attribute = node.attributes["author"];
  std::string author;
  attribute.read(author);
  std::cout<<"Author: "<<author<<std::endl;
}

void tensor_attribute(const node::Node node)
{
  std::vector<double> data{1,2,3,4,5,6,7,8,9};

  // creating a multidimensional attribute
  auto attribute = node.attributes.create<double>("tensor",Dimensions{3,3});
  attribute.write(data);

  std::vector<double> read(9);
  attribute.read(read);
  std::for_each(read.begin(),read.end(),[](double value) { std::cout<<value<<" ";});
  std::cout<<std::endl;
}

int main()
{
  file::File file = file::create("attribute_io.h5",file::AccessFlags::Truncate);
  node::Group root_group = file.root();

  author_attribute(root_group);
  tensor_attribute(root_group);

  return 0;
}
