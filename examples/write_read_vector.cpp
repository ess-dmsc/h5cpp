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

int main()
{
  std::string file_name{"write_read_vector.h5"};
  {
    file::File f = file::create(file_name,file::AccessFlags::TRUNCATE);
    node::Group root_group = f.root();

  std::vector<int> data{1,2,3,4,5,6,7};
    node::Dataset dataset = root_group.create_dataset("data",datatype::create<int>(),
                                                    dataspace::create(data));
    dataset.write(data);
  } //File is closed here
  
  {
    file::File f = file::open(file_name);
    node::Group root_group = f.root();
    node::Dataset dataset = root_group.get_dataset("data");
    std::vector<int> input_vector(dataset.dataspace().size());
    dataset.read(input_vector);
    for (auto &element : input_vector) {
      std::cout << element << std::endl;
    }
  }
  return 0;
}


