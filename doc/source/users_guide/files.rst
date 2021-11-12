==================
Working with files
==================

.. sectionauthor:: Eugen Wintersberger <eugen.wintersberger@desy.de>
.. codeauthor:: Eugen Wintersberger <eugen.wintersberger@desy.de>

.. todo::

    For the time being, *h5cpp* provides no interface to the metadata 
    cache. This feature might be added in future. 
    
The first things you have to do when using HDF5 is to create a new file or 
open an already existing one. This chapter deals with this very basic topic.
Unlike in the C-API filenames are not represented by mere strings but by
instances of :cpp:class:`boost::filesystem::path`. This avoids problems 
when using different seperator characters in a path on different platforms.
Additionally a file system path has a particular semantic which is not 
reflecetd by a simple string. 

Identifying an HDF5 file
========================

Before opening an HDF5 file we should check whether or not the filesystem object 
referenced by :cpp:class:`boost::filesystem::path` is indeed an HDF5 file. 
The simpliest way to achieve this goal is to use the 
:cpp:func:`hdf5::file::is_hdf5_file` utiltiy function function.

.. code-block:: cpp

   boost::filesystem::path file_path = ...;
   
   if(!hdf5::file::is_hdf5_file(file_path))
   {
      //deal with the error situation
   }
   
   //continue with opening the file 

Creating files
==============

The first thing one may wants to do is to create a new file. Use the 
:cpp:func:`hdf5::file::create` function

.. code-block:: cpp

    #include <h5cpp/hdf5.hpp>
    #include <boost/filesystem.hpp>

    using namespace hdf5;
    using namespace fs = boost::filesystem;
    
    int main()
    {
      //creating a new file
      fs::path file_path("data.h5");
      file::File f1 = file::create(file_path);

      //do something with the file
    }
                
By default, the :cpp:func:`hdf5::file::create` function will throw an 
exception if the file already exists. To overwrite an already existing file 
use 

.. code-block:: cpp

   file::File f1 = file::create(file_path,file::AccessFlags::Truncate);
   
HDF5 uses property lists to pass additional information to API functions. 
The :cpp:func:`hdf5::file::create` function accepts two additional arguments 

* a reference to a file creation property list
  (:cpp:class:`hdf5::property::FileCreateList`)
* and a reference to a file access property list 
  (:cpp:class:`hdf5::property::FileAccessList`) 
  
There are several situations when you have to use these property lists to 
create a file. The most common might be 

* you want better control over object and link iteration 
* you want to use the SWMR feature introduced with HDF5 1.10. 

We will deal with the iterator problem a bit later. For now we have a look 
on the SWMR feature. Provided you link *h5cpp* against HDF5 1.10.0 or higher 
you have to provide a custom file access property list 

.. code-block:: cpp

   property::FileCreationList fcpl; //can use the default here
   property::FileAccessList fapl;
   
   //we need to set the appropriate version flags
   fapl.library_version_bounds(property::LibVersion::Latest,
                               property::LibVersion::Latest);
                               
   file::File f = file::create("swmr_file.h5",
                               file::AccessFlags::Truncate,
                               fcpl,fapl);
  
Opening an existing file
========================

To open a file use the :cpp:func:`hdf5::file::open` function 

.. code-block:: cpp

    #include <h5cpp/hdf5.hpp>
    #include <boost/filesystem.hpp>

    using namespace hdf5;
    using namespace fs = boost::filesystem;
    
    int main()
    {
      //creating a new file
      fs::path file_path("data.h5");
      file::File f1 = file::open(file_path);

      //do something with the file
    }
    
By default, files are opened in read only mode to avoid accidental modification
of the file. To write to an existing file use 

.. code-block:: cpp

   file::File f1 = file::open(file_path,file::AccessFlags::ReadWrite);
   
The only additional argument :cpp:func:`hdf5::file::open` takes is a 
reference to file access property list. We have to use this to open a file 
for SWMR access. However, in addition we need some custom flags to use 
SWMR. To open a file for writing in SWMR mode use 

.. code-block:: cpp

   property::FileAccessList fapl;
   //we need to set the appropriate version flags
   fapl.library_version_bounds(property::LibVersion::Latest,
                               property::LibVersion::Latest);
   
   file::File write_fiel = file::open(file_path,
                                      file::AccessFlags::ReadWrite | 
                                      file::AccessFlags::SWMRWrite,
                                      fapl);
                                      
and to open a file for reading in SWMR mode use 

.. code-block:: cpp

   property::FileAccessList fapl;
   //we need to set the appropriate version flags
   fapl.library_version_bounds(property::LibVersion::Latest,
                               property::LibVersion::Latest);
   
   file::File write_fiel = file::open(file_path,
                                      file::AccessFlags::ReadOnly | 
                                      file::AccessFlags::SWMRRead,
                                      fapl);

Getting access to the object tree
=================================

Unlike in the C-API an instance of :cpp:class:`hdf5::File` is not a valid 
parent object. For this purpose the root group of the file must be obtained 
using the :cpp:func:`File::root()` method of a file instance

.. code-block:: cpp

    hdf5::file::File f = ....;
    hdf5::node::Group root_group = f.root();

.. admonition:: Rational 

    Though in the C-API the ID of a group and a file can both act as valid
    parent object, this approach does not run well with an object oriented
    appraoch. It would mean that :cpp:class:`hdf5::file::File` 
    and :cpp:class:`hdf5::node::Gruop` would have to provide a common, 
    group-like interface. 

    In order to avoid code duplications we :cpp:class:`hdf5::file::File` 
    would have to derive from :cpp:class:`hdf5::node::Group` making it 
    also a valid group object. From the point of semantics this is simply 
    wrong. A file is not a group. 
    
    Though the approach choosen here requires a single line of code more to
    obtain the root group of a file before doing any useful work on the file,
    however, I think a clean difference between :cpp:class:`hdf5::file::File` 
    and :cpp:class:`hdf5::node::Group` is worth the additional effort.
    


