/************************************************************

  This example shows how to set the conditions for
  conversion between compact and dense (indexed) groups.

  This file is intended for use with HDF5 Library version 1.8

 ************************************************************/

#include <h5cpp/hdf5.hpp>
#include <stdio.h>

#define FILE        "h5ex_g_phase.h5"
#define MAX_GROUPS  7
#define MAX_COMPACT 5
#define MIN_DENSE   3

using namespace hdf5;

void print_group_info(const node::GroupInfo &info)
{
  std::string group = "Group";

  group += info.number_of_links () == 1 ? " " : "s";
  std::cout << info.number_of_links () << group << ": Storage type is "
      << info.storage_type () << std::endl;
}

int main (void)
{
  char name[3] = "G0"; /* Name of subgroup */

  // Set file access property list to allow the latest file format.
  // This will allow the library to create new format groups.
  property::FileCreationList fcpl;
  property::FileAccessList fapl;
  fapl.library_version_bounds (property::LibVersion::LATEST,
                               property::LibVersion::LATEST);

  // Create group access property list and set the phase change
  // conditions.  In this example we lowered the conversion threshold
  // to simplify the output, though this may not be optimal.
  property::LinkCreationList lcpl;
  property::GroupCreationList gcpl;
  gcpl.link_storage_thresholds (MAX_COMPACT, MIN_DENSE);

  // Create a new file using the default properties.
  file::File file = file::create (FILE, file::AccessFlags::TRUNCATE, fcpl,
                                  fapl);

  // Create primary group.
  node::Group group (file.root(), "G0", lcpl, gcpl);

  // Add subgroups to "group" one at a time, print the storage type
  // for "group" after each subgroup is created.
  for (size_t i = 1; i <= MAX_GROUPS; i++)
  {

    {
      std::stringstream ss;
      ss << "G0_" << i;
      node::Group (group, ss.str ());
    }

    // Obtain the group info and print the group storage type
    print_group_info (group.info ());
  }
  std::cout<<std::endl;

  // Delete subgroups one at a time, print the storage type for
  // "group" after each subgroup is deleted.
  for (ssize_t i = MAX_GROUPS; i >= 1; i--)
  {
    // Define the subgroup name and delete the subgroup.
    std::stringstream ss;
    ss << "G0_" << i;
    node::remove (group, ss.str ());

    // Obtain the group info and print the group storage type
    print_group_info (group.info ());
  }

  return 0;
}
