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


#include "property_list.hpp"
#include "property_list_class.hpp"

namespace hdf5 {
namespace property_list {

  List::List(const Class &plist_class):
      handle_(H5Pcreate(static_cast<hid_t>(plist_class)))
  {
  }

  List::List(const List &plist):
      handle_(H5Pcopy(static_cast<hid_t>(plist.handle_)))
  {
  }

  void List::close()
  {
    handle_.close();
  }

  Class List::get_class() const
  {
    return Class(ObjectHandle(H5Pget_class(static_cast<hid_t>(handle_))));
  }


} // namespace property_list
} // namespace hdf5
