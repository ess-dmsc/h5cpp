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
#include <h5cpp/contrib/stl/stl.hpp>

#include <iostream>
#include <complex>

using namespace hdf5;

using ComplexDouble = std::complex<double>;

int main()
{
  file::File f = file::create("writing_complex.h5",file::AccessFlags::Truncate);
  node::Group root_group = f.root();
  node::Dataset dataset(root_group,"data",datatype::create<ComplexDouble>(),
                                                    dataspace::Scalar());

  //
  // writing a complex number
  //
  ComplexDouble write(1.2,-3.4231);
  std::cout<<"writing: "<<write<<std::endl;
  dataset.write(write);

  //
  // reading a complex number
  //
  ComplexDouble read(0,0);
  dataset.read(read);

  std::cout<<"reading: "<<read<<std::endl;

  return 0;
}


