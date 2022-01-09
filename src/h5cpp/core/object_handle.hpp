//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5pp.
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
// Created on: Aug 07, 2017
//

#pragma once

#include <h5cpp/core/hdf5_capi.hpp>
#include <iostream>

#include <h5cpp/core/windows.hpp>

namespace hdf5
{

//!
//! \brief Wrapper for hid_t object identifiers
//!
//! Objects in HDf5 are referenced using an handle of type hid_t. Though
//! the name of the type and the API reference of the HDF5 C-API suggest
//! this value is an ID it should be rather considered a handle which is
//! used to reference a particular object.
//!
//!
//! The aim of this class is to encapsulate an HDF5 handler and control
//! the reference counting for that handler for copy and move construction
//! and assignment.
//!
//! * copy construction and assignment increments the reference count of an
//!   handler
//! * move construction and assignment leaves the reference count unchanged
//! * closing an object decrements the reference count
//! * in addition, the reference count is decreased if the destructor of
//!   an instance of ObjectHandle is called
//!
//! From that point of view ObjectHandle could also be considered as a
//! guard object for a handle which ensures that an object gets closed
//! once it looses scope.
//!
//! The class also comprises a set of static member functions which provide
//! operations on the handler.
//!
//!
class DLL_EXPORT ObjectHandle
{
  public:
    //!
    //! @brief type of the object handle
    //!
    enum class Type
    {
      Uninitialized,
      BadObject,
      File,
      Group,
      Datatype,
      Dataspace,
      Dataset,
      Attribute,
      PropertyList,
      VirtualFileLayer,
      PropertyListClass,
      ErrorClass,
      ErrorMessage,
      ErrorStack
    };

    //!
    //! @brief type of the ward policy
    //!
    enum class Policy
    {
      WithWard = 1,
      WithoutWard= 2
    };
  private:
    hid_t handle_; //!< ID of the object

    //------------------------------------------------------------------------
    //!
    //! \brief increment reference counter
    //!
    //! Increment the reference counter on the current handle if the
    //! handle is valid.
    //!
    //! \throws std::runtime_error if incrementing the reference count fails
    void increment_reference_count() const;

    //------------------------------------------------------------------------
    //!
    //! \brief decrement reference counter
    //!
    //! Decrement the reference counter on the current handle if it
    //! references a valid object.
    //!
    //! \throws std::runtime_error if decrementing the reference count fails
    void decrement_reference_count() const;
  public:
    //================constructors and destructors=====================
    //!
    //! \brief construct from HDF5 ID
    //!
    //! This constructor can be used to construct an instance of
    //! h5object from an HDF5 ID.
    //! h5object takes full control over the constructed object. Thus
    //! the constructor has move semantics and does not allow to use
    //! const & or & to the hid_t argument.
    //! A typical usage example would look like this
    /*!
    \code
    .....
    hdf5::ObjectHandle handle(H5Gopen(fid,"data",hdf5::property::kDefault));
    ...
    \endcode
    */
    //! An exception is thrown if the ID passed is negative.
    //!
    //! \throws std::runtime_error if the passed id is invalid (<0)
    //!
    //! \param id HDF5 object ID.
    //! \param policy with or w/o ward policy.
    //!
    explicit ObjectHandle(hid_t id, Policy policy=Policy::WithWard);

    //-----------------------------------------------------------------
    //!
    //! \brief default constructor
    //!
    //! The default constructor does not throw. However, after default
    //! construction the object will be in an invalid state.
    //!
    explicit ObjectHandle() noexcept;

    //-----------------------------------------------------------------
    //!
    //! \brief copy constructor
    //!
    //! Copies the ID of the o and increments its reference counter if
    //! the object is valid.
    //!
    //! \throws std::runtime_error in case of errors
    //!
    //! \param o object which to cpy
    ObjectHandle(const ObjectHandle &o);

    //-----------------------------------------------------------------
    //!
    //! \brief move constructor
    //!
    //! Copies the ID of the original object and sets the ID of the
    //! original object to 0. As this is a move process the reference
    //! counter of the ID will not be incremented.
    //!
    //! \param o object to move
    ObjectHandle(ObjectHandle &&o) noexcept;

    //-----------------------------------------------------------------
    //!
    //! \brief destructor
    //!
    ~ObjectHandle() noexcept;

    //================assignment operators=============================
    //!
    //! \brief copy assignment operator
    //!
    //! Just like for the copy constructor the reference counter for
    //! the original ID is incremented.
    //!
    //! \throws std::runtime_error in case of errors
    //!
    //! \param o object to assign
    //! \return refence to object
    ObjectHandle &operator=(const ObjectHandle &o);

    //-----------------------------------------------------------------
    //!
    //! \brief move assignment operator
    //!
    //! Like the move constructor this operator has no influence on the
    //! value of the IDs reference counter.
    //!
    //! \throws std::runtime_error in case of errors
    //!
    //! \param o object form which to move data
    //! \return reference to object
    ObjectHandle &operator=(ObjectHandle &&o) noexcept;


    //!
    //! \brief conversion operator
    //!
    explicit operator hid_t() const
    {
      return handle_;
    }

    //=====================static member functions ====================
    //!
    //! \brief close the object
    //!
    //! This will decrement the reference counter of the ID held by this
    //! object or close it if the reference counter approaches 0.
    //! The close method runs an object introspection by means of the
    //! HDF5 library and calls the appropriate close function.
    //!
    //! \throws std::runtime_error if the close operation fails
    void close();

    //------------------------------------------------------------------
    //!
    //! \brief check validity
    //!
    //! This method returns true of the object refers to a valid HDF5
    //! object. In other words this means that the object is valid and
    //! available. For a file object this would mean that the file is
    //! open.
    //!
    //! \throws std::runtime_error if object status retrieval fails
    //! \returns true if valid HDF5 object
    bool is_valid() const;

    //------------------------------------------------------------------------
    //!
    //! \brief get nexus object type
    //!
    //! \throws std::runtime_error if the type is unknown
    //! \return object type
    ObjectHandle::Type get_type() const;



    //------------------------------------------------------------------------
    //!
    //! \brief return reference counter value
    //!
    //! \throws std::runtime_error if retrieval of the reference count fails
    //!
    //! \return the actual reference count
    int get_reference_count() const;
};


//!
//! \brief equality operator
//!
//! Two instances of ObjectHandle are considered equal when their internal
//! representation have equal value. This is not a sufficient criteria for
//! object equality!
//!
DLL_EXPORT bool operator==(const ObjectHandle &lhs,const ObjectHandle &rhs);

//!
//! \brief not equal to operator
//!
//! Simply the inverse of the == operator.
//!
DLL_EXPORT bool operator!=(const ObjectHandle &lhs,const ObjectHandle &rhs);

//!
//! \brief output operator for Types
//!
DLL_EXPORT std::ostream &operator<<(std::ostream &stream,
                                    const ObjectHandle::Type &type);

} // namespace hdf5
