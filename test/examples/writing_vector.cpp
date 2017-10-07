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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Oct 07, 2017
//
#include <h5cpp/hdf5.hpp>
#include <iostream>
#include <vector>

using namespace hdf5;

using data_type = std::vector<int>;

int main()
{
  file::File f = file::create("writing_vector.h5",file::AccessFlags::TRUNCATE);
  node::Group root_group = f.root();

  data_type data{1,2,3,4};
  node::Dataset dataset = root_group.create_dataset("data",datatype::create<data_type>(),
                                                    dataspace::create(data));
  dataset.write(data);

  return 0;
}


