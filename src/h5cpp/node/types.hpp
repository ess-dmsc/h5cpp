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
// Created on: Sep 8, 2017
//
#pragma once

#include <iostream>
#include <h5cpp/core/hdf5_capi.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace node {

/**
 * @brief enumeration for node type
 */
enum class NodeType : std::underlying_type<H5O_type_t>::type
{
  Unknown = H5O_TYPE_UNKNOWN,
  Group   = H5O_TYPE_GROUP,
  Dataset = H5O_TYPE_DATASET,
  Datatype = H5O_TYPE_NAMED_DATATYPE
};

/**
 * @brief output stream operator for the NodeType enumeration
 * 
 * This operator writes a text representation of the node type to the output
 * stream.
 * 
 * @param stream reference to the output stream
 * @param type the actual type to write to the stream
 * @return modified output stream
 */
DLL_EXPORT std::ostream &operator<<(std::ostream &stream,const NodeType &type);

/**
 * @brief alias type to ensure compatibility with existing code
 * 
 * This alias ensures, that existing code still using the old Type enumeration
 * type is still working. Since NodeType and Type are equivalent from a 
 * structural point of view this should be no issue.
 */
using Type = NodeType;

/**
 * @brief link type enumeration
 * 
 * Enumeration type to distinguish the various link types in HDF5.
 */
enum class LinkType : std::underlying_type<H5L_type_t>::type
{
  Hard = H5L_TYPE_HARD,
  Soft = H5L_TYPE_SOFT,
  External = H5L_TYPE_EXTERNAL,
  Error = H5L_TYPE_ERROR
};

/**
 * @brief output stream operator for the link type enumeration
 * 
 * This operator writes a textual representation of the link type to the 
 * output stream.
 * 
 * @param stream refernce to the output stream
 * @param type reference to the link type
 * @return modified output stream
 */
DLL_EXPORT std::ostream &operator<<(std::ostream &stream,const LinkType &type);

} // namespace node
} // namespace hdf5
