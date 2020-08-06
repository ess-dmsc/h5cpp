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

#include <h5cpp/hdf5.hpp>
#include "measurement.hpp"


namespace hdf5 {
namespace datatype {



template<>
  class TypeTrait<Measurement>
  {
    private:
      struct buffer_struct
      {
          int serial_no_;
          std::string location_;
          double temperature_;
          double pressure_;
      };
    public:
      using Type = Measurement;
      using TypeClass = Compound;

      static TypeClass
      create (const Type& = Type ())
      {
        Compound type = Compound::create (sizeof(buffer_struct));
        type.insert ("serial_no", HOFFSET(buffer_struct, serial_no_),
                     datatype::create<int> ());
        type.insert ("location", HOFFSET(buffer_struct, location_),
                     datatype::create<std::string> ());
        type.insert ("temperature", HOFFSET(buffer_struct, temperature_),
                     datatype::create<double> ());
        type.insert ("pressure", HOFFSET(buffer_struct, pressure_),
                     datatype::create<double> ());

        return type;
      }
};

} // end of namespace datatype
} // end of namespace hdf5
