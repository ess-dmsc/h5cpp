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
//
// Created on: Sep 7, 2017
//
#pragma once

#include <h5cpp/node/node.hpp>
#include <h5cpp/dataspace/dataspace.hpp>
#include <h5cpp/dataspace/hyperslab.hpp>
#include <h5cpp/datatype/datatype.hpp>
#include <h5cpp/property/dataset_transfer.hpp>
#include <h5cpp/core/types.hpp>
#include <h5cpp/core/variable_length_string.hpp>
#include <h5cpp/core/fixed_length_string.hpp>
#include <h5cpp/core/windows.hpp>
#include <h5cpp/property/link_creation.hpp>
#include <h5cpp/property/dataset_creation.hpp>
#include <h5cpp/property/dataset_access.hpp>
#include <h5cpp/error/error.hpp>

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
    //! \throws std::runtime_error in case that the node is not a dataset
    //! \param node reference to the original node from which to construct
    //!             the dataset.
    //!
    Dataset(const Node &node);

    //!
    //! \brief constructor
    //!
    //! \throws std::runtime_error in case of a failure
    //! \param base the base object for the dataset creation
    //! \param path the path to the new dataset
    //! \param space optional reference to a dataspace (default is a scalar one)
    //! \param lcpl optional reference to a link creation property list
    //! \param dcpl optional reference to a dataset creation property list
    //! \param dapl optional reference to a dataset access property list
    //!
    Dataset(const Group &base,const Path &path,
            const datatype::Datatype &type,
            const dataspace::Dataspace &space = dataspace::Scalar(),
            const property::LinkCreationList &lcpl = property::LinkCreationList(),
            const property::DatasetCreationList &dcpl = property::DatasetCreationList(),
            const property::DatasetAccessList &dapl = property::DatasetAccessList());

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
    //! \brief get the dataset creation property list used for creation
    //!
    //! Returns an instance of a dataset creation property list with the
    //! values used for the creation of the dataset.
    //!
    //! \throws std::runtime_error in case of a failure
    //! \return instance of DatasetCreationList
    //!
    property::DatasetCreationList creation_list() const;

    //!
    //! \brief get the dataset access property list for the instance
    //!
    //! Returns an instance of the dataset access property list for the
    //! dataset.
    //!
    //! \throws std::runtime_error in case of a failure
    //! \return instance of DatasetAccessList
    //!
    property::DatasetAccessList access_list() const;

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
    //! \deprecated this method is deprecated - use resize instead
    //!
    void extent(const Dimensions &dims) const;



    void extent(size_t dim,ssize_t delta_elements) const;


    //!
    //! \brief resize the dataset
    //!
    //! Allows to change the shape (number of elements along each dimensions)
    //! of a dataset. It is important to note that in such a case a previously
    //! requested dataspace though remaining a valid object does no longer
    //! describe the datasets layout correctly. The number of elements can be
    //! increased or decreased within the limits of the dataspace originally
    //! used to create the dataset.
    //!
    //! \throws std::runtime_error in case of a failure
    //! \param dims vector with new number of elements along each dimension
    //!
    void resize(const Dimensions &dims) const;



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
               const dataspace::Dataspace &file_space,
               const property::DatasetTransferList &dtpl =
                   property::DatasetTransferList()) const;

    //!
    //! @brief write data to the dataset
    //!
    //! This function allows specification of the memory dataspace and dataspace
    //! and optionally the dataset transfer property list.
    //!
    template<typename T>
    void write(const T &data,const datatype::Datatype &mem_type,
               const dataspace::Dataspace &mem_space,
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
              const dataspace::Dataspace &file_space,
              const property::DatasetTransferList &dtpl =
                  property::DatasetTransferList()) const;

    template<typename T>
    void read(T &data,
              const datatype::Datatype &mem_type,
              const dataspace::Dataspace &mem_space,
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
    //! \brief write dataset chunk
    //!
    //! Write a dataset chunk from an instance of T.
    //!
    //! \throws std::runtime_error in case of a failure
    //! \tparam T source type
    //! \param data reference to the source instance of T
    //! \param offset logical position of the first element of the chunk in the dataset's dataspace
    //! \param filter_mask mask of which filters are used with the chunk
    //! \param dtpl reference to a dataset transfer property list
    //!
    template<typename T>
      void write_chunk(const T &data,
                       std::vector<long long unsigned int> offset,
                       std::uint32_t filter_mask = 0,
                       const property::DatasetTransferList &dtpl =
                       property::DatasetTransferList())  const;

#if H5_VERSION_GE(1,10,2)

    //!
    //! \brief read dataset chunk
    //!
    //! Read a chunk from a dataset to an instance of T.
    //!
    //! \throws std::runtime_error in case of a failure
    //! \tparam T source type
    //! \param data reference to the source instance of T
    //! \param offset logical position of the first element of the chunk in the dataset's dataspace
    //! \param dtpl reference to a dataset transfer property list
    //! \return filter_mask mask of which filters are used with the chunk
    //!
    template<typename T>
      std::uint32_t read_chunk(T &data,
                       std::vector<long long unsigned int> offset,
                       const property::DatasetTransferList &dtpl =
                       property::DatasetTransferList())  const;

#endif

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
    //! This template method tries to deduce the memory type and memory space
    //! for the target type (where to write the data to) automatically using
    //! the appropriate type traits.
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

    //!
    //! @brief reading data from a dataset
    //!
    //! @throws std::runtime_error in case of a failure
    //! @param data reference to the target to which to read the data
    //! @param memory_type reference to the memory data type of the target
    //! @param memory_space reference to the memory data space of the target
    //! @param file_selection reference to the selection for the file dataspace
    //! @param dtpl optional reference to a dataset transfer property list
    //!
    template<typename T>
    void read(T &data,
              const datatype::Datatype &memory_type,
              const dataspace::Dataspace &memory_space,
              const dataspace::Selection &file_selection,
              const property::DatasetTransferList &dtpl = property::DatasetTransferList()) const;


  private:
    //!
    //! \brief static factory function for dataset creation
    //!
    //! This function is used in the constructors for the Dataset class
    //! in order to avoid code duplications.
    //!
    static Node create_dataset(const Group &base,
                               const Path &path,
                               const datatype::Datatype &type,
                               const dataspace::Dataspace &space,
                               const property::LinkCreationList &lcpl,
                               const property::DatasetCreationList &dcpl,
                               const property::DatasetAccessList &dapl);

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
        ss<<"Failure to write variable length data to dataset ["<<link().path()<<"]!";
        error::Singleton::instance().throw_with_stack(ss.str());
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
        ss<<"Failure to write contiguous data to dataset ["<<link().path()<<"]!";
        error::Singleton::instance().throw_with_stack(ss.str());
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
        error::Singleton::instance().throw_with_stack(ss.str());
      }
    }

    template<typename T>
    void write_fixed_length_string_data(const T &data,
                                        const datatype::Datatype &mem_type,
                                        const dataspace::Dataspace &mem_space,
                                        const datatype::Datatype &,
                                        const dataspace::Dataspace &file_space,
                                        const property::DatasetTransferList &dtpl) const
    {
      using Trait = FixedLengthStringTrait<T>;
      auto buffer = Trait::to_buffer(data,mem_type,mem_space);

      if(H5Dwrite(static_cast<hid_t>(*this),
                  static_cast<hid_t>(mem_type),
                  static_cast<hid_t>(mem_space),
                  static_cast<hid_t>(file_space),
                  static_cast<hid_t>(dtpl),
                  reinterpret_cast<void*>(buffer.data()))<0)
      {
        std::stringstream ss;
        ss<<"Failure to write fixed length string data to dataset ["<<link().path()<<"]!";
        error::Singleton::instance().throw_with_stack(ss.str());
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
        ss<<"Failure to read variable length data from dataset ["<<link().path()<<"]!";
        error::Singleton::instance().throw_with_stack(ss.str());
      }

      VarLengthBufferTrait<T>::from_buffer(buffer,data);

      if(H5Dvlen_reclaim(static_cast<hid_t>(file_type),
                         static_cast<hid_t>(file_space),
                         static_cast<hid_t>(dtpl),
                         buffer.data())<0)
      {
        error::Singleton::instance().throw_with_stack("Error reclaiming variable length memory!");
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
        ss<<"Failure to read contiguous data from dataset ["<<link().path()<<"]!";
        error::Singleton::instance().throw_with_stack(ss.str());
      }
    }

    template<typename T>
    void read_variable_length_string_data(T &data,
                                          const datatype::Datatype &mem_type,
                                          const dataspace::Dataspace &mem_space,
                                          const datatype::Datatype &,
                                          const dataspace::Dataspace &file_space,
                                          const property::DatasetTransferList &dtpl) const
    {
      using Trait = VarLengthStringTrait<T>;

      typename Trait::BufferType buffer(mem_space.size());


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
        error::Singleton::instance().throw_with_stack(ss.str());
      }

      Trait::from_buffer(buffer,data);

      if(buffer.size() > 0)
      {
	if(H5Dvlen_reclaim(static_cast<hid_t>(mem_type),
                         static_cast<hid_t>(mem_space),
                         static_cast<hid_t>(dtpl),
                         buffer.data())<0)
	{
	  std::stringstream ss;
	  ss<<"Error reclaiming memory from variable length string data in "
	    <<"dataset ["<<link().path()<<"]!";
	  error::Singleton::instance().throw_with_stack(ss.str());
	}
      }
    }

    template<typename T>
    void read_fixed_length_string_data(T &data,
                                       const datatype::Datatype &mem_type,
                                       const dataspace::Dataspace &mem_space,
                                       const datatype::Datatype &,
                                       const dataspace::Dataspace &file_space,
                                       const property::DatasetTransferList &dtpl) const
    {
      using Trait = FixedLengthStringTrait<T>;

      auto buffer = Trait::BufferType::create(mem_type,mem_space);

      if(file_space.size() > 0)
      {
	if(H5Dread(static_cast<hid_t>(*this),
		   static_cast<hid_t>(mem_type),
		   static_cast<hid_t>(mem_space),
		   static_cast<hid_t>(file_space),
		   static_cast<hid_t>(dtpl),
		   buffer.data())<0)
	  {
	    std::stringstream ss;
	    ss<<"Failure to read fixed length string data to dataset ["<<link().path()<<"]!";
	    error::Singleton::instance().throw_with_stack(ss.str());
	  }

	//get data out of the buffer
	data = Trait::from_buffer(buffer,mem_type,mem_space);
      }
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
void Dataset::write(const T &data,
                    const datatype::Datatype &mem_type,
                    const dataspace::Dataspace &mem_space,
                    const property::DatasetTransferList &dtpl) const
{
  auto file_space = dataspace();
  file_space.selection.all();

  write(data,mem_type,mem_space,file_space,dtpl);

}

template<typename T>
void Dataset::write_chunk(const T &data,
                          std::vector<long long unsigned int> offset,
                          std::uint32_t filter_mask,
                          const property::DatasetTransferList &dtpl) const
{
  auto memory_space = hdf5::dataspace::create(data);
  auto memory_type  = hdf5::datatype::create(data);
  size_t databytesize = memory_space.size() * memory_type.size();

  if(memory_type.get_class() == datatype::Class::INTEGER)
    {
#if H5_VERSION_GE(1,10,3)
      if(H5Dwrite_chunk(static_cast<hid_t>(*this),
                         static_cast<hid_t>(dtpl),
                         filter_mask,
                         offset.data(),
                         databytesize,
                         dataspace::cptr(data))<0)
	{
	  std::stringstream ss;
	  ss<<"Failure to write chunk data to dataset ["<<link().path()<<"]!";
	  error::Singleton::instance().throw_with_stack(ss.str());
	}
#else
      if(H5DOwrite_chunk(static_cast<hid_t>(*this),
                         static_cast<hid_t>(dtpl),
                         filter_mask,
                         offset.data(),
                         databytesize,
                         dataspace::cptr(data))<0)
	{
	  std::stringstream ss;
	  ss<<"Failure to write chunk data to dataset ["<<link().path()<<"]!";
	  error::Singleton::instance().throw_with_stack(ss.str());
	}
#endif
    }
  else
    {
      std::stringstream ss;
      ss<<"Failure to write non-integer chunk data to dataset ["<<link().path()<<"]!";
      error::Singleton::instance().throw_with_stack(ss.str());
    }
}

#if H5_VERSION_GE(1,10,2)

template<typename T>
std::uint32_t Dataset::read_chunk(T &data,
			 std::vector<long long unsigned int> offset,
			 const property::DatasetTransferList &dtpl) const
{
  auto memory_type  = hdf5::datatype::create(data);
  std::uint32_t filter_mask;
  if(memory_type.get_class() == datatype::Class::INTEGER)
    {
#if H5_VERSION_GE(1,10,3)
      if(H5Dread_chunk(static_cast<hid_t>(*this),
		       static_cast<hid_t>(dtpl),
		       offset.data(),
		       &filter_mask,
		       dataspace::ptr(data))<0)
	{
	  std::stringstream ss;
	  ss<<"Failure to read chunk data from dataset ["<<link().path()<<"]!";
	  error::Singleton::instance().throw_with_stack(ss.str());
	}
#else
      if(H5DOread_chunk(static_cast<hid_t>(*this),
		       static_cast<hid_t>(dtpl),
		       offset.data(),
		       &filter_mask,
		       dataspace::ptr(data))<0)
	{
	  std::stringstream ss;
	  ss<<"Failure to read chunk data from dataset ["<<link().path()<<"]!";
	  error::Singleton::instance().throw_with_stack(ss.str());
	}
#endif
    }
  else
    {
      std::stringstream ss;
      ss<<"Failure to read non-integer chunk data from dataset ["<<link().path()<<"]!";
      error::Singleton::instance().throw_with_stack(ss.str());
    }
  return filter_mask;
}

#endif

template<typename T>
void Dataset::write(const T &data,const property::DatasetTransferList &dtpl) const
{
  auto memory_space = hdf5::dataspace::create(data);
  auto memory_type  = hdf5::datatype::create(data);
  auto file_space  = dataspace();
  file_space.selection.all();

  if (file_space.size() == memory_space.size() &&
      memory_space.type() == dataspace::Type::SIMPLE &&
      file_space.type() == dataspace::Type::SIMPLE){
    const dataspace::Simple & mem_space = dataspace::Simple(memory_space);
    const dataspace::Simple & fl_space = dataspace::Simple(file_space);
    if(fl_space.rank() > 1 && mem_space.rank() == 1){
      write(data,memory_type,file_space,file_space,dtpl);
      return;
    }
  }
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
  try{
    const dataspace::Hyperslab & hyper = dynamic_cast<const dataspace::Hyperslab &>(selection);
      auto dims = hyper.block();
      auto count = hyper.count();
      for(Dimensions::size_type i = 0; i != dims.size(); i++)
	dims[i] *= count[i];

      dataspace::Simple selected_space(dims);
      if (selected_space.size() == memory_space.size())
	read(data,memory_type,selected_space,file_space,dtpl);
      else
	read(data,memory_type,memory_space,file_space,dtpl);
  }
  catch(const std::bad_cast&){
    read(data,memory_type,memory_space,file_space,dtpl);
  }
}

template<typename T>
void Dataset::read(T &data,
                   const datatype::Datatype &memory_type,
                   const dataspace::Dataspace &memory_space,
                   const dataspace::Selection &file_selection,
                   const property::DatasetTransferList &dtpl) const
{
  dataspace::Dataspace file_space = dataspace();
  file_space.selection(dataspace::SelectionOperation::SET,file_selection);
  read(data,memory_type,memory_space,file_space,dtpl);
}

template<typename T>
void Dataset::read(T &data,
                   const datatype::Datatype &memory_type,
                   const dataspace::Dataspace &memory_space,
                   const property::DatasetTransferList &dtpl) const
{
  dataspace::Dataspace file_space = dataspace();
  file_space.selection.all();
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
  if (memory_space.type() != dataspace::Type::SIMPLE) {
    write(data,memory_type,memory_space,file_space,dtpl);
  }
  else{
    try{

      const dataspace::Hyperslab & hyper = dynamic_cast<const dataspace::Hyperslab &>(selection);
      const dataspace::Simple & mem_space = dataspace::Simple(memory_space);

      auto dims = hyper.block();
      auto count = hyper.count();
      for(Dimensions::size_type i = 0; i != dims.size(); i++)
	dims[i] *= count[i];
      dataspace::Simple selected_space(dims);
      if(selected_space.rank() > 1 &&
	 mem_space.rank() == 1 &&
	 selected_space.size() == memory_space.size())
	write(data,memory_type,selected_space,file_space,dtpl);
      else
	write(data,memory_type,memory_space,file_space,dtpl);

    }
    catch(const std::bad_cast&){
      write(data,memory_type,memory_space,file_space,dtpl);
    }
  }
}


template<typename T>
void Dataset::read(T &data,const property::DatasetTransferList &dtpl) const
{
  auto memory_space = hdf5::dataspace::create(data);
  auto memory_type  = hdf5::datatype::create(data);
  auto file_space = dataspace();
  file_space.selection.all();

  if (file_space.size() == memory_space.size()){
    read(data,memory_type,file_space,file_space,dtpl);
  }
  else{
    read(data,memory_type,memory_space,file_space,dtpl);
  }

}


//!
//! \brief resize a dataset by a particular offset
//!
//! Resizes a dataset along the dimension determined by dimension_index
//! by delta elements. As delta is a signed integer one can either
//! enlarge or shrink the dataset.
//!
//! \param dataset reference to the dataset to resize
//! \param dimension_index the index of the dimension to resize
//! \param delta the number of elements about which the dataset should be resized
//! \throws std::runtime_error in case of any failure
//!
DLL_EXPORT void resize_by(const Dataset &dataset,size_t dimension_index,ssize_t delta);



} // namespace node
} // namespace hdf5
