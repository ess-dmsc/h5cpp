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
// Created on: Sep 7, 2017
//
#pragma once

#include <h5cpp/node/node.hpp>
#include <h5cpp/dataspace/dataspace.hpp>
#include <h5cpp/datatype/datatype.hpp>
#include <h5cpp/property/dataset_transfer.hpp>
#include <h5cpp/types.hpp>
#include <h5cpp/windows.hpp>

namespace hdf5 {
namespace node {

class Selection;

class DLL_EXPORT Dataset : public Node
{
  public:
    //!
    //! \brief default constructor
    //!
    //! Use default implementation here. We need this for some STL containers.
    //! After default construction the dataset is in an invalid state.
    //!
    //! \sa is_valid()
    //!
    Dataset() = default;

    //!
    //! \brief copy constructor
    //!
    //! Use default implementation here.
    //!
    Dataset(const Dataset &) = default;

    //!
    //! \brief construct
    //!
    //! Construct a dataset from a node instance.
    //!
    Dataset(const Node &node);

    //!
    //! \brief get dataspace of dataset
    //!
    //! Return a new instance of the dataspace describing the dataset.
    //!
    //! \throws std::runtime_error in case of a failure
    //! \return new dataspace instance
    //!
    dataspace::Dataspace dataspace() const;

    //!
    //! \brief get datatype of dataset
    //!
    //! Return an instance of the datatype describing the elements stored
    //! in the file.
    //!
    //! \throws std::runtime_error in case of a failure
    //! \return new instance of datatype
    //!
    datatype::Datatype datatype() const;

    //!
    //! \brief set extent of the dataset
    //!
    //! Allows to change the extent (number of elements along each dimensions)
    //! of a dataset. It is important to note that in such a case a previously
    //! requested dataspace though remaining a valid object does no longer
    //! describe the datasets layout correctly. The number of elements can be
    //! increased or decreased within the limits of the dataspace originally
    //! used to create the dataset.
    //!
    //! \throws std::runtime_error in case of a failure
    //! \param dims vector with new number of elements along each dimension
    //!
    void extent(const Dimensions &dims) const;

    void extent(size_t dim,ssize_t delta_elements) const;

#if H5_VERSION_GE(1,10,0)
    void refresh() const;
#endif


    //!
    //! \brief write data to the dataset
    //!
    //! This template function a very simple wrapper around the original HDF5
    //! C-API function. The major difference is that a type trait is used to
    //! obtain a pointer to the data passed as the first argument.
    //! This template is provided for maximum flexibility as it allows virtually
    //! to do everything which could be done with the C-API.
    //!
    //! \throws std::runtime_error  in case of a failure
    //! \tparam T type from which to write data
    //! \param data const reference to the data source
    //! \param mem_type reference to the memory data type
    //! \param mem_space reference to the memory data space
    //! \param file_space reference to the dataspace in the file
    //! \param dtpl data transfer property list
    //!
    template<typename T>
    void write(const T &data,const datatype::Datatype &mem_type,
               const dataspace::Dataspace &mem_space,
               const dataspace::Dataspace &file_space =
                   dataspace::Dataspace(ObjectHandle(H5S_ALL,ObjectHandle::Policy::WITHOUT_WARD)),
               const property::DatasetTransferList &dtpl =
                   property::DatasetTransferList()) const;

    //!
    //! \brief read data from the dataset
    //!
    //! This template function a very simple wrapper around the original HDF5
    //! C-API function. The major difference is that a type trait is used to
    //! obtain a pointer to the data passed as the first argument.
    //! This template is provided for maximum flexibility as it allows virtually
    //! to do everything which could be done with the C-API.
    //!
    //! \throws std::runtime_error  in case of a failure
    //! \tparam T type from which to write data
    //! \param data const reference to the data source
    //! \param mem_type reference to the memory data type
    //! \param mem_space reference to the memory data space
    //! \param file_space reference to the dataspace in the file
    //! \param dtpl data transfer property list
    //!
    template<typename T>
    void read(T &data,const datatype::Datatype &mem_type,
              const dataspace::Dataspace &mem_space,
              const dataspace::Dataspace &file_space =
                  dataspace::Dataspace(ObjectHandle(H5S_ALL,ObjectHandle::Policy::WITHOUT_WARD)),
              const property::DatasetTransferList &dtpl =
                  property::DatasetTransferList()) const;


    //!
    //! \brief write entire dataset
    //!
    //! Write the entire dataset from an instance of T.
    //!
    //! \throws std::runtime_error in caes of a failure
    //! \tparam T source type
    //! \param data reference to the source instance of T
    //! \param dtpl reference to a dataset transfer property list
    //!
    template<typename T>
    void write(const T &data,const property::DatasetTransferList &dtpl =
                                   property::DatasetTransferList()) const;

    void write(const char *data,const property::DatasetTransferList &dtpl =
                                      property::DatasetTransferList()) const;

    //!
    //! \brief read entire dataset
    //!
    //! Read the entire data from a dataset to an instance of T.
    //!
    //! \throws std::runtime_error in case of a failre
    //! \tparam T destination type
    //! \param data reference to the destination
    //! \param dtpl reference to a dataset transfer property list
    //!
    template<typename T>
    void read(T &data,const property::DatasetTransferList &dtpl =
                            property::DatasetTransferList()) const;

    //!
    //! \brief write data to a selection
    //!
    //! Write data from an instance of T to a selection of the dataset.
    //!
    //! \throws std::runtime_error in case of a failure
    //! \tparam T type of the source
    //! \param data reference to the source
    //! \param selection reference to the selection
    //! \param dtpl reference to a dataset transfer property list
    //!
    template<typename T>
    void write(const T &data,const dataspace::Selection &selection,
               const property::DatasetTransferList &dtpl =
                   property::DatasetTransferList()) const;

    //!
    //! \brief reading data from a selection
    //!
    //! Reading data to an instance of T from a selection of a dataset.
    //!
    //! \throws std::runtime_error in case of a failure
    //! \tparam T type of the destination object
    //! \param data reference to the destination object
    //! \param selection reference to the selection
    //! \param dtpl reference to a dataset transfer property list
    //!
    template<typename T>
    void read(T &data,const dataspace::Selection &selection,
              const property::DatasetTransferList &dtpl =
                  property::DatasetTransferList()) const;

  private:

    //
    // writing template methods for various data configurations
    //
    template<typename T>
    void write_variable_length_data(const T &data,
                                    const datatype::Datatype &mem_type,
                                    const dataspace::Dataspace &mem_space,
                                    const datatype::Datatype &,
                                    const dataspace::Dataspace &file_space,
                                    const property::DatasetTransferList &dtpl) const
    {
      VarLengthDataBuffer buffer;
      VarLengthBufferTrait<T>::to_buffer(data,buffer);
      if(H5Dwrite(static_cast<hid_t>(*this),
                     static_cast<hid_t>(mem_type),
                     static_cast<hid_t>(mem_space),
                     static_cast<hid_t>(file_space),
                     static_cast<hid_t>(dtpl),
                     buffer.data())<0)
      {
        std::stringstream ss;
        ss<<"Failure to write data to dataset ["<<link().path()<<"]!";
        throw std::runtime_error(ss.str());
      }
    }

    template<typename T>
    void write_contiguous_data(const T &data,
                               const datatype::Datatype &mem_type,
                               const dataspace::Dataspace &mem_space,
                               const datatype::Datatype &,
                               const dataspace::Dataspace &file_space,
                               const property::DatasetTransferList &dtpl) const
    {
      if(H5Dwrite(static_cast<hid_t>(*this),
                  static_cast<hid_t>(mem_type),
                  static_cast<hid_t>(mem_space),
                  static_cast<hid_t>(file_space),
                  static_cast<hid_t>(dtpl),
                  dataspace::cptr(data))<0)
      {
        std::stringstream ss;
        ss<<"Failure to write data to dataset ["<<link().path()<<"]!";
        throw std::runtime_error(ss.str());
      }
    }

    template<typename T>
    void write_variable_length_string_data(const T &data,
                                           const datatype::Datatype &mem_type,
                                           const dataspace::Dataspace &mem_space,
                                           const datatype::Datatype &,
                                           const dataspace::Dataspace &file_space,
                                           const property::DatasetTransferList &dtpl) const
    {
      using Trait = VarLengthStringTrait<T>;
      auto buffer = Trait::to_buffer(data);

      if(H5Dwrite(static_cast<hid_t>(*this),
                  static_cast<hid_t>(mem_type),
                  static_cast<hid_t>(mem_space),
                  static_cast<hid_t>(file_space),
                  static_cast<hid_t>(dtpl),
                  reinterpret_cast<void*>(buffer.data()))<0)
      {
        std::stringstream ss;
        ss<<"Failure to write variable length string data to dataset ["<<link().path()<<"]!";
        throw std::runtime_error(ss.str());
      }
    }

    template<typename T>
    void write_fixed_length_string_data(const T &data,
                                        const datatype::Datatype &mem_type,
                                        const dataspace::Dataspace &mem_space,
                                        const datatype::Datatype &file_type,
                                        const dataspace::Dataspace &file_space,
                                        const property::DatasetTransferList &dtpl) const
    {
      using Trait = FixedLengthStringTrait<T>;
      auto buffer = Trait::to_buffer(data,file_type);

      if(H5Dwrite(static_cast<hid_t>(*this),
                  static_cast<hid_t>(mem_type),
                  static_cast<hid_t>(mem_space),
                  static_cast<hid_t>(file_space),
                  static_cast<hid_t>(dtpl),
                  reinterpret_cast<void*>(buffer.data()))<0)
      {
        std::stringstream ss;
        ss<<"Failure to write fixed length string data to dataset ["<<link().path()<<"]!";
        throw std::runtime_error(ss.str());
      }


    }

    //
    // reading template methods for various data configurations
    //
    template<typename T>
    void read_variable_length_data(T &data,
                                   const datatype::Datatype &mem_type,
                                   const dataspace::Dataspace &mem_space,
                                   const datatype::Datatype &file_type,
                                   const dataspace::Dataspace &file_space,
                                   const property::DatasetTransferList &dtpl) const
    {
      VarLengthDataBuffer buffer;
      if(file_space.selection.type() != dataspace::SelectionType::ALL)
      {
        buffer.resize(file_space.selection.size());
      }
      else
      {
        buffer.resize(file_space.size());
      }

      if(H5Dread(static_cast<hid_t>(*this),
                 static_cast<hid_t>(mem_type),
                 static_cast<hid_t>(mem_space),
                 static_cast<hid_t>(file_space),
                 static_cast<hid_t>(dtpl),
                 buffer.data())<0)
      {
        std::stringstream ss;
        ss<<"Failure to write data to dataset ["<<link().path()<<"]!";
        throw std::runtime_error(ss.str());
      }

      VarLengthBufferTrait<T>::from_buffer(buffer,data);

      if(H5Dvlen_reclaim(static_cast<hid_t>(file_type),
                         static_cast<hid_t>(file_space),
                         static_cast<hid_t>(dtpl),
                         buffer.data())<0)
      {
        throw std::runtime_error("Error reclaiming variable length memory!");
      }
    }

    template<typename T>
    void read_contiguous_data(T &data,
                              const datatype::Datatype &mem_type,
                              const dataspace::Dataspace &mem_space,
                              const datatype::Datatype &,
                              const dataspace::Dataspace &file_space,
                              const property::DatasetTransferList &dtpl) const
    {
      if(H5Dread(static_cast<hid_t>(*this),
                 static_cast<hid_t>(mem_type),
                 static_cast<hid_t>(mem_space),
                 static_cast<hid_t>(file_space),
                 static_cast<hid_t>(dtpl),
                 dataspace::ptr(data))<0)
      {
        std::stringstream ss;
        ss<<"Failure to write data to dataset ["<<link().path()<<"]!";
        throw std::runtime_error(ss.str());
      }
    }

    template<typename T>
    void read_variable_length_string_data(T &data,
                                          const datatype::Datatype &mem_type,
                                          const dataspace::Dataspace &mem_space,
                                          const datatype::Datatype &file_type,
                                          const dataspace::Dataspace &file_space,
                                          const property::DatasetTransferList &dtpl) const
    {
      using Trait = VarLengthStringTrait<T>;

      typename Trait::BufferType buffer;
      if(file_space.selection.type() == dataspace::SelectionType::ALL)
        buffer = typename Trait::BufferType(file_space.size());
      else
        buffer = typename Trait::BufferType(file_space.selection.size());


      if(H5Dread(static_cast<hid_t>(*this),
                 static_cast<hid_t>(mem_type),
                 static_cast<hid_t>(mem_space),
                 static_cast<hid_t>(file_space),
                 static_cast<hid_t>(dtpl),
                 buffer.data())<0)
      {
        std::stringstream ss;
        ss<<"Failure to read variable length string data from dataset ["
          <<link().path()<<"]!";
        throw std::runtime_error(ss.str());
      }

      Trait::from_buffer(buffer,data);

      if(H5Dvlen_reclaim(static_cast<hid_t>(file_type),
                         static_cast<hid_t>(file_space),
                         static_cast<hid_t>(dtpl),
                         buffer.data())<0)
      {
        std::stringstream ss;
        ss<<"Error reclaiming memory from variable length string data in "
          <<"dataset ["<<link().path()<<"]!";
        throw std::runtime_error(ss.str());
      }


    }

    template<typename T>
    void read_fixed_length_string_data(T &data,
                                       const datatype::Datatype &mem_type,
                                       const dataspace::Dataspace &mem_space,
                                       const datatype::Datatype &file_type,
                                       const dataspace::Dataspace &file_space,
                                       const property::DatasetTransferList &dtpl) const
    {
      using Trait = FixedLengthStringTrait<T>;

      typename Trait::BufferType buffer;
      if(file_space.selection.type()==dataspace::SelectionType::ALL)
        buffer = typename Trait::BufferType(file_type.size()*file_space.size());
      else
        buffer = typename Trait::BufferType(file_type.size()*file_space.selection.size());

      if(H5Dread(static_cast<hid_t>(*this),
                 static_cast<hid_t>(mem_type),
                 static_cast<hid_t>(mem_space),
                 static_cast<hid_t>(file_space),
                 static_cast<hid_t>(dtpl),
                 buffer.data())<0)
      {
        std::stringstream ss;
        ss<<"Failure to read fixed length string data to dataset ["<<link().path()<<"]!";
        throw std::runtime_error(ss.str());
      }

      //get data out of the buffer
      data = Trait::from_buffer(buffer,file_type);

    }
};

template<typename T>
void Dataset::write(const T &data,const datatype::Datatype &mem_type,
                                  const dataspace::Dataspace &mem_space,
                                  const dataspace::Dataspace &file_space,
                                  const property::DatasetTransferList &dtpl) const
{
  datatype::Datatype file_type = datatype();

  if(file_type.get_class() == datatype::Class::VARLENGTH)
  {
    write_variable_length_data(data,mem_type,mem_space,file_type,file_space,dtpl);
  }
  else if(file_type.get_class() == datatype::Class::STRING)
  {
    datatype::String string_type(file_type);
    if(string_type.is_variable_length())
    {
      write_variable_length_string_data(data,mem_type,mem_space,file_type,file_space,dtpl);
    }
    else
    {
      write_fixed_length_string_data(data,mem_type,mem_space,file_type,file_space,dtpl);
    }
  }
  else
  {
    write_contiguous_data(data,mem_type,mem_space,file_type,file_space,dtpl);
  }

}

template<typename T>
void Dataset::write(const T &data,const property::DatasetTransferList &dtpl) const
{
  auto memory_space = hdf5::dataspace::create(data);
  auto memory_type  = hdf5::datatype::create(data);
  auto file_space  = dataspace();
  file_space.selection.all();

  write(data,memory_type,memory_space,file_space,dtpl);
}


template<typename T>
void Dataset::read(T &data,const datatype::Datatype &mem_type,
                           const dataspace::Dataspace &mem_space,
                           const dataspace::Dataspace &file_space,
                           const property::DatasetTransferList &dtpl) const
{
  datatype::Datatype file_type = datatype();
  if(file_type.get_class() == datatype::Class::VARLENGTH)
  {
    read_variable_length_data(data,mem_type,mem_space,file_type,file_space,dtpl);
  }
  else if(file_type.get_class() == datatype::Class::STRING)
  {
    datatype::String string_type(file_type);
    if(string_type.is_variable_length())
    {
      read_variable_length_string_data(data,mem_type,mem_space,file_type,file_space,dtpl);
    }
    else
    {
      read_fixed_length_string_data(data,mem_type,mem_space,file_type,file_space,dtpl);
    }
  }
  else
  {
    read_contiguous_data(data,mem_type,mem_space,file_type,file_space,dtpl);
  }

}

template<typename T>
void Dataset::read(T &data,const dataspace::Selection &selection,
                   const property::DatasetTransferList &dtpl) const
{
  auto memory_space = hdf5::dataspace::create(data);
  auto memory_type  = hdf5::datatype::create(data);

  dataspace::Dataspace file_space = dataspace();
  file_space.selection(dataspace::SelectionOperation::SET,selection);

  read(data,memory_type,memory_space,file_space,dtpl);

}

template<typename T>
void Dataset::write(const T &data,const dataspace::Selection &selection,
                    const property::DatasetTransferList &dtpl) const
{
  auto memory_space = hdf5::dataspace::create(data);
  auto memory_type  = hdf5::datatype::create(data);

  dataspace::Dataspace file_space = dataspace();
  file_space.selection(dataspace::SelectionOperation::SET,selection);
  write(data,memory_type,memory_space,file_space,dtpl);
}

template<typename T>
void Dataset::read(T &data,const property::DatasetTransferList &dtpl) const
{
  auto memory_space = hdf5::dataspace::create(data);
  auto memory_type  = hdf5::datatype::create(data);
  auto file_space = dataspace();
  file_space.selection.all();

  read(data,memory_type,memory_space,file_space,dtpl);

}



} // namespace node
} // namespace hdf5
