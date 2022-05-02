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
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 25, 2017
//
#pragma once

#include <h5cpp/dataspace/selection.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5
{
namespace dataspace
{

//!
//! \brief point selection implementation
//!
//!
class DLL_EXPORT Points : public Selection
{
  public:
    //!
    //! \brief default constructor
    //!
    //! We use the compiler provided default implementation.
    Points () = default;

    //!
    //! \brief destructor
    //!
    //! Use the compiler provided default implementation.
    ~Points () override = default;

    //!
    //! \brief constructor
    //!
    //! Create a new point selection or a given rank
    //!
    //! \param rank the number of dimensions of the selection
    //!
    explicit Points (size_t rank);

    //!
    //! \brief constructor
    //!
    //! Create a point selection from a set of selection coordinates. The
    //! number of dimensions of the first coordinates determines the rank
    //! of the selection.
    //!
    //! \param coord_set set of selection coordinates
    //!
    explicit Points (const std::vector<std::vector<hsize_t>>& coord_set);

    //!
    //! \brief get the number of dimensions
    //!
    //! \return number of dimensions of the selection.
    //!
    size_t rank () const;

    //!
    //! \brief get the number of points in the selection
    //!
    //! \return number of points as unsigned integer
    //!
    size_t points () const;

    //!
    //! \brief add a new point to the selection
    //!
    //! \param coords index coordinates of the point
    //! \throws runtime_error in the case of a failure
    //!
    void add (const std::vector<hsize_t>& coords);

    //!
    //! \brief add point set to the selection
    //!
    //! \param coord_set coordinate set
    //! \throws runtime_error in the case of a failure
    //!
    void add_set (const std::vector<std::vector<hsize_t>>& coord_set);

    //!
    //! \brief apply the selection to a dataspace
    //!
    //! \param space reference to the dataspace onto which the selection should
    //!              be applied
    //! \param ops opertion used to apply the selection
    //!
    void apply (const Dataspace &space, SelectionOperation ops) const override;

    //!
    //! \brief get the selection size
    //!
    //! Get the total number of elements adressed by an individual selection
    //!
    //! \throws std::runtime_error in case of a failure
    //!
    //! \return the selection type enumerator
    //!
    virtual size_t size() const override;

    //!
    //! \brief get the selection type
    //!
    //! Get the type of the selection
    //!
    //! \return the selection type enumerator
    //!
    virtual SelectionType type() const override;

    //!
    //! \brief get current dimensions
    //!
    //! Get a number of elements along each dimension a selection spans
    //! this is particularly useful in the case of a Hyperslab 
    //!
    //! \throws std::runtime_error in case of a failure
    //!
    //! \return the selection dimentsions
    //!
    virtual Dimensions dimensions() const override;

  private:
    size_t rank_{ 0 };
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif
    std::vector<hsize_t> coordinates_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
};

} // namespace dataspace
} // namespace hdf5
