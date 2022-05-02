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
// Created on: Aug 16, 2017
//

#include <h5cpp/property/file_creation.hpp>
#include <h5cpp/error/error.hpp>
#include <sstream>

namespace hdf5 {
namespace property {

FileCreationList::FileCreationList() :
    GroupCreationList(kFileCreate) {
}

FileCreationList::~FileCreationList() {}

FileCreationList::FileCreationList(ObjectHandle &&handle) :
    GroupCreationList(std::move(handle)) {
  if (get_class() != kFileCreate) {
    std::stringstream ss;
    ss << "Cannot create property::FileCreationList from " << get_class();
    throw std::runtime_error(ss.str());
  }
}

hsize_t FileCreationList::user_block() const {
  hsize_t buffer;
  if (0 > H5Pget_userblock(static_cast<hid_t>(*this), &buffer)) {
    error::Singleton::instance().throw_with_stack("Cannot retrieve user block size from file creation property list!");
  }
  return buffer;
}

void FileCreationList::user_block(hsize_t size) const {
  if (0 > H5Pset_userblock(static_cast<hid_t>(*this), size)) {
    error::Singleton::instance().throw_with_stack("Cannot set user block size for file creation property list!");
  }
}

void FileCreationList::object_offset_size(size_t size) const {
  if (0 > H5Pset_sizes(static_cast<hid_t>(*this), size, 0)) {
    error::Singleton::instance().throw_with_stack("Failure setting object offset size to file creation property list!");
  }
}

size_t FileCreationList::object_offset_size() const {
  size_t offset_size{0};
  if (0 > H5Pget_sizes(static_cast<hid_t>(*this), &offset_size, nullptr)) {
    error::Singleton::instance().throw_with_stack(
        "Failure retrieving object offset size from file creation property list!");
  }

  return offset_size;
}

void FileCreationList::object_length_size(size_t size) const {
  if (0 > H5Pset_sizes(static_cast<hid_t>(*this), 0, size)) {
    error::Singleton::instance().throw_with_stack("Failure setting object length size in file creation property list!");
  }
}

size_t FileCreationList::object_length_size() const {
  size_t length_size{0};
  if (0 > H5Pget_sizes(static_cast<hid_t>(*this), nullptr, &length_size)) {
    error::Singleton::instance().throw_with_stack(
        "Failure retrieving object length size from file creation property list!");
  }
  return length_size;
}

void FileCreationList::btree_rank(unsigned int ik) {
  if (0 > H5Pset_sym_k(static_cast<hid_t>(*this), ik, 0)) {
    error::Singleton::instance().throw_with_stack("Failure setting rank parameter for symbol table nodes!");
  }
}

unsigned int FileCreationList::btree_rank() const {
  unsigned int ik{0};
  if (0 > H5Pget_sym_k(static_cast<hid_t>(*this), &ik, nullptr)) {
    error::Singleton::instance().throw_with_stack("Failure retrieving rank parameter for symbol table nodes!");
  }
  return ik;
}

void FileCreationList::btree_symbols(unsigned int lk) {
  if (0 > H5Pset_sym_k(static_cast<hid_t>(*this), 0, lk)) {
    error::Singleton::instance().throw_with_stack("Failure setting symbol size parameter for symbol table nodes!");
  }
}

unsigned int FileCreationList::btree_symbols() const {
  unsigned int lk{0};
  if (0 > H5Pget_sym_k(static_cast<hid_t>(*this), nullptr, &lk)) {
    error::Singleton::instance().throw_with_stack("Failure retrieving symbol size parameter for symbol table nodes!");
  }
  return lk;
}

void FileCreationList::chunk_tree_rank(unsigned int ik) {
  if (0 > H5Pset_istore_k(static_cast<hid_t>(*this), ik)) {
    error::Singleton::instance().throw_with_stack("Failure setting rank parameter for symbol table nodes!");
  }
}

unsigned int FileCreationList::chunk_tree_rank() const {
  unsigned int ik{0};
  if (0 > H5Pget_istore_k(static_cast<hid_t>(*this), &ik)) {
    error::Singleton::instance().throw_with_stack("Failure retrieving rank parameter for symbol table nodes!");
  }
  return ik;
}

#if H5_VERSION_GE(1, 10, 1)
void FileCreationList::page_size(hsize_t size) {
  if (0 > H5Pset_file_space_page_size(static_cast<hid_t>(*this), size)) {
    error::Singleton::instance().throw_with_stack("Failure setting rank parameter for symbol table nodes!");
  }
}

hsize_t FileCreationList::page_size() const {
  hsize_t size{0};
  if (0 > H5Pget_file_space_page_size(static_cast<hid_t>(*this), &size)) {
    error::Singleton::instance().throw_with_stack("Failure retrieving rank parameter for symbol table nodes!");
  }
  return size;
}
#endif

} // namespace property
} // namespace hdf5
