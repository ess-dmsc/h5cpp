===================================
Namespace :cpp:any:`hdf5::datatype`
===================================

Classes
=======

:cpp:class:`Datatype`
---------------------

.. doxygenclass:: hdf5::datatype::Datatype
   :members:

:cpp:class:`Array`
------------------

.. doxygenclass:: hdf5::datatype::Array
   :members:

:cpp:class:`VLengthArray`
-------------------------

.. doxygenclass:: hdf5::datatype::VLengthArray
   :members:

:cpp:class:`Compound`
---------------------

.. doxygenclass:: hdf5::datatype::Compound
   :members:

:cpp:class:`Float`
------------------

.. doxygenclass:: hdf5::datatype::Float
   :members:

:cpp:class:`Integer`
--------------------

.. doxygenclass:: hdf5::datatype::Integer
   :members:

:cpp:class:`String`
-------------------

.. doxygenclass:: hdf5::datatype::String
   :members:

:cpp:class:`Enum`
-----------------

.. doxygenclass:: hdf5::datatype::Enum
   :members:

Type traits
===========

.. doxygenclass:: hdf5::datatype::TypeTrait
   :members:

Enumerations
============

:cpp:enum:`EBool`
-----------------

.. doxygenenum:: hdf5::datatype::EBool

.. doxygenfunction:: hdf5::datatype::is_bool(const Enum &);
                 
:cpp:enum:`Order`
-----------------

.. doxygenenum:: hdf5::datatype::Order

.. doxygenfunction:: hdf5::datatype::operator<<(std::ostream &, const Order &)

:cpp:enum:`Sign`
----------------

.. doxygenenum:: hdf5::datatype::Sign

.. doxygenfunction:: hdf5::datatype::operator<<(std::ostream &, const Sign &)

:cpp:enum:`Norm`
----------------

.. doxygenenum:: hdf5::datatype::Norm

.. doxygenfunction:: hdf5::datatype::operator<<(std::ostream &, const Norm &)

:cpp:enum:`Pad`
---------------
.. doxygenenum:: hdf5::datatype::Pad

.. doxygenfunction:: hdf5::datatype::operator<<(std::ostream &, const Pad &)

:cpp:enum:`StringPad`
---------------------

.. doxygenenum:: hdf5::datatype::StringPad

.. doxygenfunction:: hdf5::datatype::operator<<(std::ostream &, const StringPad &)

:cpp:enum:`Direction`
---------------------

.. doxygenenum:: hdf5::datatype::Direction

.. doxygenfunction:: hdf5::datatype::operator<<(std::ostream &, const Direction &)

:cpp:enum:`CharacterEncoding`
-----------------------------

.. doxygenenum:: hdf5::datatype::CharacterEncoding

.. doxygenfunction:: hdf5::datatype::operator<<(std::ostream &, const CharacterEncoding &)

:cpp:enum:`Class`
-----------------

.. doxygenenum:: hdf5::datatype::Class

.. doxygenfunction:: hdf5::datatype::operator<<(std::ostream &, const Class &)

