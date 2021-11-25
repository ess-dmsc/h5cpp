===============================
Namespace :cpp:any:`hdf5::node`
===============================

Classes
=======

:cpp:class:`Node`
-----------------

.. doxygenclass:: hdf5::node::Node
   :members:

.. doxygenfunction:: hdf5::node::operator==(const Node &, const Node &)

.. doxygenfunction:: hdf5::node::operator!=(const Node &, const Node &)

:cpp:class:`Link`
-----------------

.. doxygenclass:: hdf5::node::Link
   :members:

.. doxygenfunction:: hdf5::node::operator!=(const Link &, const Link &)

.. doxygenfunction:: hdf5::node::operator<<(std::ostream &, const Link &)

:cpp:class:`LinkTarget`
-----------------------

.. doxygenclass:: hdf5::node::LinkTarget
   :members:

:cpp:class:`Group`
------------------

.. doxygenclass:: hdf5::node::Group
   :members:

:cpp:class:`GroupView`
----------------------

.. doxygenclass:: hdf5::node::GroupView
   :members:

:cpp:class:`NodeView`
---------------------

.. doxygenclass:: hdf5::node::NodeView
   :members:

.. doxygenclass:: hdf5::node::NodeIterator
   :members:

.. doxygenclass:: hdf5::node::RecursiveNodeIterator
   :members:

:cpp:class:`LinkView`
---------------------

.. doxygenclass:: hdf5::node::LinkView
   :members:

.. doxygenclass:: hdf5::node::LinkIterator
   :members:

.. doxygenclass:: hdf5::node::RecursiveLinkIterator
   :members:

:cpp:class:`Dataset`
--------------------

.. doxygenclass:: hdf5::node::Dataset
   :members:


:cpp:class:`ChunkedDataset`
---------------------------

.. doxygenclass:: hdf5::node::ChunkedDataset
   :members:


:cpp:class:`VirtualDataset`
---------------------------

.. doxygenclass:: hdf5::node::VirtualDataset
   :members:

Functions
=========

:cpp:func:`copy`
----------------

.. doxygenfunction:: hdf5::node::copy(const Node &, const Group &, const property::ObjectCopyList &, const property::LinkCreationList &)

:cpp:func:`move`
----------------

.. doxygenfunction:: hdf5::node::move(const Node &, const Group &, const Path &, const property::LinkCreationList &, const property::LinkAccessList &)

.. doxygenfunction:: hdf5::node::move(const Node &, const Group &, const property::LinkCreationList &, const property::LinkAccessList &)

:cpp:func:`remove`
------------------

.. doxygenfunction:: hdf5::node::remove(const Node &, const property::LinkAccessList &)

.. doxygenfunction:: hdf5::node::remove(const Group &, const Path &, const property::LinkAccessList &)

:cpp:func:`link`
----------------

.. doxygenfunction:: hdf5::node::link(const Node &, const Group &, const Path &, const property::LinkCreationList &, const property::LinkAccessList &)

.. doxygenfunction:: hdf5::node::link(const Path &, const Group &, const Path &, const property::LinkCreationList &, const property::LinkAccessList &)

.. doxygenfunction:: hdf5::node::link(const fs::path &, const Path &, const Group &, const Path &, const property::LinkCreationList &, const property::LinkAccessList &)


:cpp:func:`get_node`
--------------------

.. doxygenfunction:: hdf5::node::get_node

:cpp:func:`get_real_base`
-------------------------

.. doxygenfunction:: hdf5::node::get_real_base

:cpp:func:`get_group`
---------------------

.. doxygenfunction:: hdf5::node::get_group

:cpp:func:`get_dataset`
-----------------------

.. doxygenfunction:: hdf5::node::get_dataset

:cpp:func:`is_group`
--------------------

.. doxygenfunction:: hdf5::node::is_group

:cpp:func:`is_dataset`
----------------------

.. doxygenfunction:: hdf5::node::is_dataset


Enumerations
============

:cpp:enum:`NodeType`
--------------------

.. doxygenenum:: hdf5::node::NodeType

.. doxygenfunction:: hdf5::node::operator<<(std::ostream &, const NodeType &)

:cpp:enum:`LinkType`
--------------------

.. doxygenenum:: hdf5::node::LinkType

.. doxygenfunction:: hdf5::node::operator<<(std::ostream &, const LinkType &)
