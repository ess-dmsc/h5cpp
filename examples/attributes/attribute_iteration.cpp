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


//
// the attribute manager attached to each node object follows the standard
// STL iterable interface and thus can be used along with any STL algorithm.
//
int main()
{
  file::File file = file::create("attribute_iteration.h5",file::AccessFlags::TRUNCATE);
  node::Group root_group = file.root();

  root_group.attributes.create<int>("index");
  root_group.attributes.create<std::string>("author");
  root_group.attributes.create<double>("temperature");

  for(auto attribute: root_group.attributes)
    std::cout<<"attribute: "<<attribute.name()<<std::endl;

  std::for_each(root_group.attributes.begin(),root_group.attributes.end(),
                [](const attribute::Attribute &attribute)
                { std::cout<<"datatype: "<<attribute.datatype().get_class()<<std::endl;});

  return 0;
}
