//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5pp.
//
// h5cpp is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// h5cpp is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  ee the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with h5cpp.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Aug 15, 2017
//

#pragma once

extern "C" {
#include <hdf5.h>
}
#include "object_handle.hpp"
#include "property_list_class.hpp"


namespace hdf5 {
namespace property_list{

class Class;

class List
{
  public:
    explicit List(const Class &plist_class);
    List(const List &plist);

    void close();
    Class get_class() const;

    explicit operator hid_t() const
    {
      return static_cast<hid_t>(handle_);
    }

  private:
    ObjectHandle handle_;

};


class FileCreation : public List
{
  public:
    FileCreation();

    void userblock(hsize_t size) const;
    hsize_t userblock() const;

    void object_offset_size(size_t size) const;
    size_t object_offset_size() const;

    void object_length_size(size_t size) const;
    size_t object_length_size() const;

};

class FileAccess : public List
{
  public:
    FileAccess();
};

class GroupCreation : public List
{
public:
  GroupCreation();


};

class GroupAccess : public List
{

};

}  // namespace property_list
}  // namespace hdf5
