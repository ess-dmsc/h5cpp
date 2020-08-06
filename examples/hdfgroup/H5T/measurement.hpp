//
// (c) Copyright 2019 DESY,ESS, Eugen Wintersberger <eugen.wintersberger@gmail.com>
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
// Created on: Jan 13, 2019
//

#pragma once

#include <string>
#include <iostream>

class Measurement
{
  private:
    int serial_no_;
    std::string location_;
    double temperature_;
    double pressure_;
  public:
    Measurement() = default;
    Measurement(int serial_no,const std::string &location,double temperature,double pressure);

    int serial_no() const noexcept;
    std::string location() const;
    double temperature() const noexcept;
    double pressure() const noexcept;
};

std::ostream &operator<<(std::ostream &stream,const Measurement &measurement);
