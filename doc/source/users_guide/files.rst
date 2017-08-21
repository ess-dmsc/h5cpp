==================
Working with files
==================

.. sectionauthor:: Eugen Wintersberger <eugen.wintersberger@desy.de>
.. codeauthor:: Eugen Wintersberger <eugen.wintersberger@desy.de>

.. todo::

    How do we deal with the meta-data cache?

Open and create files
=====================

.. code-block:: cpp

    using namespace fs = boost::filesystem;
    //creating a new file
    fs::path file_path("name.h5");
    h5::file_t f1 = h5::file_t::create(file_path,
                                       h5::file_t::flag_t::TRUNCATE,
                                       file_creation_plist(),
                                       file_access_plist());

    //opening an existing file
    h5::file_t f2 = h5::file_t::open(file_path,
                                     h5::file_t::flag_t::READ_WRITE,
                                     file_access_plist());

Unlike in the C-API an instance of :cpp:class:`h5::file_t` is not a valid parent object.
For this purpose the root group of the file must be obtained using the
:cpp:func:`root()` method of a file instance

.. code-block:: cpp

    h5::group_t root_group = f.root();

.. admonition:: Rational 

    Though in the C-API the ID of a group and a file can both act as valid
    parent object, this approach does not run well with an object oriented
    appraoch. It would mean that :cpp:class:`file_t` and :cpp:class:`group_t`
    would have to provide a common, group-like interface. 

    In order to avoid code duplications we :cpp:class:`file_t` would have to
    derive from :cpp:class:`group_t` making it also a valid group object. From
    the point of semantics this is simply wrong. A file is not a group. 
    
    Though the approach choosen here requires a single line of code more to
    obtain the root group of a file before doing any useful work on the file,
    however, I think a clean difference between :cpp:class:`file_t` and
    :cpp:class:`group_t` is worth the additional effort.

Methods
=======

.. cpp:class:: file_t

    .. cpp:enum-struct:: flag_t : uint8_t


    .. cpp:function:: public boost::filesystem_path path() const
        
        Return the file system path for this instance of :cpp:class:`file_t`.


    .. cpp:function:: public void flush() const

        Flush data to the file.

    .. cpp:function:: public flag_t mode() const

        Return the current mode the file is opened.

    .. cpp:function:: public group_t root() const

        Return the root group of the file as an instance of
        :cpp:class:`group_t`.



Flags
=====

The :cpp:class:`file_t` class has a nested scoped enumeration type
:cpp:enum:`file_t::flags` with flags used to open and create files as well as
to denote the status of a file.

+----------------------------------------------+------------------------------+
|  Flag                                        | Description                  |
+==============================================+==============================+
| :cpp:enumerator:`file_t::flag_t::TRUNCATE`   | overwrite an already existing|
|                                              | file during file creation!   | 
+----------------------------------------------+------------------------------+
| :cpp:enumerator:`file_t::flag_t::EXCL`       | file creation will fail if a | 
|                                              | file of equal name already   |
|                                              | exists                       | 
+----------------------------------------------+------------------------------+
| :cpp:enumerator:`file_t::flag_t::READ_WRITE` | open a file for read write   | 
|                                              | access or the file is in     | 
|                                              | read write mode              |
+----------------------------------------------+------------------------------+
| :cpp:enumerator:`file_t::flag_t::READ_ONLY`  | open a file in read only mode| 
|                                              | or the file is in read only  | 
|                                              | mode                         |
+----------------------------------------------+------------------------------+
| :cpp:enumerator:`file_t::flag_t::SWMR_WRITE` | open the file in SWMR write  | 
|                                              | mode or the file is in SWMR  | 
|                                              | write mode                   |
+----------------------------------------------+------------------------------+
| :cpp:enumerator:`file_t::flag_t::SWMR_READ`  | open a file in SWMR read mode|
|                                              | or the file is in SWMR read  | 
|                                              | mode.                        |
+----------------------------------------------+------------------------------+


Utility types and functions
===========================

The function :cpp:func:`is_hdf5_file` checks whether or not a file system path
points to an HDF5 file or not. 

.. code-block:: cpp

    boost::filesystem::path file_path = ...;

    if(!h5::is_hdf5_file(file_path))
    {
        std::cerr<<"Some error message!"<<std::endl;
        return 1;
    }
    



