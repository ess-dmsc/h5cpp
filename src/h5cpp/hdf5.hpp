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
// Created on: Oct 7, 2017
//
#pragma once

#include <h5cpp/core/hdf5_capi.hpp>

#include <h5cpp/core/iterator_config.hpp>
#include <h5cpp/core/iterator.hpp>
#include <h5cpp/core/object_handle.hpp>
#include <h5cpp/core/object_id.hpp>
#include <h5cpp/core/path.hpp>
#include <h5cpp/core/types.hpp>
#include <h5cpp/core/version.hpp>
#include <h5cpp/core/windows.hpp>
#include <h5cpp/core/variable_length_string.hpp>
#include <h5cpp/core/fixed_length_string.hpp>

#include <h5cpp/attribute/attribute_iterator.hpp>
#include <h5cpp/attribute/attribute_manager.hpp>
#include <h5cpp/attribute/attribute.hpp>

#include <h5cpp/error/error.hpp>

#include <h5cpp/datatype/compound.hpp>
#include <h5cpp/datatype/datatype.hpp>
#include <h5cpp/datatype/factory.hpp>
#include <h5cpp/datatype/float.hpp>
#include <h5cpp/datatype/integer.hpp>
#include <h5cpp/datatype/type_trait.hpp>
#include <h5cpp/datatype/types.hpp>
#include <h5cpp/datatype/string.hpp>
#include <h5cpp/datatype/array.hpp>
#include <h5cpp/datatype/enum.hpp>

#include <h5cpp/dataspace/dataspace.hpp>
#include <h5cpp/dataspace/hyperslab.hpp>
#include <h5cpp/dataspace/points.hpp>
#include <h5cpp/dataspace/scalar.hpp>
#include <h5cpp/dataspace/selection_manager.hpp>
#include <h5cpp/dataspace/selection.hpp>
#include <h5cpp/dataspace/simple.hpp>
#include <h5cpp/dataspace/type.hpp>
#include <h5cpp/dataspace/type_trait.hpp>
#include <h5cpp/dataspace/view.hpp>
#include <h5cpp/dataspace/pool.hpp>

#include <h5cpp/file/file.hpp>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/file/types.hpp>
#include <h5cpp/file/driver.hpp>
#include <h5cpp/file/direct_driver.hpp>
#include <h5cpp/file/memory_driver.hpp>
#include <h5cpp/file/mpi_driver.hpp>
#include <h5cpp/file/posix_driver.hpp>

#include <h5cpp/filter/filter.hpp>
#include <h5cpp/filter/types.hpp>
#include <h5cpp/filter/deflate.hpp>
#include <h5cpp/filter/fletcher32.hpp>
#include <h5cpp/filter/nbit.hpp>
#include <h5cpp/filter/scaleoffset.hpp>
#include <h5cpp/filter/shuffle.hpp>
#include <h5cpp/filter/szip.hpp>
#include <h5cpp/filter/external_filter.hpp>

#include <h5cpp/node/dataset.hpp>
#include <h5cpp/node/group_view.hpp>
#include <h5cpp/node/group.hpp>
#include <h5cpp/node/link_view.hpp>
#include <h5cpp/node/link.hpp>
#include <h5cpp/node/node.hpp>
#include <h5cpp/node/node_iterator.hpp>
#include <h5cpp/node/link_iterator.hpp>
#include <h5cpp/node/node_view.hpp>
#include <h5cpp/node/functions.hpp>
#include <h5cpp/node/types.hpp>
#include <h5cpp/node/chunked_dataset.hpp>
#include <h5cpp/node/recursive_node_iterator.hpp>
#include <h5cpp/node/recursive_link_iterator.hpp>
#if (defined(_DOXYGEN_) || H5_VERSION_GE(1,10,0))
#include <h5cpp/node/virtual_dataset.hpp>
#endif

#include <h5cpp/property/attribute_creation.hpp>
#include <h5cpp/property/property_class.hpp>
#include <h5cpp/property/creation_order.hpp>
#include <h5cpp/property/dataset_access.hpp>
#include <h5cpp/property/dataset_creation.hpp>
#include <h5cpp/property/dataset_transfer.hpp>
#include <h5cpp/property/datatype_access.hpp>
#include <h5cpp/property/file_access.hpp>
#include <h5cpp/property/file_creation.hpp>
#include <h5cpp/property/file_mount.hpp>
#include <h5cpp/property/group_access.hpp>
#include <h5cpp/property/group_creation.hpp>
#include <h5cpp/property/link_access.hpp>
#include <h5cpp/property/link_creation.hpp>
#include <h5cpp/property/property_list.hpp>
#include <h5cpp/property/object_creation.hpp>
#include <h5cpp/property/string_creation.hpp>
#include <h5cpp/property/type_creation.hpp>
#include <h5cpp/property/object_copy.hpp>
#if (defined(_DOXYGEN_) || H5_VERSION_GE(1,10,0))
#include <h5cpp/property/virtual_data_map.hpp>
#endif

#include <h5cpp/utilities/array_adapter.hpp>
