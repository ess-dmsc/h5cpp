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
// Created on: Oct 08, 2017
//

#include "rgbpixel.hpp"

RGBPixel::RGBPixel():
 red_(0),
 green_(0),
 blue_(0)
{}

RGBPixel::RGBPixel(std::uint8_t red,std::uint8_t green,std::uint8_t blue ):
    red_(red),
    green_(green),
    blue_(blue)
{}

std::uint8_t RGBPixel::red() const
{
  return red_;
}

void RGBPixel::red(std::uint8_t value)
{
  red_ = value;
}


std::uint8_t RGBPixel::green() const
{
  return green_;
}

void RGBPixel::green(std::uint8_t value)
{
  green_ = value;
}


std::uint8_t RGBPixel::blue() const
{
  return blue_;
}

void RGBPixel::blue(std::uint8_t value)
{
  blue_ = value;
}





