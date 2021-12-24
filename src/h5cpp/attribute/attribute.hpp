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
// Created on: Sep 14, 2017
//
#pragma once

#include <h5cpp/datatype/datatype.hpp>
#include <h5cpp/dataspace/dataspace.hpp>
#include <h5cpp/datatype/factory.hpp>
#include <h5cpp/dataspace/type_trait.hpp>
#include <h5cpp/property/dataset_transfer.hpp>
#include <h5cpp/core/object_handle.hpp>
#include <h5cpp/core/windows.hpp>
#include <h5cpp/core/variable_length_string.hpp>
#include <h5cpp/core/fixed_length_string.hpp>
#include <h5cpp/core/types.hpp>
#include <h5cpp/node/link.hpp>
#include <h5cpp/error/error.hpp>
#include <initializer_list>
#include <h5cpp/core/utilities.hpp>
#include <h5cpp/contrib/stl/vector.hpp>

namespace hdf5 {
namespace attribute {

class DLL_EXPORT Attribute
{
  public:
    //!
    //! \brief constructor
    //!
    //! \param handle rvalue reference to the attributes handle
    //! \param parent_link like to the parent object
    //!
    Attribute(ObjectHandle &&handle,const node::Link &parent_link);

    //!
    //! \brief default constructor
    //!
    //! Uses default compiler implementation.
    //!
    Attribute() = default;

    //!
    //! \brief copy assignment operator
    //!
    //! Uses default compiler implementation.
    //!
    Attribute(const Attribute &) = default;

    //!
    //! \brief return the data type of the attribute
    //!
    //! Returns a copy of the datatype used to create the attribute.
    //!
    datatype::Datatype datatype() const;

    //!
    //! \brief return the dataspace of the attribute
    //!
    //! Returns the dataspace used to create the attribute.
    //!
    dataspace::Dataspace dataspace() const;

    //!
    //! \brief return the name of the attribute
    //!
    std::string name() const;

    //!
    //! \brief check if object is valid
    //!
    bool is_valid() const;

    //!
    //! @brief close the attribute
    //!
    //! This method will close the attribute and leave it in an invalid state.
    //! A subsequent call to is_valid should return false. The parent
    //! link remains valid though.
    //!
    void close();


    //!
    //! @brief conversion operator to hid_t
    //!
    operator hid_t() const
    {
      return static_cast<hid_t>(handle_);
    }

    //!
    //! @brief get the parent ndoe
    //!
    //! Return a reference to the node to which the attribute is attached.
    //!
    const node::Link &parent_link() const noexcept;

    //!
    //! \brief write data to attribute
    //!
    //! Write data to disk. This is the simplest form of writting
    //! datat to disk. Its only argument is a reference to the object
    //! holding the data which should be written.
    //!
    //! \throws std::runtime_error in case of a failure
    //!
    //! \tparam T data type to write to disk
    //! \param data reference to the datas instance
    //!
    template<typename T>
    void write(const T& data) const;

    //!
    //! \brief write string literal to disk
    //!
    //! This is used whenever a string literal must be
    //! written to disk.
    //!
    //! \code
    //! attribute::Attribute a = dataset.attributes.create<std::string>("note");
    //! a.write("a short text");
    //! \endcode
    //!
    //! You should be aware that this currently only works if the
    //! string type used for the attribute is a variable length string.
    //!
    //! \throws std::runtime_error in case of a failure
    //!
    void write(const char *data) const;

    //!
    //! \brief write from initializer list
    //!
    //! This method is used if the data to write is provided via
    //! an initializer list.
    //!
    //! \code
    //! Attribute a = dataset.attributes.create<int>("index_list",{4});
    //! a.write({56,23,4,12});
    //! \endcode
    //!
    //! Internaly this method stores the content of the list to an instance
    //! of std::vector<T> which is then written to the attribute.
    //!
    //! \tparam T type of the list elements
    //! \param list reference to the initializer list
    //!
    template<typename T>
    void write(const std::initializer_list<T> &list) const
    {
      write(std::vector<T>{list});
    }

    //!
    //! \brief write data to disk
    //!
    //! Write data to disk however we can pass a custom memory type
    //! to this method. This is particularly useful in the case of
    //! string types where the HDF5 datatype cannot be determined
    //! uniquely from a C++ type.
    //!
    //! \code
    //! String fixed_type = String::fixed(20);
    //! Attribute a = dataset.attributes.create("note",fixed_type,Scalar());
    //!
    //! //we have to pass the type here explicitely otherwise the library
    //! //would take std::string as a variable length string and HDF5
    //! //considers variable and fixed length strings as incompatible.
    //! std::string data = "hello";
    //! a.write(data,fixed_type);
    //! \endcode
    //!
    //! \throws std::runtime_error in case of an error
    //! \tparam T type of input data
    //! \param data refernce to input data
    //! \param mem_type HDF5 memory type of the input data
    //!
    template<typename T>
    void write(const T& data,const datatype::Datatype &mem_type) const;
    void write(const char *data,const datatype::Datatype &mem_type) const;

    template<typename T>
    void read(T &data) const;

    template<typename T>
    void read(T &data,const datatype::Datatype &mem_type) const;

  private:
    ObjectHandle handle_;
    node::Link   parent_link_;

    template<typename T>
    void read(T &data,const datatype::Datatype &mem_type, const datatype::Datatype &file_type) const;

    template<typename T>
    void write_fixed_length_string(const T &data,
                                   const datatype::Datatype &mem_type) const
    {
      using Trait = FixedLengthStringTrait<T>;
      using SpaceTrait = hdf5::dataspace::TypeTrait<T>;
      auto buffer = Trait::to_buffer(data,mem_type,SpaceTrait::create(data));

      if(H5Awrite(static_cast<hid_t>(handle_),
                  static_cast<hid_t>(mem_type),
                  buffer.data())<0)
      {
        error::Singleton::instance().throw_with_stack("Failure to write data to attribute!");
      }

    }

    template<typename T>
    void write_variable_length_string(const T &data,
                                      const datatype::Datatype &mem_type) const
    {
      using Trait = VarLengthStringTrait<T>;
      auto buffer = Trait::to_buffer(data);

      if(H5Awrite(static_cast<hid_t>(handle_),
                  static_cast<hid_t>(mem_type),
                  buffer.data())<0)
      {
        error::Singleton::instance().throw_with_stack("Failure to write data to attribute!");
      }

    }

    template<typename T>
    void write_contiguous_data(const T &data,
                               const datatype::Datatype &mem_type) const
    {
      const void *ptr = dataspace::cptr(data);
      if(H5Awrite(static_cast<hid_t>(handle_),static_cast<hid_t>(mem_type),ptr)<0)
      {
        error::Singleton::instance().throw_with_stack("Failure to write data to attribute!");
      }
    }

    template<typename T>
    void read_fixed_length_string(T &data,
                                  const datatype::Datatype &mem_type) const
    {
      using Trait = FixedLengthStringTrait<T>;
      using SpaceTrait = hdf5::dataspace::TypeTrait<T>;

      auto buffer = Trait::BufferType::create(mem_type,SpaceTrait::create(data));

      if(H5Aread(static_cast<hid_t>(handle_),
                 static_cast<hid_t>(mem_type),
                 buffer.data())<0)
      {
        error::Singleton::instance().throw_with_stack("Failure to read data from attribute!");
      }

      data = Trait::from_buffer(buffer,mem_type,SpaceTrait::create(data));

    }

    template<typename T>
    void read_variable_length_string(T &data,
                                     const datatype::Datatype &mem_type) const
    {
      using Trait = VarLengthStringTrait<T>;

      typename Trait::BufferType buffer(signed2unsigned<typename std::vector<T>::size_type>(dataspace().size()));

      if(H5Aread(static_cast<hid_t>(handle_),
                 static_cast<hid_t>(mem_type),
                 buffer.data())<0)
      {
        error::Singleton::instance().throw_with_stack("Failure to read data from attribute!");
      }

      Trait::from_buffer(buffer,data);

      if(H5Dvlen_reclaim(static_cast<hid_t>(mem_type),
                         static_cast<hid_t>(dataspace()),
                         static_cast<hid_t>(property::DatasetTransferList()),
                         buffer.data())<0)
      {
        std::stringstream ss;
        ss<<"Failure to reclaim buffer for variable length string"
          <<" string read on attribute!";
        error::Singleton::instance().throw_with_stack(ss.str());
      }

    }

    template<typename T>
    void read_contiguous_data(T &data,
                              const datatype::Datatype &mem_type) const
    {
      void *ptr = dataspace::ptr(data);

      if(H5Aread(static_cast<hid_t>(handle_),static_cast<hid_t>(mem_type),ptr)<0)
      {
        error::Singleton::instance().throw_with_stack("Failure to read data from attribute!");
      }
    }

    void check_size(const dataspace::Dataspace &mem_space,
                    const dataspace::Dataspace &file_space,
                    const std::string &operation) const;

};

template<typename T>
void Attribute::write(const T &data,const datatype::Datatype &mem_type) const
{
  datatype::Datatype file_type = datatype();

  check_size(dataspace::create(data),dataspace(),"write");

  if(file_type.get_class()==datatype::Class::String)
  {
    datatype::String string_type(file_type);

    if(string_type.is_variable_length())
    {
      write_variable_length_string(data,mem_type);
    }
    else
    {
      write_fixed_length_string(data,mem_type);
    }
  }
  else
  {
    write_contiguous_data(data,mem_type);
  }
}

template<typename T>
void Attribute::write(const T &data) const
{
  hdf5::datatype::DatatypeHolder mem_type_holder;

  write(data,mem_type_holder.get<T>());
}

template<typename T>
void Attribute::read(T &data) const
{
  auto file_type = datatype();
  if(file_type.get_class() == datatype::Class::String)
  {
    read(data, file_type);
  }
  else
  {
    hdf5::datatype::DatatypeHolder mem_type_holder;
    read(data, mem_type_holder.get<T>(), file_type);
  }
}

template<typename T>
void Attribute::read(T &data,const datatype::Datatype &mem_type) const
{
  datatype::Datatype file_type = datatype();
  read(data, mem_type, file_type);
}

template<typename T>
void Attribute::read(T &data, const datatype::Datatype &mem_type, const datatype::Datatype &file_type) const
{
  check_size(dataspace::create(data),dataspace(),"read");

  if(file_type.get_class()==datatype::Class::String)
  {
    datatype::String string_type(file_type);

    if(string_type.is_variable_length())
    {
      read_variable_length_string(data,mem_type);
    }
    else
    {
      read_fixed_length_string(data,mem_type);
    }
  }
  else
  {
    read_contiguous_data(data,mem_type);
  }
}



} // namespace attribute
} // namespace hdf5
