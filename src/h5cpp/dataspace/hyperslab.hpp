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
#include <h5cpp/core/types.hpp>
#include <h5cpp/core/windows.hpp>
#include <memory>
#include <list>
#include <sstream>

namespace hdf5 {
namespace dataspace {

//!
//! \brief hyperslab selection class
//!
//! Hyperslabs represent complex multidimensional selections within an
//! HDF5 dataset. The number of dimensions for every hyperslab  is determined
//! during construction and cannot be altered once it has been fixed.
//!
//! \b Todo:
//!
//! - we may have to add a function to check if all the Dimension instances
//!     have the same size. However, this might be an expensive procedure and
//!     we should take performance considerations into account here.
//!
class DLL_EXPORT Hyperslab : public Selection {
 public:
  //!
  //! \brief default constructor
  //!
  //! The default constructor is present to allow Hyperslabs in STL
  //! containers. It must be noted that any attempt to change an internal value
  //! will result in a std::runtime_error exception.
  //! The rank of a default constructed Hyperslab would be 0. As a
  //! Hyperslab of rank 0 would not make any sense one could use this
  //! to identify a default constructed Hyperslab.
  //!
  //! \post all internal buffers remain unallocated
  //!
  Hyperslab();

  //!
  //! \brief destructor
  //!
  ~Hyperslab() override;

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
  //! This constructor exposes the full capabilities of a hyperslab. All
  //! parameters can be adjusted.
  //!
  //! \param offset the offset from which to start the selection
  //! \param block the size of a single block in the selection
  //! \param count the number of blocks along each dimensions
  //! \param stride the stride along each dimension between the blocks
  //!
  Hyperslab(const Dimensions &offset,
            const Dimensions &block,
            const Dimensions &count,
            const Dimensions &stride);

  //!
  //! \brief constructor
  //!
  //! Construct a hyperslab which constists of a single block starting
  //! at a particular offset.
  //!
  //! \param offset the start offset of the block
  //! \param block the size of the single block
  //!
  Hyperslab(const Dimensions &offset,
            const Dimensions &block);

  //!
  //! \brief constructor
  //!
  //! Construct a hyperslab which consists of \c count blocks of size 1
  //! along each dimension separated by \c stride elements.
  //!
  //! \param offset starting offset of the selection
  //! \param count number of blocks along each dimensions
  //! \param stride the stride between the blocks along each dimension
  //1
  Hyperslab(const Dimensions &offset,
            const Dimensions &count,
            const Dimensions &stride);

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
  void offset(size_t index, size_t value);

  //!
  //! \brief set all start values
  //!
  //! Set the start values for all dimensions of the hyperslab. If the size of
  //! \c values exceeds the rank of the hyperslab an exception will be thrown.
  //!
  //! \throws std::runtime_error in case of a failure
  //! \param values new start values for the hyperslab
  //!
  void offset(const Dimensions &values);

  //!
  //! \brief get start values
  //! \throws std::runtime_error if the Hyperslab is default constructed
  //! \return const reference to the start values of the hyperslab
  //!
  const Dimensions &offset() const;

  //!
  //! \brief set stride value for an individual dimension
  //!
  //! \throws std::runtime_error in case of a failure
  //! \param index dimension index for which to set the stride
  //! \param value new stride value
  //!
  void stride(size_t index, size_t value);

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

  //!
  //! \brief set count value for a particular dimension
  //!
  //! \throws std::runtime_error in case of a failure
  //! \param index dimension index
  //! \param value new count value for this dimension
  //!
  void count(size_t index, size_t value);

  //!
  //! \brief set all count values
  //! \throws std::runtime_error in case of a failure
  //! \param values reference to the new count values
  //!
  void count(const Dimensions &values);

  //!
  //! \brief get count values
  //!
  //! Return a const reference to the count values of the Hypeslab. The
  //! values cannot be changed via this reference.
  //!
  //! \throws std::runtime_error in case of a failure
  //! \return reference to count values
  //!
  const Dimensions &count() const;

  //!
  //! \brief set block size for dimension
  //!
  //! \throws std::runtime_error in case of a failure
  //! \param index dimension index
  //! \param value the new block size for this dimension
  //1
  void block(size_t index, size_t value);

  //!
  //! \brief set all block values
  //!
  //! Set all block values for the hyperslab selection.
  //! \throws std::runtime_error in case of a failure
  //! \param values reference to the new block values
  //!
  void block(const Dimensions &values);

  //!
  //! \brief get block values
  //!
  //! Get a const reference to the block values of the hyperslab.
  //! \throws std::runtime_error in case of a failure
  //! \return const reference to the block values
  //!
  const Dimensions &block() const;

  virtual void apply(const Dataspace &space,
                     SelectionOperation ops) const override;

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

 private:
  inline void check_dimension_index(size_t index, const std::string &what) const {
    if (index >= rank()) {
      std::stringstream ss;
      ss << "Cannot set " << what << " value at dimension " << index << " for a Hyperslab"
         << " of rank " << rank() << "!";
      throw std::runtime_error(ss.str());
    }
  }

  inline void check_container_size(const Dimensions &container, const std::string &what) const {
    if (container.size() != rank()) {
      std::stringstream ss;
      ss << "Cannot assign " << container.size() << " " << what << " values to a Hyperslab"
         << " of rank " << rank() << "!";
      throw std::runtime_error(ss.str());
    }
  }

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

DLL_EXPORT Dataspace operator||(const Dataspace &space, const Hyperslab &selection);

DLL_EXPORT SelectionList operator|(const Hyperslab &a, const Hyperslab &b);

DLL_EXPORT SelectionList &operator|(SelectionList &selections, const Hyperslab &b);

} // namespace dataspace
} // namespace hdf5
