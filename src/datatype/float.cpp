//
// (c) Copyright 2017 DESY,ESS
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
// Created on: Aug 23, 2017
//

#include <h5cpp/datatype/float.hpp>
#include <sstream>
#include <stdexcept>

namespace hdf5 {
namespace datatype {

  Float::Float(ObjectHandle &&handle):
		    Datatype(std::move(handle))
  {}

  Float::Float(const Datatype &datatype):
      Datatype(datatype)
  {
    if((datatype.get_class() != Class::FLOAT) &&
       (datatype.get_class() != Class::NONE))
    {
      std::stringstream ss;
      ss<<"Datatype is not a FLOAT or NONE type!";
      throw std::runtime_error(ss.str());
    }
  }

} // namespace datatype
} // namespace hdf5




