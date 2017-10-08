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

    void extent(const Dimensions &dims) const;

    //!
    //! \brief write entire dataset
    //!
    template<typename T>
    void write(const T &data,const property::DatasetTransferList &dtpl =
                                   property::DatasetTransferList()) const
    {
      auto memory_space = hdf5::dataspace::create(data);
      auto memory_type  = hdf5::datatype::create(data);

      if(H5Dwrite(static_cast<hid_t>(*this),
                  static_cast<hid_t>(memory_type),
                  static_cast<hid_t>(memory_space),
                  H5S_ALL,
                  static_cast<hid_t>(dtpl),
                  dataspace::cptr(data))<0)
      {
        std::stringstream ss;
        ss<<"Failure to write data to dataset ["<<link().path()<<"]!";
        throw std::runtime_error(ss.str());
      }
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

      if(H5Dread(static_cast<hid_t>(*this),
                  static_cast<hid_t>(memory_type),
                  static_cast<hid_t>(memory_space),
                  H5S_ALL,
                  static_cast<hid_t>(dtpl),
                  dataspace::ptr(data))<0)
      {
        std::stringstream ss;
        ss<<"Failure to write data to dataset ["<<link().path()<<"]!";
        throw std::runtime_error(ss.str());
      }

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

//ds.push_back(data);
//
//std::vector<double> data(4);
//ds.write(Points{{2},{3},{10},{56}},data);
//
//ds.write(Hyperslab{{3},{6}},data)



} // namespace node
} // namespace hdf5
