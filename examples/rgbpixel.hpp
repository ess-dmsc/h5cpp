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
// Created on: Sep 14, 2017
//
#pragma once

#include <cstdint>

class RGBPixel
{
  private:
   std::uint8_t red_;
   std::uint8_t green_;
   std::uint8_t blue_;
  public:
   RGBPixel();
   RGBPixel(std::uint8_t red,std::uint8_t green,std::uint8_t blue);
   RGBPixel(const RGBPixel &)=default;

   std::uint8_t red() const;
   void red(std::uint8_t value);

   std::uint8_t blue() const;
   void blue(std::uint8_t value);

   std::uint8_t green() const;
   void green(std::uint8_t value);

};
