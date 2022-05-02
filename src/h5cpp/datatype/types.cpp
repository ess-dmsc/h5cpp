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
// Created on: Sep 6, 2017
//

#include <h5cpp/datatype/types.hpp>

namespace hdf5 {
namespace datatype {

std::ostream &operator<<(std::ostream &stream, const Class &c) {
  switch (c) {
    case Class::None: return stream << "NONE";
    case Class::Integer: return stream << "INTEGER";
    case Class::Float: return stream << "FLOAT";
    case Class::Time: return stream << "TIME";
    case Class::String: return stream << "STRING";
    case Class::BitField: return stream << "BITFIELD";
    case Class::Opaque: return stream << "OPAQUE";
    case Class::Compound: return stream << "COMPOUND";
    case Class::Reference: return stream << "REFERENCE";
    case Class::Enum: return stream << "ENUM";
    case Class::VarLength: return stream << "VARLENGTH";
    case Class::Array: return stream << "ARRAY";
  }
  return stream;
}

std::ostream &operator<<(std::ostream &stream, const Order &o) {
  switch (o) {
    case Order::BE: return stream << "BE";
    case Order::LE: return stream << "LE";
    case Order::Vax: return stream << "VAX";
    case Order::None: return stream << "NONE";
  }
  return stream;
}

std::ostream &operator<<(std::ostream &stream, const Sign &s) {
  switch (s) {
    case Sign::TwosComplement: return stream << "TWOS COMPLEMENT";
    case Sign::Unsigned: return stream << "UNSIGNED";
  }
  return stream;
}

std::ostream &operator<<(std::ostream &stream, const Norm &n) {
  switch (n) {
    case Norm::Implied: return stream << "IMPLIED";
    case Norm::MSBSet: return stream << "MSBSET";
    case Norm::None: return stream << "NONE";
  }
  return stream;
}

std::ostream &operator<<(std::ostream &stream, const Pad &p) {
  switch (p) {
    case Pad::Background: return stream << "BACKGROUND";
    case Pad::One: return stream << "ONE";
    case Pad::Zero: return stream << "ZERO";
  }
  return stream;
}

std::ostream &operator<<(std::ostream &stream, const StringPad &pad) {
  switch (pad) {
    case StringPad::NullPad: return stream << "NULLPAD";
    case StringPad::NullTerm: return stream << "NULLTERM";
    case StringPad::SpacePad: return stream << "SPACEPAD";
  }
  return stream;
}

std::ostream &operator<<(std::ostream &stream, const Direction &d) {
  switch (d) {
    case Direction::Ascend: return stream << "ASCEND";
    case Direction::Descend: return stream << "DESCEND";
  }
  return stream;
}

std::ostream &operator<<(std::ostream &stream, const CharacterEncoding &enc) {
  switch (enc) {
    case CharacterEncoding::ASCII: return stream << "ASCII";
    case CharacterEncoding::UTF8: return stream << "UTF8";
  }
  return stream;
}

} // namespace datatype
} // namespace hdf5
