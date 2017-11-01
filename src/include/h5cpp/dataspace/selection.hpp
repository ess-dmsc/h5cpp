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
// Created on: Aug 25, 2017
//
#pragma once

#include "type.hpp"
#include "dataspace.hpp"
#include "../types.hpp"
#include "../windows.hpp"

namespace hdf5 {
namespace dataspace {

//!
//! \brief selection base class
//!
class DLL_EXPORT Selection
{
  public:
    //!
    //! \brief default constructor
    //!
    //! Use the compiler provided default implementation.
    Selection() = default;

    //!
    //! \brief copy constructor
    //!
    //! Use the compiler provided default implementation.
    //!
    Selection(const Selection &) = default;

    //!
    //! \brief destructor
    //!
    //! The destructor has to be virtual to inherit from this class.
    //!
    virtual ~Selection();

    //!
    //! \brief apply a selection onto a dataspace
    //!
    //! The current selection will be applied to dataspace \c space using the
    //! operator determined by \c ops.
    //!
    //! \throws std::runtime_error in case of a failure
    //!
    //! \param space reference to the dataspace onto which to apply the
    //!              selection
    //! \param ops operator for the selection
    virtual void apply(const Dataspace &space,
                       SelectionOperation ops) const = 0;
};

//!
//! \brief hyperslab selection class
//!
//! Hyperslabs represent complex multidimensional selections within an
//! HDF5 dataset. The number of dimensions for every hyperslab  is determined
//! during construction and cannot be altered once it has been fixed.
//!
class DLL_EXPORT Hyperslab : public Selection
{
  public:
    //!
    //! \brief default constructor
    //!
    //! The default constructor is present to allow Hyperslabs in STL
    //! containers. It must be noted that any attempt to an internal value
    //! will result in a std::runtime_error exception.
    //! The rank of a default constructed Hyperslab would be 0. As a
    //! Hyperslab of rank 0 would not make any sense one could use this
    //! to identify a default constructed Hyperslab.
    //!
    //! \post all internall buffers remain unallocated
    //!
    Hyperslab();

    //!
    //! \brief destructor
    //!
    ~Hyperslab();

    //!
    //! \brief copy constructor
    //!
    //! Use compiler generated default implementation here
    //!
    Hyperslab(const Hyperslab &) = default;

    //!
    //! \brief constructor
    //!
    //! Construct a Hyperslab selection of a given rank.
    //!
    //! \param rank the number of dimensions
    //!
    //! \post all start values are set to 0
    //! \post all stride values are set to 1
    //! \post all count values are set to 0
    //! \post all block values are set to 0
    //!
    Hyperslab(size_t rank);

    //!
    //! \brief constructor
    //!
    Hyperslab(const Dimensions &start,
              const Dimensions &stride,
              const Dimensions &count,
              const Dimensions &block);

    //!
    //! \brief get rank
    //! \return number of dimensions in the selection
    //!
    size_t rank() const noexcept;

    //!
    //! \brief set start value for a dimension
    //!
    //! Set the start value of the hyperslab for a particular dimension determined
    //! by \c index to \c value. This method throws an exception if the dimension
    //! \c index exceeds the rank of the hyperslab.
    //!
    //! \throws std::runtime_error in case of a failure
    //! \param index dimension index
    //! \param value new start value
    //!
    void start(size_t index,size_t value);

    //!
    //! \brief set all start values
    //!
    //! Set the start values for all dimensions of the hyperslab. If the size of
    //! \c values exceeds the rank of the hyperslab an exception will be thrown.
    //!
    //! \throws std::runtime_error in case of a failure
    //! \param values new start values for the hyperslab
    //!
    void start(const Dimensions &values);

    //!
    //! \brief get start values
    //! \throws std::runtime_error if the Hyperslab is default constructed
    //! \return const reference to the start values of the hyperslab
    //!
    const Dimensions &start() const;


    //!
    //! \brief set stride value for an individual dimension
    //!
    //! \throws std::runtime_error in case of a failure
    //! \param index dimension index for which to set the stride
    //! \param value new stride value
    //!
    void stride(size_t index,size_t value);

    //!
    //! \brief set all stride values for the Hyperslab
    //!
    //! \throws std::runtime_error in case of a failure
    //! \param values new stride values for the Hyperslab
    //!
    void stride(const Dimensions &values);

    //!
    //! \brief get stride values for the Hyperslab
    //! \throws std::runtime_error in case of a failure
    //! \return const reference to the stride values
    //!
    const Dimensions &stride() const;

    void count(size_t index,size_t value);
    void count(const Dimensions &values);
    const Dimensions &count() const;

    void block(size_t index,size_t value);
    void block(const Dimensions &values);
    const Dimensions &block() const;

    virtual void apply(const Dataspace &space,
                       SelectionOperation ops) const;

  private:
    void check_dimension_index(size_t index,const std::string &what) const;
    void check_container_size(const Dimensions &container,const std::string &what) const;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
    Dimensions start_;
    Dimensions stride_;
    Dimensions count_;
    Dimensions block_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};


class DLL_EXPORT Points : public Selection
{
  public:
    Points();
    Points(size_t rank);
    ~Points();

    virtual void apply(const Dataspace &space,
                       SelectionOperation ops) const;

};

} // namespace dataspace
} // namespace hdf5
