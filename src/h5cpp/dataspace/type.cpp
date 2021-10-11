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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Sep 7, 2017
//

#include <h5cpp/dataspace/type.hpp>

namespace hdf5 {
namespace dataspace {

std::ostream &operator<<(std::ostream &stream, const Type &t) {
  switch (t) {
    case Type::SCALAR: return stream << "SCALAR";
    case Type::SIMPLE: return stream << "SIMPLE";
    case Type::NODATA: return stream << "NODATA";
#ifndef __clang__
    default:return stream;
#endif
  }
}

std::ostream &operator<<(std::ostream &stream, const SelectionType &t) {
  switch (t) {
    case SelectionType::NONE: return stream << "NONE";
    case SelectionType::POINTS: return stream << "POINTS";
    case SelectionType::HYPERSLAB: return stream << "HYPERSLAB";
    case SelectionType::ALL: return stream << "ALL";
#ifndef __clang__
    default:return stream;
#endif
  }

}

std::ostream &operator<<(std::ostream &stream, const SelectionOperation &o) {
  switch (o) {
    case SelectionOperation::SET: return stream << "SET";
    case SelectionOperation::OR: return stream << "OR";
    case SelectionOperation::AND: return stream << "AND";
    case SelectionOperation::XOR: return stream << "XOR";
    case SelectionOperation::NOTB: return stream << "NOTB";
    case SelectionOperation::NOTA: return stream << "NOTA";
    case SelectionOperation::APPEND: return stream << "APPEND";
    case SelectionOperation::PREPEND: return stream << "PREPEND";
#ifndef __clang__
    default:return stream;
#endif
  }

}

} // namespace dataspace
} // namespace hdf5
