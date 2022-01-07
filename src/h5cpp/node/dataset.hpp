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
#include <h5cpp/dataspace/pool.hpp>
#include <h5cpp/property/dataset_transfer.hpp>
#include <h5cpp/core/types.hpp>
#include <h5cpp/core/variable_length_string.hpp>
#include <h5cpp/core/fixed_length_string.hpp>
#include <h5cpp/core/windows.hpp>
#include <h5cpp/property/link_creation.hpp>
#include <h5cpp/property/dataset_creation.hpp>
#include <h5cpp/property/dataset_access.hpp>
#include <h5cpp/filter/external_filter.hpp>
#include <h5cpp/error/error.hpp>
#include <vector>
#include <h5cpp/core/utilities.hpp>

namespace hdf5 {
namespace node {

class Selection;

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif
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
    //! \param type optional reference to a datatype
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
    #ifdef __clang__
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wdocumentation-deprecated-sync"
    #endif
    void extent(const Dimensions &dims) const;
    #ifdef __clang__
    #pragma clang diagnostic pop
    #endif



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



#if (defined(_DOXYGEN_) || H5_VERSION_GE(1,10,0))
    //!
    //! \brief refresh the dataset (*since hdf5 1.10.0*)
    //!
    //!
    //! \throws std::runtime_error in case of a failure
    //!
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
                   property::DatasetTransferList::get()) const;

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
                   property::DatasetTransferList::get()) const;

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
                  property::DatasetTransferList::get()) const;

    template<typename T>
    void read(T &data,
              const datatype::Datatype &mem_type,
              const dataspace::Dataspace &mem_space,
              const property::DatasetTransferList &dtpl =
                  property::DatasetTransferList::get()) const;

    template<typename T>
    void read_reshape(T &data,
		      const datatype::Datatype &mem_type,
		      const dataspace::Dataspace &mem_space,
		      const property::DatasetTransferList &dtpl =
		      property::DatasetTransferList::get()) const;


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
                                   property::DatasetTransferList::get());
    template<typename T>
    void write(const T &data,const property::DatasetTransferList &dtpl =
                                   property::DatasetTransferList::get()) const;

    //!
    //! \brief write entire dataset
    //!
    //! Write the entire dataset from an instance of T.
    //! It reshapes the mem_space if its rank does not match to the selection rank
    //!
    //! \throws std::runtime_error in caes of a failure
   //! \tparam T source type
    //! \param data reference to the source instance of T
    //! \param mem_type reference to the memory data type
    //! \param mem_space reference to the memory data space
    //! \param dtpl reference to a dataset transfer property list
    //!
    template<typename T>
    void write_reshape(const T &data,
		       const datatype::Datatype &mem_type,
		       const dataspace::Dataspace &mem_space,
		       const property::DatasetTransferList &dtpl =
		       property::DatasetTransferList::get()) const;

    //!
    //! \brief write entire dataset
    //!
    //! Write the entire dataset from an instance of const char *
    //!
    //! \throws std::runtime_error in caes of a failure
    //! \param data pointer to the source instance of const char *
    //! \param dtpl reference to a dataset transfer property list
    //!
    void write(const char *data,const property::DatasetTransferList &dtpl =
                                      property::DatasetTransferList::get());
    void write(const char *data,const property::DatasetTransferList &dtpl =
                                      property::DatasetTransferList::get()) const;

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
		     std::vector<unsigned long long> offset,
		     std::uint32_t filter_mask = 0,
		     const property::DatasetTransferList &dtpl =
		     property::DatasetTransferList::get());

    template<typename T>
    void write_chunk(const T &data,
		     std::vector<unsigned long long> offset,
		     std::uint32_t filter_mask = 0,
		     const property::DatasetTransferList &dtpl =
		     property::DatasetTransferList::get()) const;

    //!
    //! \brief write dataset chunk
    //!
    //! Write a dataset chunk from an instance of T.
    //!
    //! \throws std::runtime_error in case of a failure
    //! \tparam T source type
    //! \param data reference to the source instance of T
    //! \param mem_type reference to the memory data type
    //! \param mem_space reference to the memory data space
    //! \param offset logical position of the first element of the chunk in the dataset's dataspace
    //! \param filter_mask mask of which filters are used with the chunk
    //! \param dtpl reference to a dataset transfer property list
    //!
    template<typename T>
    void write_chunk(const T &data,
		     const datatype::Datatype &mem_type,
		     const dataspace::Dataspace &mem_space,
		     std::vector<unsigned long long> & offset,
		     std::uint32_t filter_mask = 0,
		     const property::DatasetTransferList &dtpl =
		     property::DatasetTransferList::get())  const;

#if (defined(_DOXYGEN_) || H5_VERSION_GE(1,10,2))

    //!
    //! \brief read dataset chunk  (*since hdf5 1.10.2*)
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
			       std::vector<unsigned long long> offset,
			       const property::DatasetTransferList &dtpl =
			       property::DatasetTransferList::get())  const;


    //!
    //! \brief read dataset chunk
    //!
    //! Read a chunk from a dataset to an instance of T.
    //!
    //! \throws std::runtime_error in case of a failure
    //! \tparam T source type
    //! \param data reference to the source instance of T
    //! \param mem_type reference to the memory data type
    //! \param offset logical position of the first element of the chunk in the dataset's dataspace
    //! \param dtpl reference to a dataset transfer property list
    //! \return filter_mask mask of which filters are used with the chunk
    //!
    template<typename T>
      std::uint32_t read_chunk(T &data,
			       const datatype::Datatype &mem_type,
			       std::vector<unsigned long long> & offset,
			       const property::DatasetTransferList &dtpl =
			       property::DatasetTransferList::get())  const;


    //!
    //! \brief read dataset chunk
    //!
    //! Read a chunk storage size from a dataset to an instance of T.
    //!
    //! \throws std::runtime_error in case of a failure
    //! \param offset logical position of the first element of the chunk in the dataset's dataspace
    //! \return the size in bytes for the chunk.
    //!
      unsigned long long chunk_storage_size(std::vector<unsigned long long> offset)  const;

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
                            property::DatasetTransferList::get());
    template<typename T>
    void read(T &data,const property::DatasetTransferList &dtpl =
                            property::DatasetTransferList::get()) const;

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
	            property::DatasetTransferList::get());
    template<typename T>
    void write(const T &data,const dataspace::Selection &selection,
               const property::DatasetTransferList &dtpl =
	            property::DatasetTransferList::get()) const;

    //!
    //! \brief write data to a selection
    //!
    //! Write data from an instance of T to a selection of the dataset.
    //! It reshapes the mem_space if its rank does not match to the selection rank
    //!
    //! \throws std::runtime_error in case of a failure
    //! \tparam T type of the source
    //! \param data reference to the source
    //! \param mem_type reference to the memory data type
    //! \param mem_space reference to the memory data space
    //! \param selection reference to the selection
    //! \param dtpl reference to a dataset transfer property list
    //!
    template<typename T>
    void write_reshape(const T &data,
		       const datatype::Datatype &mem_type,
		       const dataspace::Dataspace &mem_space,
		       const dataspace::Selection &selection,
		       const property::DatasetTransferList &dtpl =
		       property::DatasetTransferList::get()) const;

    //!
    //! \brief reading data from a selection
    //!
    //! Reading data to an instance of T from a selection of a dataset.
    //! It reshapes the mem_space if its rank does not match to the selection rank
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
                  property::DatasetTransferList::get());
    template<typename T>
    void read(T &data,const dataspace::Selection &selection,
              const property::DatasetTransferList &dtpl =
                  property::DatasetTransferList::get()) const;

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
    //! \param mem_type reference to the memory data type
    //! \param mem_space reference to the memory data space
    //! \param selection reference to the selection
    //! \param dtpl reference to a dataset transfer property list
    //!
    template<typename T>
    void read_reshape(T &data,
		      const datatype::Datatype &mem_type,
		      const dataspace::Dataspace &mem_space,
		      const dataspace::Selection &selection,
		      const property::DatasetTransferList &dtpl =
		      property::DatasetTransferList::get()) const;

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
              const property::DatasetTransferList &dtpl = property::DatasetTransferList::get()) const;

    //!
    //! \brief get the dataset external filters for the instance
    //!
    //! Returns an instance of the dataset external filters for the
    //! dataset.
    //!
    //! \throws std::runtime_error in case of a failure
    //! \return instance of ExternalFilters
    //!
    filter::ExternalFilters filters() const;

  private:
    datatype::Datatype file_type_;
    datatype::Class file_type_class;
    dataspace::DataspacePool space_pool;
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
      if(file_space.selection.type() != dataspace::SelectionType::All)
      {
        buffer.resize(file_space.selection.size());
      }
      else
      {
        buffer.resize(signed2unsigned<size_t>(file_space.size()));
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
      using size_type = typename std::vector<T>::size_type;

      typename Trait::BufferType buffer(static_cast<size_type>(mem_space.size()));


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

#ifdef __clang__
#pragma clang diagnostic pop
#endif

template<typename T>
void Dataset::write(const T &data,const datatype::Datatype &mem_type,
                                  const dataspace::Dataspace &mem_space,
                                  const dataspace::Dataspace &file_space,
                                  const property::DatasetTransferList &dtpl) const
{
  if(file_type_class == datatype::Class::VarLength)
  {
    write_variable_length_data(data,mem_type,mem_space,file_type_,file_space,dtpl);
  }
  else if(file_type_class == datatype::Class::String)
  {
    datatype::String string_type(file_type_);
    if(string_type.is_variable_length())
    {
      write_variable_length_string_data(data,mem_type,mem_space,file_type_,file_space,dtpl);
    }
    else
    {
      write_fixed_length_string_data(data,mem_type,mem_space,file_type_,file_space,dtpl);
    }
  }
  else
  {
    write_contiguous_data(data,mem_type,mem_space,file_type_,file_space,dtpl);
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
                          std::vector<unsigned long long> offset,
                          std::uint32_t filter_mask,
                          const property::DatasetTransferList &dtpl)
{
  hdf5::datatype::DatatypeHolder mem_type_holder;
  hdf5::dataspace::DataspaceHolder mem_space_holder(space_pool);
  write_chunk(data, mem_type_holder.get(data), mem_space_holder.get(data), offset, filter_mask, dtpl);
}

template<typename T>
void Dataset::write_chunk(const T &data,
                          std::vector<unsigned long long> offset,
                          std::uint32_t filter_mask,
                          const property::DatasetTransferList &dtpl) const
{
  hdf5::datatype::DatatypeHolder mem_type_holder;
  hdf5::dataspace::DataspaceHolder mem_space_holder;
  write_chunk(data, mem_type_holder.get(data), mem_space_holder.get(data), offset, filter_mask, dtpl);
}

template<typename T>
void Dataset::write_chunk(const T &data,
			  const datatype::Datatype &mem_type,
			  const dataspace::Dataspace &mem_space,
			  std::vector<unsigned long long> & offset,
                          std::uint32_t filter_mask,
                          const property::DatasetTransferList &dtpl) const
{
  size_t databytesize = signed2unsigned<unsigned long long>(mem_space.size()) * mem_type.size();

  if(mem_type.get_class() == datatype::Class::Integer)
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
			 std::vector<unsigned long long> offset,
			 const property::DatasetTransferList &dtpl) const
{
  hdf5::datatype::DatatypeHolder mem_type_holder;
  return read_chunk(data, mem_type_holder.get(data), offset, dtpl);
}

template<typename T>
std::uint32_t Dataset::read_chunk(T &data,
				  const datatype::Datatype &mem_type,
				  std::vector<unsigned long long> & offset,
				  const property::DatasetTransferList &dtpl) const
{
  std::uint32_t filter_mask;
  if(mem_type.get_class() == datatype::Class::Integer)
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
void Dataset::write(const T &data,const property::DatasetTransferList &dtpl)
{
  hdf5::datatype::DatatypeHolder mem_type_holder;
  hdf5::dataspace::DataspaceHolder mem_space_holder(space_pool);
  write_reshape(data, mem_type_holder.get(data), mem_space_holder.get(data), dtpl);
}

template<typename T>
void Dataset::write(const T &data,const property::DatasetTransferList &dtpl) const
{
  hdf5::datatype::DatatypeHolder mem_type_holder;
  hdf5::dataspace::DataspaceHolder mem_space_holder;
  write_reshape(data, mem_type_holder.get(data), mem_space_holder.get(data), dtpl);
}

template<typename T>
void Dataset::write_reshape(const T &data,
			    const datatype::Datatype &mem_type,
			    const dataspace::Dataspace &mem_space,
			    const property::DatasetTransferList &dtpl) const
{
  auto file_space  = dataspace();
  file_space.selection.all();

  if (file_space.size() == mem_space.size() &&
      mem_space.type() == dataspace::Type::Simple &&
      file_space.type() == dataspace::Type::Simple){
    const dataspace::Simple & mem_simple_space = dataspace::Simple(mem_space);
    const dataspace::Simple & file_simple_space = dataspace::Simple(file_space);
    if(file_simple_space.rank() > 1 && mem_simple_space.rank() == 1){
      return write(data,mem_type,file_space,file_space,dtpl);
    }
  }
  write(data,mem_type,mem_space,file_space,dtpl);
}


template<typename T>
void Dataset::read(T &data,const datatype::Datatype &mem_type,
                           const dataspace::Dataspace &mem_space,
                           const dataspace::Dataspace &file_space,
                           const property::DatasetTransferList &dtpl) const
{
  if(file_type_class == datatype::Class::VarLength)
  {
    read_variable_length_data(data,mem_type,mem_space,file_type_,file_space,dtpl);
  }
  else if(file_type_class == datatype::Class::String)
  {
    datatype::String string_type(file_type_);
    if(string_type.is_variable_length())
    {
      read_variable_length_string_data(data,mem_type,mem_space,file_type_,file_space,dtpl);
    }
    else
    {
      read_fixed_length_string_data(data,mem_type,mem_space,file_type_,file_space,dtpl);
    }
  }
  else
  {
    read_contiguous_data(data,mem_type,mem_space,file_type_,file_space,dtpl);
  }

}

template<typename T>
void Dataset::read(T &data,const dataspace::Selection &selection,
                   const property::DatasetTransferList &dtpl)
{
  hdf5::datatype::DatatypeHolder mem_type_holder;
  hdf5::dataspace::DataspaceHolder mem_space_holder(space_pool);
  read_reshape(data, mem_type_holder.get(data), mem_space_holder.get(data), selection, dtpl);
}

template<typename T>
void Dataset::read(T &data,const dataspace::Selection &selection,
                   const property::DatasetTransferList &dtpl) const
{
  hdf5::datatype::DatatypeHolder mem_type_holder;
  hdf5::dataspace::DataspaceHolder mem_space_holder;
  read_reshape(data, mem_type_holder.get(data), mem_space_holder.get(data), selection, dtpl);
}

template<typename T>
void Dataset::read_reshape(T &data,
			   const datatype::Datatype &mem_type,
			   const dataspace::Dataspace &mem_space,
			   const dataspace::Selection &selection,
			   const property::DatasetTransferList &dtpl) const
{
  dataspace::Dataspace file_space = dataspace();
  file_space.selection(dataspace::SelectionOperation::Set,selection);
  if (selection.type() != dataspace::SelectionType::Hyperslab)
    return read(data,mem_type,mem_space,file_space,dtpl);
  try{
    const dataspace::Hyperslab & hyper = dynamic_cast<const dataspace::Hyperslab &>(selection);
    if(hyper.rank() > 1) {
      dataspace::Simple selected_space(hyper.dimensions());
      if (selected_space.size() == mem_space.size()) {
	// reads to the reshaped memory data buffer
	return read(data,mem_type,selected_space,file_space,dtpl);
      }
    }
  }
  catch(const std::bad_cast&) {  }
  read(data,mem_type,mem_space,file_space,dtpl);
}

template<typename T>
void Dataset::read(T &data,
                   const datatype::Datatype &memory_type,
                   const dataspace::Dataspace &memory_space,
                   const dataspace::Selection &file_selection,
                   const property::DatasetTransferList &dtpl) const
{
  dataspace::Dataspace file_space = dataspace();
  file_space.selection(dataspace::SelectionOperation::Set,file_selection);
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
                    const property::DatasetTransferList &dtpl)
{
  hdf5::datatype::DatatypeHolder mem_type_holder;
  hdf5::dataspace::DataspaceHolder mem_space_holder(space_pool);
  write_reshape(data, mem_type_holder.get(data), mem_space_holder.get(data), selection, dtpl);
}

template<typename T>
void Dataset::write(const T &data,const dataspace::Selection &selection,
                    const property::DatasetTransferList &dtpl) const
{
  hdf5::datatype::DatatypeHolder mem_type_holder;
  hdf5::dataspace::DataspaceHolder mem_space_holder;
  write_reshape(data, mem_type_holder.get(data), mem_space_holder.get(data), selection, dtpl);
}

template<typename T>
void Dataset::write_reshape(const T &data,
			    const datatype::Datatype &mem_type,
			    const dataspace::Dataspace &mem_space,
			    const dataspace::Selection &selection,
			    const property::DatasetTransferList &dtpl) const
{
  dataspace::Dataspace file_space = dataspace();
  file_space.selection(dataspace::SelectionOperation::Set,selection);
  if (mem_space.type() != dataspace::Type::Simple
      || selection.type() != dataspace::SelectionType::Hyperslab)
    return write(data,mem_type,mem_space,file_space,dtpl);
  try{
    const dataspace::Hyperslab & hyper = dynamic_cast<const dataspace::Hyperslab &>(selection);
    if(hyper.rank() > 1) {
      const dataspace::Simple & mem_simple_space = dataspace::Simple(mem_space);
      dataspace::Simple selected_space(hyper.dimensions());
      if(selected_space.rank() > 1 &&
	 mem_simple_space.rank() == 1 &&
	 selected_space.size() == mem_space.size()) {
	// writes from the reshaped memory data buffer
	return write(data,mem_type,selected_space,file_space,dtpl);
      }
    }
  }
  catch(const std::bad_cast&) { }
  write(data,mem_type,mem_space,file_space,dtpl);
}


template<typename T>
void Dataset::read(T &data,const property::DatasetTransferList &dtpl)
{
  hdf5::dataspace::DataspaceHolder mem_space_holder(space_pool);
  if(file_type_class == datatype::Class::String){
    // in hdf5 1.12.1 UFT8 data cannot be read to an ASCII buffer
    read_reshape(data, file_type_, mem_space_holder.get(data), dtpl);
  }
  else {
    hdf5::datatype::DatatypeHolder mem_type_holder;
    read_reshape(data, mem_type_holder.get(data), mem_space_holder.get(data), dtpl);
  }
}

template<typename T>
void Dataset::read(T &data,const property::DatasetTransferList &dtpl) const
{
  hdf5::datatype::DatatypeHolder mem_type_holder;
  hdf5::dataspace::DataspaceHolder mem_space_holder;
  read_reshape(data, mem_type_holder.get(data), mem_space_holder.get(data), dtpl);
}


template<typename T>
void Dataset::read_reshape(T &data,
			   const datatype::Datatype &mem_type,
			   const dataspace::Dataspace &mem_space,
			   const property::DatasetTransferList &dtpl) const
{
  auto file_space = dataspace();
  file_space.selection.all();

  if (file_space.size() == mem_space.size()){
    read(data,mem_type,file_space,file_space,dtpl);
  }
  else{
    read(data,mem_type,mem_space,file_space,dtpl);
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
