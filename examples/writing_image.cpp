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
#include <h5cpp/h5cpp.hpp>
#include <iostream>
#include <complex>
#include "rgbpixel.hpp"
#include "image.hpp"
#include "image_h5.hpp"

using namespace hdf5;

using RGBImage = Image<RGBPixel>;

int main()
{
  file::File f = file::create("writing_image.h5",file::AccessFlags::Truncate);
  node::Group root_group = f.root();

  RGBImage image(2,3);
  image(0,0) = RGBPixel(0,0,0);
  image(0,1) = RGBPixel(0,0,255);
  image(0,2) = RGBPixel(0,255,0);
  image(1,0) = RGBPixel(255,0,0);
  image(1,1) = RGBPixel(255,255,0);
  image(1,2) = RGBPixel(255,255,255);
  node::Dataset dataset = root_group.create_dataset("mona_lisa",datatype::create<RGBImage>(),
                                                    dataspace::create(image));
  dataset.write(image);

  return 0;
}


