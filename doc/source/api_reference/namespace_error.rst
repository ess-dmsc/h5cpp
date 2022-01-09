================================
Namespace :cpp:any:`hdf5::error`
================================

Classes
=======

:cpp:class:`Singleton`
----------------------

.. doxygenclass:: hdf5::error::Singleton
   :members:

:cpp:class:`H5CError`
---------------------

.. doxygenclass:: hdf5::error::H5CError
   :members:

:cpp:class:`Descriptor`
-----------------------

.. doxygenstruct:: hdf5::error::Descriptor
   :members:

.. doxygenfunction:: hdf5::error::operator<<(std::ostream &, const Descriptor &)

Functions
=========

:cpp:func:`print_nested`
------------------------

.. doxygenfunction:: hdf5::error::print_nested(const std::exception&, size_t)
