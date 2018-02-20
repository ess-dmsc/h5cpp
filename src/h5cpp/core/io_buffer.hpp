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
// Created on: Feb 6, 2018
//
#pragma once 

#include <memory>

namespace hdf5 {

class IOWriteBuffer
{
  public:
    using UniquePointer = std::unique_pointer<IOWriteBuffer>;
    using SharedPointer = std::shared_pointer<IOWriteBuffer>;

    virtual ~IOWriteBuffer() {}
    const void *pointer() const = 0;
};

class IOReadBuffer
{
  public:
    using UniquePointer = std::unique_pointer<IOReadBuffer>;
    using SharedPointer = std::unique_pointer<IOReadBuffer>;

    virtual ~IOReadBuffer() {}

    void *pointer() = 0;
    void notify() = 0;
};

} // namespace hdf5
