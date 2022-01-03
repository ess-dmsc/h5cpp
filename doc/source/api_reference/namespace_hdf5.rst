=========================
Namespace :cpp:any:`hdf5`
=========================

Classes
=======

:cpp:class:`ObjectHandle`
-------------------------

.. doxygenclass:: hdf5::ObjectHandle
   :members:

.. doxygenenum:: hdf5::ObjectHandle::Policy

.. doxygenenum:: hdf5::ObjectHandle::Type

.. doxygenfunction:: hdf5::operator==(const ObjectHandle &,const ObjectHandle &)

.. doxygenfunction:: hdf5::operator!=(const ObjectHandle &,const ObjectHandle &)

.. doxygenfunction:: hdf5::operator<<(std::ostream &, const ObjectHandle::Type &)

:cpp:class:`Path`
-----------------

.. doxygenclass:: hdf5::Path
   :members:

.. doxygenfunction:: hdf5::operator+(const Path &,const Path &)

.. doxygenfunction:: hdf5::operator==(const Path &,const Path &)

.. doxygenfunction:: hdf5::operator!=(const Path &,const Path &)

.. doxygenfunction:: hdf5::operator<<(std::ostream &, const Path &)

.. doxygenfunction:: hdf5::common_base(const Path&, const Path&)

:cpp:class:`IteratorConfig`
---------------------------

.. doxygenclass:: hdf5::IteratorConfig
   :members:


.. doxygenenum:: hdf5::IterationOrder

.. doxygenfunction:: hdf5::operator<<(std::ostream &, const IterationOrder &)

.. doxygenenum:: hdf5::IterationIndex

.. doxygenfunction:: hdf5::operator<<(std::ostream &, const IterationIndex &)

:cpp:class:`Version`
--------------------

.. doxygenclass:: hdf5::Version
   :members:

.. doxygenfunction:: hdf5::operator<<(std::ostream &, const Version &)

.. doxygenfunction:: hdf5::operator==(const Version &,const Version &)

.. doxygenfunction:: hdf5::operator!=(const Version &,const Version &)

.. doxygenfunction:: hdf5::operator<=(const Version &,const Version &)

.. doxygenfunction:: hdf5::operator>=(const Version &,const Version &)

.. doxygenfunction:: hdf5::operator<(const Version &,const Version &)

.. doxygenfunction:: hdf5::operator>(const Version &,const Version &)

:cpp:class:`ObjectId`
---------------------

.. doxygenclass:: hdf5::ObjectId
   :members:

.. doxygenfunction:: hdf5::operator<<(std::ostream &, const ObjectId &)

:cpp:class:`Context`
--------------------

.. doxygenclass:: hdf5::Context
   :members:

:cpp:class:`IOWriteBuffer`
--------------------------

.. doxygenclass:: hdf5::IOWriteBuffer
   :members:

:cpp:class:`IOReadBuffer`
-------------------------

.. doxygenclass:: hdf5::IOReadBuffer
   :members:

:cpp:class:`FixedLengthStringBuffer`
------------------------------------

.. doxygenclass:: hdf5::FixedLengthStringBuffer
   :members:

:cpp:class:`Iterator`
---------------------

.. doxygenclass:: hdf5::Iterator
   :members:

.. doxygenfunction:: hdf5::operator+(const Iterator&, ssize_t)

.. doxygenfunction:: hdf5::operator+(ssize_t, const Iterator&)

.. doxygenfunction:: hdf5::operator-(const Iterator&, ssize_t)

.. doxygenfunction:: hdf5::operator-(const Iterator&, const Iterator&)

:cpp:class:`ArrayAdapter`
-------------------------

.. doxygenclass:: hdf5::ArrayAdapter
   :members:

Functions
=========

:cpp:func:`current_library_version`
-----------------------------------

.. doxygenfunction:: hdf5::current_library_version
