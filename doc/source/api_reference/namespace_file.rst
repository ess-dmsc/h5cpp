===============================
Namespace :cpp:any:`hdf5::file`
===============================

The :cpp:class:`File` class
===========================

.. doxygenclass:: hdf5::file::File
   :members:
   
Functions
=========

:cpp:func:`create`
------------------

.. doxygenfunction:: hdf5::file::create(const fs::path &, AccessFlags, const property::FileCreationList &, const property::FileAccessList &)

:cpp:func:`open`
----------------

.. doxygenfunction:: hdf5::file::open(const fs::path &, AccessFlags, const property::FileAccessList &)

:cpp:func:`is_hdf5_file`
------------------------

.. doxygenfunction:: hdf5::file::is_hdf5_file

Enumerations
============

:cpp:class:`AccessFlags` and :cpp:type:`AccessFlagsBase`
--------------------------------------------------------

.. doxygenenum:: hdf5::file::AccessFlags

.. doxygentypedef:: hdf5::file::AccessFlagsBase

.. doxygenfunction:: hdf5::file::operator|(const AccessFlags &, const AccessFlags &)

.. doxygenfunction:: hdf5::file::operator|(const AccessFlagsBase &, const AccessFlags &)

.. doxygenfunction:: hdf5::file::operator|(const AccessFlags &, const AccessFlagsBase &)

.. doxygenfunction:: hdf5::file::operator&(const AccessFlags &, const AccessFlags &)

.. doxygenfunction:: hdf5::file::operator&(const AccessFlagsBase &, const AccessFlags &)

.. doxygenfunction:: hdf5::file::operator&(const AccessFlags &, const AccessFlagsBase &)

.. doxygenfunction:: hdf5::file::operator<<(std::ostream &, const AccessFlags &)

:cpp:class:`SearchFlags` and :cpp:type:`SearchFlagsBase`
--------------------------------------------------------

.. doxygenenum:: hdf5::file::SearchFlags

.. doxygentypedef:: hdf5::file::SearchFlagsBase

.. doxygenfunction:: hdf5::file::operator|(const SearchFlags &, const SearchFlags &)

.. doxygenfunction:: hdf5::file::operator|(const SearchFlagsBase &, const SearchFlags &)

.. doxygenfunction:: hdf5::file::operator|(const SearchFlags &, const SearchFlagsBase &)

.. doxygenfunction:: hdf5::file::operator&(const SearchFlags &, const SearchFlags &)

.. doxygenfunction:: hdf5::file::operator&(const SearchFlagsBase &, const SearchFlags &)

.. doxygenfunction:: hdf5::file::operator&(const SearchFlags &, const SearchFlagsBase &)

.. doxygenfunction:: hdf5::file::operator<<(std::ostream &, const SearchFlags &)

:cpp:class:`ImageFlags` and :cpp:type:`ImageFlagsBase`
------------------------------------------------------

.. doxygenenum:: hdf5::file::ImageFlags

.. doxygentypedef:: hdf5::file::ImageFlagsBase

.. doxygenfunction:: hdf5::file::operator|(const ImageFlags &, const ImageFlags &)

.. doxygenfunction:: hdf5::file::operator|(const ImageFlagsBase &, const ImageFlags &)

.. doxygenfunction:: hdf5::file::operator|(const ImageFlags &, const ImageFlagsBase &)

.. doxygenfunction:: hdf5::file::operator&(const ImageFlags &, const ImageFlags &)

.. doxygenfunction:: hdf5::file::operator&(const ImageFlagsBase &, const ImageFlags &)

.. doxygenfunction:: hdf5::file::operator&(const ImageFlags &, const ImageFlagsBase &)

.. doxygenfunction:: hdf5::file::operator<<(std::ostream &, const ImageFlags &)


:cpp:class:`Scope` and :cpp:type:`ScopeBase`
--------------------------------------------

.. doxygenenum:: hdf5::file::Scope

.. doxygentypedef:: hdf5::file::ScopeBase

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
