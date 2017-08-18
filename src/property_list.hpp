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

class CreationOrder
{
  public:
    //!
    //! \brief default constructor
    //!
    CreationOrder();

    //!
    //! \brief copy constructor
    //!
    //! @param c reference from which to copy
    CreationOrder(const CreationOrder &c)=default;

    //!
    //! \brief constructor
    //!
    //! @param value flags from which to construct the instance
    explicit CreationOrder(unsigned value);

    //!
    //! \brief enable tracked creation order
    //!
    //! @return reference to the modified instance
    //! \sa disable_tracked
    CreationOrder &enable_tracked();

    //!
    //! \brief disable tracked creation order
    //!
    //! @return reference to the modified instance
    //! \sa enable_tracked
    CreationOrder &disable_tracked();

    //!
    //! \brief enable indexed creation order
    //!
    //! This implies also tracked creation order which will be
    //! enabled by this method automatically if it is not.
    //!
    //! @return reference to the modified instance
    //! \sa disable_indexed
    CreationOrder &enable_indexed();

    //!
    //! \brief disable indexed creation order
    //!
    //! This does not automatically disable also tracked creation order.
    //!
    //! @return reference to the modified instance
    //! \sa enable_tracked
    CreationOrder &disable_indexed();

    //!
    //! \brief query if tracked creation order is enabled
    //! @return true if creation order is tracked, false otherwise
    bool tracked() const;

    //!
    //! \brief query if indexed creation order is enabled
    //! @return true if creation order indexed is enabled, false otherwise
    bool indexed() const;

    //!
    //! \brief conversion operator
    //!
    //! Allows the conversion of an instance of this class to an unsigned
    //! integer value which can be used with the HDF5 C-API low level
    //! functions.
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

//!
//! \brief base class for property lists
//!
class List
{
  public:
    //!
    //! \brief constructor
    //!
    //! @param plist_class
    //!
    explicit List(const Class &plist_class);

    //!
    //! \brief copy constructor
    //! @param plist
    //!
    List(const List &plist);

    //!
    //! \brief destructor
    //!
    virtual ~List();

    //!
    //! \brief close the property list
    //!
    void close();

    //
    //! \brief return property list class
    //!
    //! Return an instance of the property list class the list belongs to.
    //!
    //! \return class instance
    Class get_class() const;

    //!
    //! \brief conversion operator
    //!
    //! Use this operator to obtain the actual HDF5 handler to the list
    //! instance.
    //!
    explicit operator hid_t() const
    {
      return static_cast<hid_t>(handle_);
    }

  private:
    ObjectHandle handle_;

};

class ObjectCreation : public List
{
  public:
    //!
    //! \brief constructor
    //!
    ObjectCreation();

    //!
    //! \brief destructor
    //!
    virtual ~ObjectCreation();

    void enable_create_intermediate_group() const;
    void disable_create_intermediate_group() const;
    bool create_intermediate_group() const;

    //!
    //! \brief enable object time tracking
    //!
    //! Activates the time tracking feature on objects in the file.
    //!
    //! \sa disable_time_tracking
    //! \sa time_tracking
    void enable_time_tracking() const;

    //!
    //! \brief disable object time tracking
    //! \sa enable_time_tracking
    //! \sa time_tracking
    void disable_time_tracking() const;

    //!
    //! \brief return time tacking status
    //!
    //! Queries the current status of the time tracking feature. This method
    //! returns true if time tracking is activate and false otherwise.
    //!
    //! \throws std::runtime_errr in case of an error
    //!
    //! @return true if time tracking is active, false otherwise
    //! \sa enable_time_tracking
    //! \sa disable_time_tracking
    bool time_tracking() const;

    //!
    //! \brief set the attribute creation order
    //!
    //! Set the attribute creation order flags which will be used for all
    //! objects.
    //!
    //! @param order requested attribute creation order
    //! \sa CreationOrder
    //! \sa attribute_creation_order()
    void attribute_creation_order(const CreationOrder &order) const;

    //!
    //! \brief retrieve current attribute creation order
    //!
    //! @return current attribute creation order
    //! \sa attribute_creation_order
    //! \sa CreationOrder
    CreationOrder attribute_creation_order() const;


    //!
    //! \brief set storage layout thresholds
    //!
    //! @param max_compact maximum number above which dense storage will be
    //!                    used
    //! @param min_dense minimum number below which compact storage will be
    //!                  used
    //! \sa attribute_storage_maximum_compact
    //! \sa attribute_storage_minimum_dense
    void attribute_storage_thresholds(unsigned max_compact,unsigned min_dense) const;

    //!
    //! \brief get upper threshold for compact storage
    //!
    //! \return
    unsigned attribute_storage_maximum_compact() const;

    //!
    //! \brief get lower threshold for dense threshold
    unsigned attribute_storage_minimum_dense() const;

  protected:
    ObjectCreation(const Class &plist_class);
  private:
    void get_attribute_phase_change_(unsigned &max_compact,
                                     unsigned &min_dense,
                                     const std::string &error_message) const;
};

enum class CharacterEncoding :  std::underlying_type<H5T_cset_t>::type
{
  ASCII = H5T_CSET_ASCII,
  UTF8  = H5T_CSET_UTF8
};

class StringCreation : public List
{
  public:
    //!
    //! \brief constructor
    //!
    StringCreation();

    //!
    //! \brief destructor
    //!
    virtual ~StringCreation();

    CharacterEncoding character_encoding() const;
    void character_encoding(CharacterEncoding encoding) const;

  protected:
    StringCreation(const Class &plist_class);
};

class LinkAccess : public List
{
  public:
    LinkAccess();
    virtual ~LinkAccess();

    size_t nlinks() const;
    void nlinks(size_t size) const;

    boost::filesystem::path external_link_prefix() const;
    void external_link_prefix(const boost::filesystem::path &path) const;

  protected:
    LinkAccess(const Class &plist_class);
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

    size_t local_heap_size_hint() const;
    void local_heap_size_hint(size_t size) const;

    unsigned estimated_number_of_links() const;
    void estimated_number_of_links(unsigned nlinks) const;

    unsigned estimated_link_name_length() const;
    void estimated_link_name_length(unsigned name_length) const;

    void link_creation_order(CreationOrder order) const;
    CreationOrder link_creation_order() const;

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

    void collective_metadata_io(bool value) const;
    bool collective_metadata_io() const;

};

class LinkCreation : public List
{
  public:
    LinkCreation();
};



}  // namespace property_list
}  // namespace hdf5
