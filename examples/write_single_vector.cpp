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
// Created on: Oct 10, 2017
//

#include <h5cpp/hdf5.hpp>
#include "vector.hpp"
#include "vector_h5.hpp"

using namespace hdf5;

using DoubleVector = Vector<double>;


int main()
{
  DoubleVector position,velocity;
  velocity = {30.2,-2.3,20.3};
  position = {203.33,203.21,1233.0};

  file::File f = file::create("write_single_vector.h5",file::AccessFlags::TRUNCATE);
  node::Group root_group = f.root();
  auto type = datatype::create<DoubleVector>();
  dataspace::Scalar space;
  node::Dataset position_dataset(root_group,"position",type,space);
  node::Dataset velocity_dataset(root_group,"velocity",type,space);

  std::cout<<"writing position: "<<position<<std::endl;
  std::cout<<"writing velocity: "<<velocity<<std::endl;
  position_dataset.write(position);
  velocity_dataset.write(velocity);


}


