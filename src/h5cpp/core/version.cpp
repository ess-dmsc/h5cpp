//
// (c) Copyright 2018 DESY,ESS
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
// Created on: Feb 7, 2018
//

#include <h5cpp/core/hdf5_capi.hpp>
#include <h5cpp/error/error.hpp>
#include <h5cpp/core/version.hpp>
#include <sstream>
#include <stdexcept>


namespace hdf5 {

Version::Version() noexcept:
    major_(0),
    minor_(0),
    patch_(0)
{}

Version::Version(NumberType major_number, NumberType minor_number, NumberType patch) noexcept:
    major_(major_number),
    minor_(minor_number),
    patch_(patch)
{}

Version::NumberType Version::major_number() const noexcept
{
  return major_;
}

Version::NumberType Version::minor_number() const noexcept
{
  return minor_;
}

Version::NumberType Version::patch_number() const noexcept
{
  return patch_;
}

std::string Version::to_string(const Version &version)
{
  std::stringstream ss;
  ss << version.major_number() << "." << version.minor_number() << "." << version.patch_number();
  return ss.str();
}

bool operator==(const Version &lhs,const Version &rhs)
{
  return (lhs.major_number() == rhs.major_number()) &&
         (lhs.minor_number() == rhs.minor_number()) &&
         (lhs.patch_number() == rhs.patch_number());
}

bool operator!=(const Version &lhs,const Version &rhs)
{
  return !(lhs==rhs);
}

bool operator<=(const Version &lhs,const Version &rhs)
{
  return (rhs==lhs)||(lhs<rhs);
}

bool operator<(const Version &lhs,const Version &rhs)
{
  if(lhs.major_number()<rhs.major_number())
    return true;

  if(lhs.minor_number() < rhs.minor_number())
    return true;

  if(lhs.patch_number() < rhs.patch_number())
    return true;

  return false;
}

bool operator>=(const Version &lhs,const Version &rhs)
{
  return (lhs==rhs) || (lhs>rhs);
}

bool operator>(const Version &lhs,const Version &rhs)
{
  if(lhs.major_number() > rhs.major_number())
    return true;

  if(lhs.minor_number() > rhs.minor_number())
    return true;

  if(lhs.patch_number() > rhs.patch_number())
    return true;

  return false;
}

std::ostream &operator<<(std::ostream &stream,const Version &v)
{
  return stream << Version::to_string(v);
}

Version current_library_version()
{
  unsigned int major_number = 0, minor_number = 0, release = 0;
  if (H5get_libversion(&major_number, &minor_number, &release) < 0)
  {
    std::stringstream ss;
    ss << "Cannot determine library version!";
    error::Singleton::instance().throw_with_stack(ss.str());
  }
  return Version(major_number, minor_number, release);
}

} // namespace hdf5
