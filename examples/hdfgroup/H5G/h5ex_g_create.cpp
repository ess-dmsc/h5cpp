/************************************************************

  This example shows how to create, open, and close a group.

  This file is intended for use with HDF5 Library version 1.8

 ************************************************************/

#include <h5cpp/hdf5.hpp>

#define FILE "h5ex_g_create.h5"

using namespace hdf5;

int main(void)
{
  // Create a new file using the default properties.
  file::File file = file::create (FILE, file::AccessFlags::TRUNCATE);

  // Create a group named "G1" in the file.
  node::Group group (file.root(), "/G1");

  // Close the group.  The handle "group" can no longer be used.
  group.close ();

  // Re-open the group, obtaining a new handle.
  group = node::get_node (file.root (), "/G1");

  return 0;
}
