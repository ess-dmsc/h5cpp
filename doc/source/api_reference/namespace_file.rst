===============================
Namespace :cpp:any:`hdf5::file`
===============================

Enumerations
============


The :cpp:class:`File` class
===========================

.. doxygenclass:: hdf5::file::File
   :members:
   
Functions
---------

.. doxygenfunction:: hdf5::file::create(const fs::path &, AccessFlags, const property::FileCreationList &, const property::FileAccessList &)

.. doxygenfunction:: hdf5::file::open(const fs::path &, AccessFlags, const property::FileAccessList &)

.. doxygenfunction:: hdf5::file::is_hdf5_file

Flags
-----

.. doxygenenum:: hdf5::file::AccessFlags

.. doxygenfunction:: hdf5::file::operator|(const AccessFlags &, const AccessFlags &)

.. doxygenfunction:: hdf5::file::operator<<(std::ostream &, const AccessFlags &)

.. doxygenenum:: hdf5::file::SearchFlags

.. doxygenfunction:: hdf5::file::operator|(const SearchFlags &, const SearchFlags &)

.. doxygenfunction:: hdf5::file::operator<<(std::ostream &, const SearchFlags &)

.. doxygenenum:: hdf5::file::Scope

.. doxygenfunction:: hdf5::file::operator<<(std::ostream &, const Scope &)


   
Driver classes
==============

:cpp:class:`Driver`
-------------------

.. doxygenclass:: hdf5::file::Driver
   :members:
   
.. doxygenenum:: hdf5::file::DriverID
   
:cpp:class:`PosixDriver`
------------------------

.. doxygenclass:: hdf5::file::PosixDriver
   :members:


:cpp:class:`MemoryDriver`
-------------------------
   
.. doxygenclass:: hdf5::file::MemoryDriver
   :members:

:cpp:class:`DirectDriver`
-------------------------

.. doxygenclass:: hdf5::file::DirectDriver
   :members:

:cpp:class:`MPIDriver`
----------------------

.. doxygenclass:: hdf5::file::MPIDriver
   :members:
