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

namespace hdf5 {
namespace node {

class Selection;

class Dataset : public Node
{
  public:

    Dataspace dataspace() const;
    Datatype dataspace() const;

    //!
    //! \brief write entire dataset
    //!
    template<typename T>
    void write(const T &data) const
    {
      auto memory_space = hdf5::dataspace::create(data);
      auto memory_type  = hdf5::datatype::create(data);

      Dataspace file_space = dataspace();

      if(H5Dwrite(........)<0)
      {

      }
    }

    //!
    //! \brief read entire dataset
    //!
    template<typename T>
    void read(T &data) const;

    //!
    //! \brief
    //!
    template<typename T>
    void write(const Dataspace &filespace,const T &data) const
    {

    }

    template<typename T>
    void write(const Dataspace &filespace,const Dataspace &memspace, const T &data);

    template<typename T>
    void write(const Selection &file_selection,const T &data) const;





};

ds.push_back(data);

std::vector<double> data(4);
ds.write(Points{{2},{3},{10},{56}},data);

ds.write(Hyperslab{{3},{6}},data)



} // namespace node
} // namespace hdf5
