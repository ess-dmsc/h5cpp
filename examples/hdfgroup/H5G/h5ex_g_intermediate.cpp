/************************************************************

  This example shows how to create intermediate groups with
  a single call to H5Gcreate.

  This file is intended for use with HDF5 Library version 1.8

 ************************************************************/

#include <h5cpp/hdf5.hpp>

#define FILE            "h5ex_g_intermediate.h5"

using namespace hdf5;

int main(void)
{
  // Create a new file using the default properties.
  file::File file = file::create (FILE, file::AccessFlags::TRUNCATE);

  // Create group creation property list and set it to allow creation
  // of intermediate groups.
  property::LinkCreationList lcpl;
  lcpl.enable_intermediate_group_creation ();

  // Create the group /G1/G2/G3.  Note that /G1 and /G1/G2 do not
  // exist yet.  This call would cause an error if we did not use the
  // previously created property list.
  node::Group group (file.root (), "/G1/G2/G3", lcpl);

  // Print all the objects in the files to show that intermediate
  // groups have been created.  See h5ex_g_visit for more information
  // on how to use H5Ovisit.
  std::cout << "Objects in the file:" << std::endl;
  node::Group root_group = file.root ();
  root_group.iterator_config ().index (IterationIndex::NAME);
  root_group.iterator_config ().order (IterationOrder::NATIVE);
  std::for_each (node::RecursiveNodeIterator::begin (root_group),
                 node::RecursiveNodeIterator::end (root_group),
                 [](const node::Node &node)
                 {
                   std::cout<<node.link().path()<<" "<<node.type()<<std::endl;
                 });

  return 0;
}



