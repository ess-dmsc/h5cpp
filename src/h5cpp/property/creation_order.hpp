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
// Created on: Aug 18, 2017
//

#pragma once

#include <h5cpp/core/hdf5_capi.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace property {

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif
class DLL_EXPORT CreationOrder {
 public:
  //!
  //! \brief default constructor
  //!
  CreationOrder();

  //!
  //! \brief copy constructor
  //!
  //! @param c reference from which to copy
  CreationOrder(const CreationOrder &c) = default;

  //!
  //! \brief constructor
  //!
  //! @param value flags from which to construct the instance
  explicit CreationOrder(unsigned value);

  //!
  //! \brief enable tracked creation order
  //!
  //! @return reference to the modified instance
  //! \sa disable_tracked
  CreationOrder &enable_tracked();

  //!
  //! \brief disable tracked creation order
  //!
  //! @return reference to the modified instance
  //! \sa enable_tracked
  CreationOrder &disable_tracked();

  //!
  //! \brief enable indexed creation order
  //!
  //! This implies also tracked creation order which will be
  //! enabled by this method automatically if it is not.
  //!
  //! @return reference to the modified instance
  //! \sa disable_indexed
  CreationOrder &enable_indexed();

  //!
  //! \brief disable indexed creation order
  //!
  //! This does not automatically disable also tracked creation order.
  //!
  //! @return reference to the modified instance
  //! \sa enable_tracked
  CreationOrder &disable_indexed();

  //!
  //! \brief query if tracked creation order is enabled
  //! @return true if creation order is tracked, false otherwise
  bool tracked() const;

  //!
  //! \brief query if indexed creation order is enabled
  //! @return true if creation order indexed is enabled, false otherwise
  bool indexed() const;

  //!
  //! \brief conversion operator
  //!
  //! Allows the conversion of an instance of this class to an unsigned
  //! integer value which can be used with the HDF5 C-API low level
  //! functions.
  operator unsigned() const {
    unsigned result = 0;
    if (tracked_) result |= H5P_CRT_ORDER_TRACKED;

    if (indexed_) result |= H5P_CRT_ORDER_INDEXED;

    return result;

  }

 private:
  unsigned tracked_:1;
  unsigned indexed_:1;
#ifdef __clang__
  unsigned reserved_:sizeof(unsigned) - 2 __attribute__((unused));
#else
  unsigned reserved_:sizeof(unsigned) - 2;
#endif
};
#ifdef __clang__
#pragma clang diagnostic pop
#endif

}  // namespace property
}  // namespace hdf5
