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
// Created on: Aug 15, 2017
//

#pragma once

#include <type_traits>
#include <boost/filesystem.hpp>
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

class LinkCreationOrder
{
  public:
    LinkCreationOrder();
    LinkCreationOrder(const LinkCreationOrder &c)=default;
    explicit LinkCreationOrder(unsigned value);

    LinkCreationOrder &enable_tracked();
    LinkCreationOrder &disable_tracked();
    LinkCreationOrder &enable_indexed();
    LinkCreationOrder &disable_indexed();

    bool tracked() const;
    bool indexed() const;

    operator unsigned() const
    {
      unsigned result = 0;
      if(tracked_) result|=H5P_CRT_ORDER_TRACKED;

      if(indexed_) result|=H5P_CRT_ORDER_INDEXED;

      return result;

    }

  private:
    unsigned tracked_:1;
    unsigned indexed_:1;
    unsigned reserved_:sizeof(unsigned)-2;

};

class GroupCreation : public List
{
  public:
    GroupCreation();

    size_t local_heap_size_hint() const;
    void local_heap_size_hint(size_t size) const;

    unsigned estimated_number_of_links() const;
    void estimated_number_of_links(unsigned nlinks) const;

    unsigned estimated_link_name_length() const;
    void estimated_link_name_length(unsigned name_length) const;

    void link_creation_order(LinkCreationOrder order) const;
    LinkCreationOrder link_creation_order() const;

    void maximum_links_for_compact_group(unsigned nlinks) const;
    unsigned maximum_links_for_compact_group() const;

    void minimum_links_for_dense_group(unsigned nlinks) const;
    unsigned minimum_links_for_dense_group() const;


  private:

    void set_estimated_link_info_(unsigned nlinks,unsigned name_length,
                                  const std::string &error_message) const;
    void get_estimated_link_info_(unsigned &nlinks,unsigned &name_length,
                                  const std::string &error_message) const;

    void set_link_phase_change_(unsigned max_links,unsigned min_links,
                                const std::string &error_message) const;
    void get_link_phase_change_(unsigned &max_links,unsigned &min_links,
                                const std::string &error_message) const;

};

class GroupAccess : public List
{
  public:
    GroupAccess();

};

class LinkCreation : public List
{
  public:
    LinkCreation();
};

class LinkAccess : public List
{
  public:
    LinkAccess();

    size_t nlinks() const;
    void nlinks(size_t size) const;

    boost::filesystem::path external_link_prefix() const;
    void external_link_prefix(const boost::filesystem::path &path) const;

};

}  // namespace property_list
}  // namespace hdf5
