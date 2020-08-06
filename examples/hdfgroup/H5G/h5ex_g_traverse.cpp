/************************************************************

  This example shows a way to recursively traverse the file
  using H5Literate.  The method shown here guarantees that
  the recursion will not enter an infinite loop, but does
  not prevent objects from being visited more than once.
  The program prints the directory structure of the file
  specified in FILE.  The default file used by this example
  implements the structure described in the User's Guide,
  chapter 4, figure 26.

  This file is intended for use with HDF5 Library version 1.8

 ************************************************************/

#include <h5cpp/hdf5.hpp>
#include <algorithm>

#define FILE       "h5ex_g_traverse.h5"
using namespace hdf5;

int
main (void)
{
  // Open file and initialize the operator data structure.
  file::File file = file::open (FILE, file::AccessFlags::READONLY);
  node::Group root_group = file.root ();

  // Print the root group and formatting, begin iteration.
  std::cout << "/" << std::endl;
  std::for_each (node::RecursiveNodeIterator::begin (root_group),
                 node::RecursiveNodeIterator::end (root_group),
                 [](const node::Node &node)
                 {
                   std::cout<<node.link().path()<<" "<<node.type()<<std::endl;
                 });
  std::cout << std::endl;

  return 0;
}





