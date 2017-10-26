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
// Author: Martin Shetty <martin.shetty@esss.se>
// Created on: Oct 11, 2017
//
#pragma once

#include <type_traits>
#include "datatype.hpp"
#include "../windows.hpp"

namespace hdf5 {
namespace datatype {

class DLL_EXPORT String : public Datatype
{
  public:
    //!
    //! \brief default constructor
    //!
    //! We need this for STL containers but can rely on the
    //! default compiler implementation for now.
    //!
    String() = default;

    //!
    //! \brief construct from handle
    //!
    String(ObjectHandle &&handle);

    //!
    //! \brief cosntruct from generic datatype
    //!
    String(const Datatype &type);

    //!
    //! \brief construct variable-length string
    //!
    static String variable();

    //!
    //! \brief construct fiex-length string
    //!
    static String fixed(size_t);

    bool is_variable_length() const;

    CharacterEncoding encoding() const;
    void set_encoding(CharacterEncoding cset);

    StringPad padding() const;
    void set_padding(StringPad strpad);

    size_t size() const override;
    void set_size(size_t size) const override;

    //set order? other types?

    //set precision? other types?

    //set offset?
    //can only be 0 for string

};


} // namespace datatype
} // namespace hdf5
