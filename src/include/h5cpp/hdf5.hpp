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

#include "iterator_config.hpp"
#include "iterator.hpp"
#include "object_handle.hpp"
#include "object_id.hpp"
#include "path.hpp"
#include "types.hpp"
#include "windows.hpp"

#include "attribute/attribute_iterator.hpp"
#include "attribute/attribute_manager.hpp"
#include "attribute/attribute.hpp"

#include "datatype/compound.hpp"
#include "datatype/datatype.hpp"
#include "datatype/factory.hpp"
#include "datatype/float.hpp"
#include "datatype/integer.hpp"
#include "datatype/type_trait.hpp"
#include "datatype/types.hpp"
#include "datatype/string.hpp"
#include "datatype/array.hpp"

#include "dataspace/dataspace.hpp"
#include "dataspace/scalar.hpp"
#include "dataspace/selection_manager.hpp"
#include "dataspace/selection.hpp"
#include "dataspace/simple.hpp"
#include "dataspace/type.hpp"
#include "dataspace/type_trait.hpp"

#include "file/file.hpp"
#include "file/functions.hpp"
#include "file/types.hpp"

#include "node/dataset.hpp"
#include "node/group_view.hpp"
#include "node/group.hpp"
#include "node/link_view.hpp"
#include "node/link.hpp"
#include "node/node.hpp"
#include "node/node_iterator.hpp"
#include "node/link_iterator.hpp"
#include "node/node_view.hpp"
#include "node/functions.hpp"
#include "node/types.hpp"

#include "property/attribute_creation_list.hpp"
#include "property/class.hpp"
#include "property/creation_order.hpp"
#include "property/dataset_access_list.hpp"
#include "property/dataset_creation_list.hpp"
#include "property/dataset_transfer_list.hpp"
#include "property/datatype_access_list.hpp"
#include "property/file_access_list.hpp"
#include "property/file_creation_list.hpp"
#include "property/file_mount_list.hpp"
#include "property/group_access_list.hpp"
#include "property/group_creation_list.hpp"
#include "property/link_access_list.hpp"
#include "property/link_creation_list.hpp"
#include "property/list.hpp"
#include "property/object_creation_list.hpp"
#include "property/string_creation_list.hpp"
#include "property/type_creation_list.hpp"
#include "property/object_copy_list.hpp"

#include "filter/filter.hpp"
#include "filter/types.hpp"
#include "filter/deflate.hpp"
#include "filter/fletcher32.hpp"
#include "filter/shuffle.hpp"
