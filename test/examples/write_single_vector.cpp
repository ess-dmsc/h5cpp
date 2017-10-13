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

using vector_type = vector<double>;


int main()
{
  vector_type p,v;
  v = {30.2,-2.3,20.3};
  p = {203.33,203.21,1233.0};
  vector_type x = {1,2,3};

  file::File f = file::create("write_single_vector.h5",file::AccessFlags::TRUNCATE);
  node::Group root_group = f.root();
  auto type = datatype::create<vector_type>();
  dataspace::Scalar space;
  node::Dataset position = root_group.create_dataset("position",type,space);
  node::Dataset velocity = root_group.create_dataset("velocity",type,space);

  position.write(p);
  velocity.write(v);


}


