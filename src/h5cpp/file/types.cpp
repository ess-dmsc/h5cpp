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
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Sep 8, 2017
//

#include <h5cpp/file/types.hpp>

namespace hdf5 {
namespace file {

std::ostream &operator<<(std::ostream &stream,const AccessFlags &flags)
{
  switch(flags)
  {
    case AccessFlags::Exclusive: return stream<<"EXCLUSIVE";
    case AccessFlags::ReadOnly: return stream<<"READONLY";
    case AccessFlags::ReadWrite: return stream<<"READWRITE";
    case AccessFlags::Truncate: return stream<<"TRUNCATE";
#if H5_VERSION_GE(1,10,0)
    case AccessFlags::SWMRRead: return stream<<"SWMR READ";
    case AccessFlags::SWMRWrite: return stream<<"SWMR WRITE";
#endif
  }
  return stream;
}

AccessFlagsBase operator|(const AccessFlags &lhs,const AccessFlags &rhs)
{
  return static_cast<AccessFlagsBase>(lhs) |
         static_cast<AccessFlagsBase>(rhs);
}

AccessFlagsBase operator|(const AccessFlagsBase &lhs,const AccessFlags &rhs)
{
  return lhs | static_cast<AccessFlagsBase>(rhs);
}

AccessFlagsBase operator|(const AccessFlags &lhs,const AccessFlagsBase &rhs)
{
  return static_cast<AccessFlagsBase>(lhs) | rhs;
}

AccessFlagsBase operator&(const AccessFlags &lhs,const AccessFlags &rhs)
{
  return static_cast<AccessFlagsBase>(lhs) & static_cast<AccessFlagsBase>(rhs);
}

AccessFlagsBase operator&(const AccessFlagsBase &lhs,const AccessFlags &rhs)
{
  return lhs & static_cast<AccessFlagsBase>(rhs);
}

AccessFlagsBase operator&(const AccessFlags &lhs,const AccessFlagsBase &rhs)
{
  return static_cast<AccessFlagsBase>(lhs) & rhs;
}

std::ostream &operator<<(std::ostream &stream,const ImageFlags &flags)
{
  switch(flags)
  {
    case ImageFlags::ReadOnly: return stream<<"READONLY";
    case ImageFlags::ReadWrite: return stream<<"READWRITE";
    case ImageFlags::DontCopy: return stream<<"DONT COPY";
    case ImageFlags::DontRelease: return stream<<"DONT RELEASE";
    case ImageFlags::All: return stream<<"ALL";
  }
  return stream;
}

ImageFlagsBase operator|(const ImageFlags &lhs,const ImageFlags &rhs)
{
  return static_cast<ImageFlagsBase>(lhs) |
         static_cast<ImageFlagsBase>(rhs);
}

ImageFlagsBase operator|(const ImageFlagsBase &lhs,const ImageFlags &rhs)
{
  return lhs | static_cast<ImageFlagsBase>(rhs);
}

ImageFlagsBase operator|(const ImageFlags &lhs,const ImageFlagsBase &rhs)
{
  return static_cast<ImageFlagsBase>(lhs) | rhs;
}

ImageFlagsBase operator&(const ImageFlags &lhs,const ImageFlags &rhs)
{
  return static_cast<ImageFlagsBase>(lhs) & static_cast<ImageFlagsBase>(rhs);
}

ImageFlagsBase operator&(const ImageFlagsBase &lhs,const ImageFlags &rhs)
{
  return lhs & static_cast<ImageFlagsBase>(rhs);
}

ImageFlagsBase operator&(const ImageFlags &lhs,const ImageFlagsBase &rhs)
{
  return static_cast<ImageFlagsBase>(lhs) & rhs;
}

std::ostream &operator<<(std::ostream &stream,const SearchFlags &flags)
{
  switch(flags)
  {
    case SearchFlags::All: return stream<<"ALL";
    case SearchFlags::Attribute: return stream<<"ATTRIBUTE";
    case SearchFlags::Dataset: return stream<<"DATASET";
    case SearchFlags::Datatype: return stream<<"DATATYPE";
    case SearchFlags::File: return stream<<"FILE";
    case SearchFlags::Group: return stream<<"GROUP";
    case SearchFlags::Local: return stream<<"LOCAL";
  }
  return stream;
}

SearchFlagsBase operator|(const SearchFlags &lhs,const SearchFlags &rhs)
{
  return static_cast<SearchFlagsBase>(lhs) | static_cast<SearchFlagsBase>(rhs);
}

SearchFlagsBase operator|(const SearchFlags &lhs,const SearchFlagsBase &rhs)
{
  return static_cast<SearchFlagsBase>(lhs) | rhs;
}

SearchFlagsBase operator|(const SearchFlagsBase &lhs,const SearchFlags &rhs)
{
  return lhs | static_cast<SearchFlagsBase>(rhs);
}

 SearchFlagsBase operator&(const SearchFlags &lhs,const SearchFlags &rhs)
{
  return static_cast<SearchFlagsBase>(lhs) & static_cast<SearchFlagsBase>(rhs);
}

SearchFlagsBase operator&(const SearchFlags &lhs,const SearchFlagsBase &rhs)
{
  return static_cast<SearchFlagsBase>(lhs) & rhs;
}

SearchFlagsBase operator&(const SearchFlagsBase &lhs,const SearchFlags &rhs)
{
  return lhs & static_cast<SearchFlagsBase>(rhs);
}

std::ostream &operator<<(std::ostream &stream,const Scope &scope)
{
  switch(scope)
  {
    case Scope::Global: return stream<<"GLOBAL";
    case Scope::Local: return stream<<"LOCAL";
  }
  return stream;
}


} // namespace file
} // namespace hdf5
