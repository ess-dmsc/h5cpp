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
// Created on: Aug 24, 2017
//
#pragma once

#include <list>
#include <string>

namespace hdf5 {

//!
//! \brief path to a node object
//!
//! Every object within an HDF5 file can be addressed via a path. Such a path is a
//! list of link names separated by a slash /.
//! While HDF5s C-API uses a simple string to represent a path, the C++ wrapper
//! provides a class for this purpose.
//!
class Path
{
  public:
    using value_type = std::string;
    using iterator = std::list<value_type>::iterator;
    using const_iterator = std::list<value_type>::const_iterator;
    using reverse_iterator = std::list<value_type>::reverse_iterator;
    using const_reverse_iterator= std::list<value_type>::const_reverse_iterator;

    Path();
    explicit Path(const std::string &str);
    Path(const Path &p) = default;

    explicit operator std::string() const
    {
      return to_string();
    }

    size_t size() const;

    const_iterator begin() const;
    const_iterator end() const;
    iterator begin();
    iterator end();

    reverse_iterator rbegin();
    reverse_iterator rend();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;

    void push_front(const value_type &link_name);
    value_type pop_front();

    void push_back(const value_type &link_name);
    value_type pop_back();

    bool is_absolute_path() const noexcept;
    void is_absolute_path(bool value) noexcept;

  private:
    bool absolute_;
    std::list<std::string> link_names_;

    void from_string(const std::string &str);
    std::string to_string() const;

};

Path operator+(const Path &lhs,const Path &rhs);

Path operator+(const std::string &link_name,const Path &path);
Path operator+(const Path &path,const std::string &link_name);

} // namespace hdf5
