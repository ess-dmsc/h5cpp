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
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Oct 09, 2017
//

#include <h5cpp/property/object_copy.hpp>
#include <h5cpp/error/error.hpp>
#include <sstream>

namespace hdf5 {
namespace property {

std::ostream &operator<<(std::ostream &stream, const CopyFlag &flag) {
  switch (flag) {
    case CopyFlag::ShallowHierarchy:return stream << "SHALLOW_HIERARCHY";
    case CopyFlag::ExpandSoftLinks:return stream << "EXPAND_SOFT_LINKS";
    case CopyFlag::ExpandExternalLinks:return stream << "EXPAND_EXTERNAL_LINKS";
    case CopyFlag::ExpandReferences:return stream << "EXPAND_REFERENCES";
    case CopyFlag::WithoutAttributes:return stream << "WITHOUT_ATTRIBUTES";
    case CopyFlag::MergeCommittedTypes:return stream << "MERGE_COMMITTED_TYPES";
  }
  return stream << "NONE"; //should never happen
}

CopyFlags operator|(const CopyFlag &lhs, const CopyFlag &rhs) {
  return CopyFlags(static_cast<unsigned>(lhs) | static_cast<unsigned>(rhs));
}

CopyFlags operator&(const CopyFlag &lhs, const CopyFlag &rhs) {
  return CopyFlags(static_cast<unsigned>(lhs) & static_cast<unsigned>(rhs));
}

CopyFlags::CopyFlags() noexcept:
    value_(0) {}

CopyFlags::CopyFlags(unsigned value) noexcept:
    value_(value) {}

CopyFlags operator|(const CopyFlags &flags, const CopyFlags &rhs) noexcept {
  return CopyFlags(static_cast<unsigned>(flags) | static_cast<unsigned>(rhs));
}

CopyFlags operator|(const CopyFlags &flags, const CopyFlag &flag) noexcept {
  return CopyFlags(static_cast<unsigned>(flags) | static_cast<unsigned>(flag));
}

CopyFlags operator|(const CopyFlag &flag, const CopyFlags &flags) noexcept {
  return CopyFlags(static_cast<unsigned>(flag) | static_cast<unsigned>(flags));
}

CopyFlags &CopyFlags::operator|=(const CopyFlag &flag) noexcept {
  value_ |= static_cast<unsigned>(flag);
  return *this;
}

CopyFlags &CopyFlags::operator|=(const CopyFlags &flags) noexcept {
  value_ |= static_cast<unsigned>(flags);
  return *this;
}

CopyFlags operator&(const CopyFlags &flags, const CopyFlags &rhs) noexcept {
  return CopyFlags(static_cast<unsigned>(flags) & static_cast<unsigned>(rhs));
}

CopyFlags operator&(const CopyFlags &flags, const CopyFlag &flag) noexcept {
  return CopyFlags(static_cast<unsigned>(flags) & static_cast<unsigned>(flag));
}

CopyFlags operator&(const CopyFlag &flag, const CopyFlags &flags) noexcept {
  return CopyFlags(static_cast<unsigned>(flag) & static_cast<unsigned>(flags));
}

CopyFlags &CopyFlags::operator&=(const CopyFlag &flag) noexcept {
  value_ &= static_cast<unsigned>(flag);
  return *this;
}

CopyFlags &CopyFlags::operator&=(const CopyFlags &flags) noexcept {
  value_ &= static_cast<unsigned>(flags);
  return *this;
}

bool CopyFlags::shallow_hierarchy() const noexcept {
  return value_ & static_cast<unsigned>(CopyFlag::ShallowHierarchy);
}
void CopyFlags::shallow_hierarchy(bool flag) noexcept {
  if (flag)
    value_ |= static_cast<unsigned>(CopyFlag::ShallowHierarchy);
  else
    value_ &= ~static_cast<unsigned>(CopyFlag::ShallowHierarchy);

}

bool CopyFlags::expand_soft_links() const noexcept {
  return value_ & static_cast<unsigned>(CopyFlag::ExpandSoftLinks);
}

void CopyFlags::expand_soft_links(bool flag) noexcept {
  if (flag)
    value_ |= static_cast<unsigned>(CopyFlag::ExpandSoftLinks);
  else
    value_ &= ~static_cast<unsigned>(CopyFlag::ExpandSoftLinks);
}

bool CopyFlags::expand_external_links() const noexcept {
  return value_ & static_cast<unsigned>(CopyFlag::ExpandExternalLinks);
}

void CopyFlags::expand_external_links(bool flag) noexcept {
  if (flag)
    value_ |= static_cast<unsigned>(CopyFlag::ExpandExternalLinks);
  else
    value_ &= ~static_cast<unsigned>(CopyFlag::ExpandExternalLinks);
}

bool CopyFlags::expand_references() const noexcept {
  return value_ & static_cast<unsigned>(CopyFlag::ExpandReferences);
}

void CopyFlags::expand_references(bool flag) noexcept {
  if (flag)
    value_ |= static_cast<unsigned>(CopyFlag::ExpandReferences);
  else
    value_ &= ~static_cast<unsigned>(CopyFlag::ExpandReferences);
}

bool CopyFlags::without_attributes() const noexcept {
  return value_ & static_cast<unsigned>(CopyFlag::WithoutAttributes);
}

void CopyFlags::without_attributes(bool flag) noexcept {
  if (flag)
    value_ |= static_cast<unsigned>(CopyFlag::WithoutAttributes);
  else
    value_ &= ~static_cast<unsigned>(CopyFlag::WithoutAttributes);
}

bool CopyFlags::merge_committed_types() const noexcept {
  return value_ & static_cast<unsigned>(CopyFlag::MergeCommittedTypes);
}

void CopyFlags::merge_committed_types(bool flag) noexcept {
  if (flag)
    value_ |= static_cast<unsigned>(CopyFlag::MergeCommittedTypes);
  else
    value_ &= ~static_cast<unsigned>(CopyFlag::MergeCommittedTypes);
}

ObjectCopyList::ObjectCopyList() :
    List(kObjectCopy) {}

ObjectCopyList::ObjectCopyList(ObjectHandle &&handle) :
    List(std::move(handle)) {
  if (get_class() != kObjectCopy) {
    std::stringstream ss;
    ss << "Cannot create property::ObjectCopyList from " << get_class();
    throw std::runtime_error(ss.str());
  }
}

void ObjectCopyList::flags(const CopyFlags &flags) const {
  if (H5Pset_copy_object(static_cast<hid_t>(*this), static_cast<unsigned>(flags)) < 0) {
    error::Singleton::instance().throw_with_stack("Failure setting flags for object copy property list!");
  }
}

void ObjectCopyList::flags(const CopyFlag &flag) const {
  flags(CopyFlags() | flag);
}

CopyFlags ObjectCopyList::flags() const {
  unsigned flag_buffer;
  if (H5Pget_copy_object(static_cast<hid_t>(*this), &flag_buffer) < 0) {
    error::Singleton::instance().throw_with_stack("Failure retrieving flags for object copy property list!");
  }
  return CopyFlags(flag_buffer);
}

} // namespace property
} // namespace hdf5
