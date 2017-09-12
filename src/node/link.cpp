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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Sep 11, 2017
//

#include <h5cpp/node/link.hpp>

namespace hdf5 {
namespace node {

LinkTarget::LinkTarget():
    file_(),
    object_path_()
{}

LinkTarget::LinkTarget(const hdf5::Path &object_path):
    file_(),
    object_path_(object_path)
{}

LinkTarget::LinkTarget(const hdf5::Path &object_path,
                       const boost::filesystem::path &file_path):
    file_(file_path),
    object_path_(object_path)
{}

boost::filesystem::path LinkTarget::file_path() const
{
  return file_;
}

hdf5::Path LinkTarget::object_path() const
{
  return object_path_;
}

} // namespace node
} // namespace hdf5
