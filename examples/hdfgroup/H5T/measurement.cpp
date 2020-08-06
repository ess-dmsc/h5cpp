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

#include "measurement.hpp"

Measurement::Measurement (int serial_no, const std::string &location,
                          double temperature, double pressure) :
    serial_no_ (serial_no),
    location_ (location),
    temperature_ (temperature),
    pressure_ ( pressure)
{
}

int Measurement::serial_no () const noexcept
{
  return serial_no_;
}

std::string Measurement::location () const
{
  return location_;
}

double Measurement::temperature () const noexcept
{
  return temperature_;
}

double Measurement::pressure () const noexcept
{
  return pressure_;
}

std::ostream &operator<<(std::ostream &stream,const Measurement &measurement)
{
  stream<<"Serial number: "<<measurement.serial_no()<<", ";
  stream<<"Location: "<<measurement.location()<<", ";
  stream<<"Temperature: "<<measurement.temperature()<<", ";
  stream<<"Pressure: "<<measurement.pressure();

  return stream;

}

