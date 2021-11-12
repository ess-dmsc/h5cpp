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
    case Type::Scalar: return stream << "SCALAR";
    case Type::Simple: return stream << "SIMPLE";
    case Type::NoData: return stream << "NODATA";
#ifndef __clang__
    default:return stream;
#endif
  }
}

std::ostream &operator<<(std::ostream &stream, const SelectionType &t) {
  switch (t) {
    case SelectionType::None: return stream << "NONE";
    case SelectionType::Points: return stream << "POINTS";
    case SelectionType::Hyperslab: return stream << "HYPERSLAB";
    case SelectionType::All: return stream << "ALL";
#ifndef __clang__
    default:return stream;
#endif
  }

}

std::ostream &operator<<(std::ostream &stream, const SelectionOperation &o) {
  switch (o) {
    case SelectionOperation::Set: return stream << "SET";
    case SelectionOperation::Or: return stream << "OR";
    case SelectionOperation::And: return stream << "AND";
    case SelectionOperation::XOr: return stream << "XOR";
    case SelectionOperation::NotB: return stream << "NOTB";
    case SelectionOperation::NotA: return stream << "NOTA";
    case SelectionOperation::Append: return stream << "APPEND";
    case SelectionOperation::Prepend: return stream << "PREPEND";
#ifndef __clang__
    default:return stream;
#endif
  }

}

} // namespace dataspace
} // namespace hdf5
