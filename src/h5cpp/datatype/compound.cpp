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
// Created on: Oct 5, 2017
//

#include <sstream>
#include <h5cpp/datatype/compound.hpp>
#include <h5cpp/error/error.hpp>
#include <h5cpp/core/utilities.hpp>

namespace hdf5 {
namespace datatype {

Compound::Compound(ObjectHandle &&handle) :
    Datatype(std::move(handle)) {}

Compound::Compound(const Datatype &type) :
    Datatype(type) {
  if (get_class() != Class::Compound) {
    std::stringstream ss;
    ss << "Cannot create Compound datatype from " << get_class();
    throw std::runtime_error(ss.str());
  }
}

Compound Compound::create(size_t size) {
  hid_t ret = H5Tcreate(static_cast<H5T_class_t>(Class::Compound), size);
  if (ret < 0) {
    std::stringstream ss;
    ss << "Could not create Compound datatype of size=" << size;
    error::Singleton::instance().throw_with_stack(ss.str());
  }
  return Compound(ObjectHandle(ret));
}


Datatype Compound::operator[](size_t index) const {
  hid_t id = H5Tget_member_type(static_cast<hid_t>(*this), unsigned2signed<int>(index));

  if (id < 0) {
    std::stringstream ss;
    ss << "Failure to obtain data type for field [" << index << "] in compound data type!";
    error::Singleton::instance().throw_with_stack(ss.str());
  }
  return Datatype(ObjectHandle(id));
}

Datatype Compound::operator[](const std::string &name) const {
  return Compound::operator[](field_index(name));
}

size_t Compound::field_index(const std::string &name) const {
  int index = H5Tget_member_index(static_cast<hid_t>(*this), name.c_str());
  if (index < 0) {
    std::stringstream ss;
    ss << "Failure to obtain the index for field [" << name << "] in compound data type!";
    error::Singleton::instance().throw_with_stack(ss.str());
  }
  return index;
}

// implementation same as for Enum
std::string Compound::field_name(size_t index) const {
  char *buffer = H5Tget_member_name(static_cast<hid_t>(*this), unsigned2signed<int>(index));
  if (buffer == NULL) {
    std::stringstream ss;
    ss << "Failure to obtain name of field [" << index << "] in compound data type!";
    error::Singleton::instance().throw_with_stack(ss.str());
  }
  std::string name(buffer);

  if (H5free_memory(buffer) < 0) {
    std::stringstream ss;
    ss << "Failure freeing memory for name buffer of field [" << index << "]"
       << " in compound data type!";
    error::Singleton::instance().throw_with_stack(ss.str());
  }
  return name;
}

size_t Compound::field_offset(const std::string &name) const {
  return field_offset(field_index(name));
}

size_t Compound::field_offset(size_t index) const {
  size_t offset = H5Tget_member_offset(static_cast<hid_t>(*this), unsigned2signed<int>(index));
  if (offset == 0) {
    // if offset == 0, there could be a field at 0, or there could be nothing
    try {
      field_class(index);
    }
    catch (const std::runtime_error &) {
      std::stringstream ss;
      ss << "Failure to obtain offset for field [" << index << "] in compound type!";
      std::throw_with_nested(std::runtime_error(ss.str()));
    }
  }

  return offset;
}

Class Compound::field_class(const std::string &name) const {
  return field_class(field_index(name));
}

Class Compound::field_class(size_t index) const {
  H5T_class_t value = H5Tget_member_class(static_cast<hid_t>(*this), unsigned2signed<int>(index));
  if (value < 0) {
    std::stringstream ss;
    ss << "Failure to obtain type class for field [" << index << "] in compound type!";
    error::Singleton::instance().throw_with_stack(ss.str());
  }
  return static_cast<Class>(value);
}

// implementation same as for Enum
size_t Compound::number_of_fields() const {
  int n = H5Tget_nmembers(static_cast<hid_t>(*this));
  if (n < 0) {
    error::Singleton::instance().throw_with_stack("Could not retrieve number of fields for compound data type!");
  }
  return static_cast<size_t>(n);
}

void Compound::insert(const std::string &name, size_t offset, const Datatype &type) const {
  if (H5Tinsert(static_cast<hid_t>(*this), name.c_str(), offset, static_cast<hid_t>(type)) < 0) {
    std::stringstream ss;
    ss << "Failure inserting field [" << name << "] at offset [" << offset << "] "
       << "in compound data type!";
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

void Compound::pack() const {
  if (H5Tpack(static_cast<hid_t>(*this)) < 0) {
    error::Singleton::instance().throw_with_stack("Failure packing compound data type!");
  }
}

} // namespace datatype
} // namespace hdf5
