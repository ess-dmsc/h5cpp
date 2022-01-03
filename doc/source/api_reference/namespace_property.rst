===================================
Namespace :cpp:any:`hdf5::property`
===================================

Classes
=======

:cpp:class:`AttributeCreationList`
----------------------------------

.. doxygenclass:: hdf5::property::AttributeCreationList
   :members:

:cpp:class:`ChunkCacheParameters`
---------------------------------

.. doxygenclass:: hdf5::property::ChunkCacheParameters
   :members:

:cpp:class:`Class`
------------------

.. doxygenclass:: hdf5::property::Class
   :members:

.. doxygenfunction:: hdf5::property::operator==(const Class &, const Class &)

.. doxygenfunction:: hdf5::property::operator!=(const Class &, const Class &)

:cpp:class:`CopyFlags`
----------------------

.. doxygenclass:: hdf5::property::CopyFlags
   :members:

:cpp:class:`CreationOrder`
--------------------------

.. doxygenclass:: hdf5::property::CreationOrder
   :members:

:cpp:class:`DatasetAccessList`
------------------------------

.. doxygenclass:: hdf5::property::DatasetAccessList
   :members:

:cpp:class:`DatasetCreationList`
--------------------------------

.. doxygenclass:: hdf5::property::DatasetCreationList
   :members:

:cpp:class:`DatasetTransferList`
--------------------------------

.. doxygenclass:: hdf5::property::DatasetTransferList
   :members:

:cpp:class:`DatatypeAccessList`
-------------------------------

.. doxygenclass:: hdf5::property::DatatypeAccessList
   :members:

:cpp:class:`FileAccessList`
---------------------------

.. doxygenclass:: hdf5::property::FileAccessList
   :members:

:cpp:class:`FileCreationList`
-----------------------------

.. doxygenclass:: hdf5::property::FileCreationList
   :members:

:cpp:class:`FileMountList`
--------------------------

.. doxygenclass:: hdf5::property::FileMountList
   :members:

:cpp:class:`GroupAccessList`
----------------------------

.. doxygenclass:: hdf5::property::GroupAccessList
   :members:

:cpp:class:`GroupCreationList`
------------------------------

.. doxygenclass:: hdf5::property::GroupCreationList
   :members:

:cpp:class:`LinkAccessList`
---------------------------

.. doxygenclass:: hdf5::property::LinkAccessList
   :members:

:cpp:class:`LinkCreationList`
-----------------------------

.. doxygenclass:: hdf5::property::LinkCreationList
   :members:

:cpp:class:`List`
-----------------

.. doxygenclass:: hdf5::property::List
   :members:

:cpp:class:`ObjectCopyList`
---------------------------

.. doxygenclass:: hdf5::property::ObjectCopyList
   :members:

:cpp:class:`ObjectCreationList`
-------------------------------

.. doxygenclass:: hdf5::property::ObjectCreationList
   :members:

:cpp:class:`StringCreationList`
-------------------------------

.. doxygenclass:: hdf5::property::StringCreationList
   :members:

:cpp:class:`TypeCreationList`
-----------------------------

.. doxygenclass:: hdf5::property::TypeCreationList
   :members:

:cpp:class:`VirtualDataMap`
---------------------------

.. doxygenclass:: hdf5::property::VirtualDataMap
   :members:

.. doxygenclass:: hdf5::property::VirtualDataMaps
   :members:

Enumerations
============

:cpp:enum:`DatasetFillValueStatus`
----------------------------------

.. doxygenenum:: hdf5::property::DatasetFillValueStatus

.. doxygenfunction:: hdf5::property::operator<<(std::ostream &, const DatasetFillValueStatus &)

:cpp:enum:`DatasetFillTime`
---------------------------

.. doxygenenum:: hdf5::property::DatasetFillTime

.. doxygenfunction:: hdf5::property::operator<<(std::ostream &, const DatasetFillTime &)

:cpp:enum:`DatasetAllocTime`
----------------------------

.. doxygenenum:: hdf5::property::DatasetAllocTime

.. doxygenfunction:: hdf5::property::operator<<(std::ostream &, const DatasetAllocTime &)

:cpp:enum:`DatasetLayout`
-------------------------

.. doxygenenum:: hdf5::property::DatasetLayout

.. doxygenfunction:: hdf5::property::operator<<(std::ostream &, const DatasetLayout &)

:cpp:enum:`LibVersion`
----------------------

.. doxygenenum:: hdf5::property::LibVersion

.. doxygenfunction:: hdf5::property::operator<<(std::ostream &, const LibVersion &)

:cpp:enum:`CopyFlag` and :cpp:type:`CopyFlags`
----------------------------------------------

.. doxygenenum:: hdf5::property::CopyFlag

.. doxygenfunction:: hdf5::property::operator|(const CopyFlag &, const CopyFlag &)

.. doxygenfunction:: hdf5::property::operator|(const CopyFlags &, const CopyFlag &) noexcept

.. doxygenfunction:: hdf5::property::operator|(const CopyFlag &, const CopyFlags &) noexcept

.. doxygenfunction:: hdf5::property::operator|(const CopyFlags &, const CopyFlags &) noexcept

.. doxygenfunction:: hdf5::property::operator&(const CopyFlag &, const CopyFlag &)

.. doxygenfunction:: hdf5::property::operator&(const CopyFlags &, const CopyFlag &) noexcept

.. doxygenfunction:: hdf5::property::operator&(const CopyFlag &, const CopyFlags &) noexcept

.. doxygenfunction:: hdf5::property::operator&(const CopyFlags &, const CopyFlags &) noexcept

.. doxygenfunction:: hdf5::property::operator<<(std::ostream &, const CopyFlag &)

:cpp:enum:`VirtualDataView`
---------------------------

.. doxygenenum:: hdf5::property::VirtualDataView

.. doxygenfunction:: hdf5::property::operator<<(std::ostream &, const VirtualDataView &)

:cpp:enum:`CloseDegree`
-----------------------

.. doxygenenum:: hdf5::property::CloseDegree

:cpp:enum:`MPITransferMode`
---------------------------

.. doxygenenum:: hdf5::property::MPITransferMode

:cpp:enum:`MPIChunkOption`
--------------------------

.. doxygenenum:: hdf5::property::MPIChunkOption

Property Class variables
========================

.. cpp:var:: const Class kAttributeCreate

.. cpp:var:: const Class kDatasetAccess

.. cpp:var:: const Class kDatasetCreate

.. cpp:var:: const Class kDatasetXfer

.. cpp:var:: const Class kDatatypeAccess

.. cpp:var:: const Class kDatatypeCreate

.. cpp:var:: const Class kFileAccess

.. cpp:var:: const Class kFileCreate

.. cpp:var:: const Class kFileMount

.. cpp:var:: const Class kGroupAccess

.. cpp:var:: const Class kGroupCreate

.. cpp:var:: const Class kLinkAccess

.. cpp:var:: const Class kLinkCreate

.. cpp:var:: const Class kObjectCopy

.. cpp:var:: const Class kObjectCreate

.. cpp:var:: const Class kStringCreate
