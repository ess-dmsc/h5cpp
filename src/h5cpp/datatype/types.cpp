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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Martin Shetty <martin.shetty@esss.es>
// Created on: Sep 6, 2017
//

#include <h5cpp/datatype/types.hpp>

namespace hdf5 {
namespace datatype {

std::ostream &operator<<(std::ostream &stream, const Class &c)
{
  switch (c) {
    case Class::NONE: return stream << "NONE";
    case Class::INTEGER: return stream << "INTEGER";
    case Class::FLOAT: return stream << "FLOAT";
    case Class::TIME: return stream << "TIME";
    case Class::STRING: return stream << "STRING";
    case Class::BITFIELD: return stream << "BITFIELD";
    case Class::OPAQUE: return stream << "OPAQUE";
    case Class::COMPOUND: return stream << "COMPOUND";
    case Class::REFERENCE: return stream << "REFERENCE";
    case Class::ENUM: return stream << "ENUM";
    case Class::VARLENGTH: return stream << "VARLENGTH";
    case Class::ARRAY: return stream << "ARRAY";
    default:return stream;
  }
}

std::ostream &operator<<(std::ostream &stream, const Order &o)
{
  switch (o) {
    case Order::BE: return stream << "BE";
    case Order::LE: return stream << "LE";
    default:return stream;
  }
}

std::ostream &operator<<(std::ostream &stream, const Sign &s)
{
  switch (s) {
    case Sign::TWOS_COMPLEMENT: return stream << "TWOS COMPLEMENT";
    case Sign::UNSIGNED: return stream << "UNSIGNED";
    default:return stream;
  }
}

std::ostream &operator<<(std::ostream &stream, const Norm &n)
{
  switch (n) {
    case Norm::IMPLIED: return stream << "IMPLIED";
    case Norm::MSBSET: return stream << "MSBSET";
    case Norm::NONE: return stream << "NONE";
    default:return stream;
  }
}

std::ostream &operator<<(std::ostream &stream, const Pad &p)
{
  switch (p) {
    case Pad::BACKGROUND: return stream << "BACKGROUND";
    case Pad::ONE: return stream << "ONE";
    case Pad::ZERO: return stream << "ZERO";
    default:return stream;
  }
}

std::ostream &operator<<(std::ostream &stream, const StringPad &pad)
{
  switch (pad) {
    case StringPad::NULLPAD: return stream << "NULLPAD";
    case StringPad::NULLTERM: return stream << "NULLTERM";
    case StringPad::SPACEPAD: return stream << "SPACEPAD";
    default:return stream;
  }
}

std::ostream &operator<<(std::ostream &stream, const Direction &d)
{
  switch (d) {
    case Direction::ASCEND: return stream << "ASCEND";
    case Direction::DESCEND: return stream << "DESCEND";
    default:return stream;
  }
}

std::ostream &operator<<(std::ostream &stream, const CharacterEncoding &enc)
{
  switch (enc) {
    case CharacterEncoding::ASCII: return stream << "ASCII";
    case CharacterEncoding::UTF8: return stream << "UTF8";
    default:return stream;
  }
}

} // namespace datatype
} // namespace hdf5
