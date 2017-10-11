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

#include "node.hpp"
#include "../dataspace/dataspace.hpp"
#include "../datatype/datatype.hpp"
#include "../property/dataset_transfer_list.hpp"
#include "../types.hpp"
#include "../windows.hpp"

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
    template<typename T>
    void write(const T &data,const property::DatasetTransferList &dtpl =
                                   property::DatasetTransferList()) const
    {
      auto memory_space = hdf5::dataspace::create(data);
      auto memory_type  = hdf5::datatype::create(data);

      write(data,memory_type,memory_space,dataspace::Dataspace(ObjectHandle(H5S_ALL,ObjectHandle::Policy::WITHOUT_WARD)),dtpl);
    }
//
//    //!
//    //! \brief read entire dataset
//    //!
    template<typename T>
    void read(T &data,const property::DatasetTransferList &dtpl =
                            property::DatasetTransferList()) const
    {
      auto memory_space = hdf5::dataspace::create(data);
      auto memory_type  = hdf5::datatype::create(data);

      read(data,memory_type,memory_space,dataspace::Dataspace(ObjectHandle(H5S_ALL,ObjectHandle::Policy::WITHOUT_WARD)),dtpl);

    }

    template<typename T>
    void read(T &data,const dataspace::Selection &selection,
              const property::DatasetTransferList &dtpl = property::DatasetTransferList()) const
    {
      auto memory_space = hdf5::dataspace::create(data);
      auto memory_type  = hdf5::dataspace::create(data);

      dataspace::Dataspace file_space = dataspace();
      file_space.selection(dataspace::SelectionOperation::SET,selection);

      read(data,memory_type,memory_space,file_space,dtpl);

    }
//
//    //!
//    //! \brief
//    //!
//    template<typename T>
//    void write(const Dataspace &filespace,const T &data) const
//    {
//
//    }
//
//    template<typename T>
//    void write(const Dataspace &filespace,const Dataspace &memspace, const T &data);
//
//    template<typename T>
//    void write(const Selection &file_selection,const T &data) const;

};

template<typename T>
void Dataset::write(const T &data,const datatype::Datatype &mem_type,
                                  const dataspace::Dataspace &mem_space,
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
void Dataset::read(T &data,const datatype::Datatype &mem_type,
                           const dataspace::Dataspace &mem_space,
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



//ds.push_back(data);
//
//std::vector<double> data(4);
//ds.write(Points{{2},{3},{10},{56}},data);
//
//ds.write(Hyperslab{{3},{6}},data)



} // namespace node
} // namespace hdf5
