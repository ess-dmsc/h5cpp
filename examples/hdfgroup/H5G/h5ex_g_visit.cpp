/************************************************************

  This example shows how to recursively traverse a file
  using H5Ovisit and H5Lvisit.  The program prints all of
  the objects in the file specified in FILE, then prints all
  of the links in that file.  The default file used by this
  example implements the structure described in the User's
  Guide, chapter 4, figure 26.

  This file is intended for use with HDF5 Library version 1.8

 ************************************************************/

#include <h5cpp/hdf5.hpp>
#include <algorithm>

#define FILE       "h5ex_g_visit.h5"
using namespace hdf5;

int main (void)
{

  // Open file
  file::File file = file::open (FILE, file::AccessFlags::READONLY);
  node::Group root_group = file.root ();

  /*
   * Begin iteration using H5Ovisit
   */
  std::cout << "Objects in the file:" << std::endl;
  std::for_each (node::RecursiveNodeIterator::begin (root_group),
                 node::RecursiveNodeIterator::end (root_group),
                 [](const node::Node &node)
                 {
                   std::cout<<node.type()<<" "<<node.link().path()<<std::endl;
                 });

  /*
   * Repeat the same process using H5Lvisit
   */
  std::cout << "Links in the file:" << std::endl;
  std::for_each (node::RecursiveLinkIterator::begin (root_group),
                 node::RecursiveLinkIterator::end (root_group),
                 [](const node::Link &link)
                 {
                   std::cout<<link.type()<<" "<<link.path()<<std::endl;
                 });

  return 0;
}


