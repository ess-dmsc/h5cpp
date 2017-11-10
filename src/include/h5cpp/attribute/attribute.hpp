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
// Created on: Sep 14, 2017
//
#pragma once

#include <h5cpp/datatype/datatype.hpp>
#include <h5cpp/dataspace/dataspace.hpp>
#include <h5cpp/datatype/factory.hpp>
#include <h5cpp/dataspace/type_trait.hpp>
#include <h5cpp/property/dataset_transfer.hpp>
#include <h5cpp/object_handle.hpp>
#include <h5cpp/windows.hpp>
#include <h5cpp/types.hpp>
#include <initializer_list>

namespace hdf5 {
namespace attribute {

class DLL_EXPORT Attribute
{
  public:
    //!
    //! \brief constructor
    //!
    //! \param handle rvalue reference to the attributes handle
    //!
    Attribute(ObjectHandle &&handle);

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

    template<typename T>
    void write_fixed_length_string(const T &data,
                                   const datatype::Datatype &mem_type) const
    {
      using Trait = FixedLengthStringTrait<T>;
      auto buffer = Trait::to_buffer(data,datatype::String(datatype()));

      if(H5Awrite(static_cast<hid_t>(handle_),
                  static_cast<hid_t>(mem_type),
                  buffer.data())<0)
      {
        throw std::runtime_error("Failure to write data to attribute!");
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
        throw std::runtime_error("Failure to write data to attribute!");
      }

    }

    template<typename T>
    void write_contiguous_data(const T &data,
                               const datatype::Datatype &mem_type) const
    {
      const void *ptr = dataspace::cptr(data);
      if(H5Awrite(static_cast<hid_t>(handle_),static_cast<hid_t>(mem_type),ptr)<0)
      {
        throw std::runtime_error("Failure to write data to attribute!");
      }
    }

    template<typename T>
    void read_fixed_length_string(T &data,
                                  const datatype::Datatype &mem_type) const
    {
      using Trait = FixedLengthStringTrait<T>;

      typename Trait::BufferType buffer(dataspace().size()*datatype().size());

      if(H5Aread(static_cast<hid_t>(handle_),
                 static_cast<hid_t>(mem_type),
                 buffer.data())<0)
      {
        throw std::runtime_error("Failure to read data from attribute!");
      }

      data = Trait::from_buffer(buffer,datatype::String(datatype()));

    }

    template<typename T>
    void read_variable_length_string(T &data,
                                     const datatype::Datatype &mem_type) const
    {
      using Trait = VarLengthStringTrait<T>;

      typename Trait::BufferType buffer(dataspace().size());

      if(H5Aread(static_cast<hid_t>(handle_),
                 static_cast<hid_t>(mem_type),
                 buffer.data())<0)
      {
        throw std::runtime_error("Failure to read data from attribute!");
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
        throw std::runtime_error(ss.str());
      }

    }

    template<typename T>
    void read_contiguous_data(T &data,
                              const datatype::Datatype &mem_type) const
    {
      void *ptr = dataspace::ptr(data);

      if(H5Aread(static_cast<hid_t>(handle_),static_cast<hid_t>(mem_type),ptr)<0)
      {
        throw std::runtime_error("Failure to read data from attribute!");
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

  if(file_type.get_class()==datatype::Class::STRING)
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
  auto mem_type = datatype::create<T>();

  write(data,mem_type);
}

template<typename T>
void Attribute::read(T &data) const
{
  auto mem_type = datatype::create<T>();
  read(data,mem_type);
}

template<typename T>
void Attribute::read(T &data,const datatype::Datatype &mem_type) const
{
  datatype::Datatype file_type = datatype();

  check_size(dataspace::create(data),dataspace(),"read");

  if(file_type.get_class()==datatype::Class::STRING)
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
