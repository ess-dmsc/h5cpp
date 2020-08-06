/************************************************************

  This example shows how to iterate over group members using
  H5Literate.

  This file is intended for use with HDF5 Library version 1.8

 ************************************************************/

#include <h5cpp/hdf5.hpp>
#include <algorithm>

#define FILE       "h5ex_g_iterate.h5"

using namespace hdf5;

int main (void)
{
  // Open file.
  file::File file = file::open (FILE, file::AccessFlags::READONLY);
  node::Group root_group = file.root ();

  // Begin iteration.
  std::cout << "Objects in root group:" << std::endl;
  std::for_each (root_group.nodes.begin (), root_group.nodes.end (),
                 [](const node::Node &node)
                 {
                   std::cout<<node.type()<<" "<<node.link().path()<<std::endl;
                 });

  return 0;
}

