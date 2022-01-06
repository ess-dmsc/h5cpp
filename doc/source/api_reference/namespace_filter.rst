=================================
Namespace :cpp:any:`hdf5::filter`
=================================

Classes
=======

:cpp:class:`Filter`
-------------------

.. doxygenclass:: hdf5::filter::Filter
   :members:

:cpp:class:`ExternalFilter`
---------------------------

.. doxygenclass:: hdf5::filter::ExternalFilter
   :members:

:cpp:class:`ExternalFilters`
----------------------------

.. doxygenclass:: hdf5::filter::ExternalFilters
   :members:

Functions
=========

:cpp:func:`is_filter_available`
-------------------------------

.. doxygenfunction:: hdf5::filter::is_filter_available(FilterID)

Enumerations
============

:cpp:enum:`Availability`
------------------------

.. doxygenenum:: hdf5::filter::Availability

Filter classes
==============

:cpp:class:`Deflate`
--------------------

.. doxygenclass:: hdf5::filter::Deflate
   :members:

:cpp:class:`Shuffle`
--------------------

.. doxygenclass:: hdf5::filter::Shuffle
   :members:

:cpp:class:`Fletcher32`
-----------------------

.. doxygenclass:: hdf5::filter::Fletcher32
   :members:

:cpp:class:`SZip`
-----------------

.. doxygenclass:: hdf5::filter::SZip
   :members:

:cpp:class:`NBit`
-----------------

.. doxygenclass:: hdf5::filter::NBit
   :members:

:cpp:class:`ScaleOffset`
------------------------

.. doxygenclass:: hdf5::filter::ScaleOffset
   :members:

.. doxygenfunction:: hdf5::filter::operator<<(std::ostream &stream, const ScaleOffset::ScaleType &scale_type)
