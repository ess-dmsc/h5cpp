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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Oct 09, 2017
//

#include <h5cpp/property/object_copy.hpp>
#include <h5cpp/error/error.hpp>

namespace hdf5 {
namespace property {

std::ostream &operator<<(std::ostream &stream,const CopyFlag &flag)
{
  switch(flag)
  {
    case CopyFlag::SHALLOW_HIERARCHY:
      return stream<<"SHALLOW_HIERARCHY";
    case CopyFlag::EXPAND_SOFT_LINKS:
      return stream<<"EXPAND_SOFT_LINKS";
    case CopyFlag::EXPAND_EXTERNAL_LINKS:
      return stream<<"EXPAND_EXTERNAL_LINKS";
    case CopyFlag::EXPAND_REFERENCES:
      return stream<<"EXPAND_REFERENCES";
    case CopyFlag::WITHOUT_ATTRIBUTES:
      return stream<<"WITHOUT_ATTRIBUTES";
    case CopyFlag::MERGE_COMMITTED_TYPES:
      return stream<<"MERGE_COMMITTED_TYPES";
    default:
      return stream<<"NONE"; //should never happen
  }
}

CopyFlags operator|(const CopyFlag &lhs,const CopyFlag &rhs)
{
  return CopyFlags(static_cast<unsigned>(lhs)|static_cast<unsigned>(rhs));
}

CopyFlags::CopyFlags() noexcept:
    value_(0)
{}

CopyFlags::CopyFlags(unsigned value) noexcept:
    value_(value)
{}

CopyFlags operator|(const CopyFlags &flags,const CopyFlags &rhs) noexcept
{
  return CopyFlags(static_cast<unsigned>(flags)|static_cast<unsigned>(rhs));
}

CopyFlags operator|(const CopyFlags &flags,const CopyFlag &flag) noexcept
{
  return CopyFlags(static_cast<unsigned>(flags)|static_cast<unsigned>(flag));
}

CopyFlags operator|(const CopyFlag &flag,const CopyFlags &flags) noexcept
{
  return CopyFlags(static_cast<unsigned>(flag)|static_cast<unsigned>(flags));
}


CopyFlags &CopyFlags::operator|=(const CopyFlag &flag) noexcept
{
  value_ |= static_cast<unsigned>(flag);
  return *this;
}

CopyFlags &CopyFlags::operator|=(const CopyFlags &flags) noexcept
{
  value_  |= static_cast<unsigned>(flags);
  return *this;
}

bool CopyFlags::shallow_hierarchy() const noexcept
{
  return value_ & static_cast<unsigned>(CopyFlag::SHALLOW_HIERARCHY);
}
void CopyFlags::shallow_hierarchy(bool flag) noexcept
{
  if(flag)
    value_ |= static_cast<unsigned>(CopyFlag::SHALLOW_HIERARCHY);
  else
    value_ &= ~static_cast<unsigned>(CopyFlag::SHALLOW_HIERARCHY);

}

bool CopyFlags::expand_soft_links() const noexcept
{
  return value_ & static_cast<unsigned>(CopyFlag::EXPAND_SOFT_LINKS);
}

void CopyFlags::expand_soft_links(bool flag) noexcept
{
  if(flag)
    value_ |= static_cast<unsigned>(CopyFlag::EXPAND_SOFT_LINKS);
  else
    value_ &= ~static_cast<unsigned>(CopyFlag::EXPAND_SOFT_LINKS);
}

bool CopyFlags::expand_external_links() const noexcept
{
  return value_ & static_cast<unsigned>(CopyFlag::EXPAND_EXTERNAL_LINKS);
}

void CopyFlags::expand_external_links(bool flag) noexcept
{
  if(flag)
    value_ |= static_cast<unsigned>(CopyFlag::EXPAND_EXTERNAL_LINKS);
  else
    value_ &= ~static_cast<unsigned>(CopyFlag::EXPAND_EXTERNAL_LINKS);
}

bool CopyFlags::expand_references() const noexcept
{
  return value_ & static_cast<unsigned>(CopyFlag::EXPAND_REFERENCES);
}

void CopyFlags::expand_references(bool flag) noexcept
{
  if(flag)
    value_ |= static_cast<unsigned>(CopyFlag::EXPAND_REFERENCES);
  else
    value_ &= ~static_cast<unsigned>(CopyFlag::EXPAND_REFERENCES);
}

bool CopyFlags::without_attributes() const noexcept
{
  return value_ & static_cast<unsigned>(CopyFlag::WITHOUT_ATTRIBUTES);
}

void CopyFlags::without_attributes(bool flag) noexcept
{
  if(flag)
    value_ |= static_cast<unsigned>(CopyFlag::WITHOUT_ATTRIBUTES);
  else
    value_ &= ~static_cast<unsigned>(CopyFlag::WITHOUT_ATTRIBUTES);
}

bool CopyFlags::merge_committed_types() const noexcept
{
  return value_ & static_cast<unsigned>(CopyFlag::MERGE_COMMITTED_TYPES);
}

void CopyFlags::merge_committed_types(bool flag) noexcept
{
  if(flag)
    value_ |= static_cast<unsigned>(CopyFlag::MERGE_COMMITTED_TYPES);
  else
    value_ &= ~static_cast<unsigned>(CopyFlag::MERGE_COMMITTED_TYPES);
}

ObjectCopyList::ObjectCopyList():
    List(kObjectCopy)
{}

void ObjectCopyList::flags(const CopyFlags &flags) const
{
  if(H5Pset_copy_object(static_cast<hid_t>(*this),static_cast<unsigned>(flags))<0)
  {
    error::Singleton::instance().throw_with_stack("Failure setting flags for object copy property list!");
  }
}

void ObjectCopyList::flags(const CopyFlag &flag) const
{
  flags(CopyFlags()|flag);
}

CopyFlags ObjectCopyList::flags() const
{
  unsigned flag_buffer;
  if(H5Pget_copy_object(static_cast<hid_t>(*this),&flag_buffer)<0)
  {
    error::Singleton::instance().throw_with_stack("Failure retrieving flags for object copy property list!");
  }
  return CopyFlags(flag_buffer);
}

} // namespace property
} // namespace hdf5
