/************************************************************

  This example shows how to create "compact-or-indexed"
  format groups, new to 1.8.  This example also illustrates
  the space savings of compact groups by creating 2 files
  which are identical except for the group format, and
  displaying the file size of each.  Both files have one
  empty group in the root group.

  This file is intended for use with HDF5 Library version 1.8

 ************************************************************/

#include <h5cpp/hdf5.hpp>

#define FILE1       "h5ex_g_compact1.h5"
#define FILE2       "h5ex_g_compact2.h5"
#define GROUP       "G1"

using namespace hdf5;

void create_default_file()
{
  // Create file 1.  This file will use original format groups.
  file::File file = file::create (FILE1, file::AccessFlags::TRUNCATE);
  node::Group group (file.root(), GROUP);

  // Obtain the group info and print the group storage type.
  node::GroupInfo info = group.info();
  std::cout<<"Group storage type for "<<FILE1<<" is: "<<info.storage_type()<<std::endl;
}

void print_default_file_size()
{
  // Re-open file.  Needed to get the correct file size.
  file::File file = file::open (FILE1, file::AccessFlags::READONLY);

  // Obtain and print the file size.
  std::cout<<"File size for "<<FILE1<<" is: "<<file.size()<<" bytes"
      <<std::endl<<std::endl;
}

void create_compact_file()
{
  // Set file access property list to allow the latest file format.
  // This will allow the library to create new compact format groups.
  property::FileCreationList fcpl;
  property::FileAccessList fapl;
  fapl.library_version_bounds(property::LibVersion::LATEST,property::LibVersion::LATEST);

  // Create file 2 using the new file access property list.
  file::File file = file::create (FILE2,file::AccessFlags::TRUNCATE, fcpl, fapl);
  node::Group group(file.root(), GROUP);

  // Obtain the group info and print the group storage type.
  node::GroupInfo info = group.info();
  std::cout<<"Group storage type for "<<FILE2<<" is: "<<info.storage_type()<<std::endl;
}

void print_compact_file_size()
{
  property::FileAccessList fapl;
  fapl.library_version_bounds(property::LibVersion::LATEST,property::LibVersion::LATEST);
  file::File file = file::open (FILE2, file::AccessFlags::READONLY, fapl);

  // Obtain and print the file size.
  std::cout<<"File size for "<<FILE2<<" is: "<<file.size()<<" bytes"<<std::endl<<std::endl;

}

int main (void)
{
  create_default_file();
  print_default_file_size();
  create_compact_file();
  print_compact_file_size();

  return 0;
}
