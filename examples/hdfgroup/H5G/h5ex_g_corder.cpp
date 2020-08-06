/************************************************************

  This example shows how to track links in a group by
  creation order.  The program creates a series of groups,
  then reads back their names: first in alphabetical order,
  then in creation order.

  This file is intended for use with HDF5 Library version 1.8

 ************************************************************/

#include <h5cpp/hdf5.hpp>

#define FILE       "h5ex_g_corder.h5"

using namespace hdf5;

int main (void)
{
  // Create a new file using the default properties.
  file::File file = file::create (FILE, file::AccessFlags::TRUNCATE);

  // Create group creation property list and enable link creation
  // order tracking.  Attempting to track by creation order in a
  // group that does not have this property set will result in an
  // error.
  property::LinkCreationList lcpl;
  property::GroupCreationList gcpl;
  gcpl.link_creation_order (
      property::CreationOrder ().enable_tracked ().enable_indexed ());

  // Create primary group using the property list.
  node::Group group (file.root (), "index_group", lcpl, gcpl);

  // Create subgroups in the primary group.  These will be tracked
  // by creation order.  Note that these groups do not have to have
  // the creation order tracking property set.
  node::Group (group, "H");
  node::Group (group, "D");
  node::Group (group, "F");
  node::Group (group, "5");

  // Traverse links in the primary group using alphabetical indices
  // (H5_INDEX_NAME).
  std::cout << "Traversing group using alphabetical indices:" << std::endl
      << std::endl;
  group.iterator_config ().index (IterationIndex::NAME);
  group.iterator_config ().order (IterationOrder::INCREASING);
  size_t index = 0;
  for (node::Node node : group.nodes)
  {
    std::cout << "Index " << index++ << ": " << node.link ().path ().name ()
        << std::endl;
  }

  // Traverse links in the primary group by creation order
  // (H5_INDEX_CRT_ORDER).
  std::cout << std::endl << "Traversing group using creation order indices:"
      << std::endl << std::endl;
  group.iterator_config ().index (IterationIndex::CREATION_ORDER);
  index = 0;
  for (node::Node node : group.nodes)
  {
    std::cout << "Index " << index++ << ": " << node.link ().path ().name ()
        << std::endl;
  }

  return 0;
}
