====================================
Namespace :cpp:any:`hdf5::dataspace`
====================================

Dataspace related classes and functions
=======================================

:cpp:class:`Dataspace`
----------------------

.. doxygenclass:: hdf5::dataspace::Dataspace
   :members:

:cpp:class:`Scalar`
-------------------

.. doxygenclass:: hdf5::dataspace::Scalar
   :members:

:cpp:class:`Simple`
-------------------

.. doxygenclass:: hdf5::dataspace::Simple
   :members:



Selection related classes and functions
=======================================

:cpp:class:`Selection` and :cpp:type:`SelectionList`
----------------------------------------------------

.. doxygenclass:: hdf5::dataspace::Selection
   :members:

.. doxygentypedef:: hdf5::dataspace::SelectionList

.. doxygenfunction:: hdf5::dataspace::operator||(const Dataspace &, const SelectionList &)


:cpp:class:`Hyperslab`
----------------------

.. doxygenclass:: hdf5::dataspace::Hyperslab
   :members:

.. doxygenfunction:: hdf5::dataspace::operator||(const Dataspace &, const Hyperslab &)
		     

:cpp:class:`Points`
-------------------

.. doxygenclass:: hdf5::dataspace::Points
   :members:

:cpp:class:`SelectionManager`
-----------------------------

.. doxygenclass:: hdf5::dataspace::SelectionManager
   :members:

:cpp:class:`View`
-----------------

.. doxygenclass:: hdf5::dataspace::View
   :members:

:cpp:class:`DataspaceHolder`
----------------------------

.. doxygenclass:: hdf5::dataspace::DataspaceHolder
   :members:

:cpp:class:`DataspacePool`
--------------------------

.. doxygenclass:: hdf5::dataspace::DataspacePool
   :members:

Type traits
===========

:cpp:class:`TypeTrait`
----------------------

.. doxygenclass:: hdf5::dataspace::TypeTrait
   :members:

Enumerations
============

:cpp:enum:`Type`
----------------

.. doxygenenum:: hdf5::dataspace::Type

.. doxygenfunction:: hdf5::dataspace::operator<<(std::ostream &, const Type &)

:cpp:enum:`SelectionType`
-------------------------

.. doxygenenum:: hdf5::dataspace::SelectionType

.. doxygenfunction:: hdf5::dataspace::operator<<(std::ostream &, const SelectionType &)

:cpp:enum:`SelectionOperation`
------------------------------

.. doxygenenum:: hdf5::dataspace::SelectionOperation

.. doxygenfunction:: hdf5::dataspace::operator<<(std::ostream &, const SelectionOperation &)
