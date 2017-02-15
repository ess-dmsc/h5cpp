========================
General design questions
========================

This chapter discusses some general design concepts of the library. 

.. attention::

    Everything in this chapter is open or discussion!

.. _design-templates:

Avoid templates if possible
===========================

As a general rule of thumb we should try to avoid templates whenever possible. 
They should only be used when compile time optimization provides a significant 
performance boost. 
As this library can be expected to become a crucial resource for many programs 
and even other libraries, templates, as useful as they are when used with care, 
can cause severe problems when maintaining library installations. 

If a bug in a class or function template gets fixed there are several
consequences for the software relying on it

* all programs and libraries using this particular template have to be rebuilt
* consequently new packages (RPM, Deb, MSI, ...) must be built
* updates, not only for the library, but also for all programs using it must be 
  installed. 

For a classical shared library (non-template) the only thing we have to do in
case of a simple bug-fix is to update the library installation. This is only a
single package that has to be rebuilt and installed. 

Thus 

.. attention::

    To keep the maintenance effort for system adminstrators and package
    maintainers of software that uses our library as small as possible we
    should use templates only in those cases where they significantly improve
    the performance or simplify the code!

In the case that templates are we should take the following rules into account

* keep the template code as short as possible 
* test function and class templates as extensive as possible. 

.. _design-API:

Keeping the ABI small
=====================

.. note::

    This is somehow related to the previous section. 

In order to keep library updates for software developers, package maintainers
and system administrators as painless as possible we should provide a rather
minimal ABI. This means that the shared object created should only export
symbols which are intended to be used by other developers (exporting all
symbols by default can cause a lot of other problems too, a good 
introduction to the problem can be found in [#f1]_). 

In other words we should try to keep the public ABI as minimal as possible in
order to avoid pumping the ABI version (see [#f2]_) whenever possible. 
If the ABI version does not change a simple library update will do the job and
none of the programs relying on the library will have to be recompiled. 

.. rubric:: Footnotes

.. [#f1] `How to write shared libraries, Drepper, 2011`_
.. [#f2] `Libtools versioning system`_

.. _How to write shared libraries, Drepper, 2011: https://software.intel.com/sites/default/files/m/a/1/e/dsohowto.pdf
.. _Libtools versioning system: https://www.gnu.org/software/libtool/manual/html_node/Libtool-versioning.html


.. _design-dependencies:

Acceptable dependencies
=======================

To make the library easy to distribute 3rd party dependencies should be kept
as small as possible. Aside from the dependencies required by the HDF5 C-library
the only acceptable requirement for me would be the `Boost libraries`_.

.. admonition:: Rational

    The `Boost libraries`_ can be considered an extension of the C++ 
    standard library. So it can be expected to be available on all 
    development plattforms for C++. 

.. _Boost libraries: http://www.boost.org/


.. _design-file-system-objects:

Referencing file system objects
===============================


It is common for C++ and C programs to use an instance of
:cpp:type:`std::string` or :cpp:type:`char` to store the path 
of an object on a computers file system. 

I strongly discourage this approach as, again, the semantics of a string and a
file system path is quite different. I suggest to use 
:cpp:class:`boost::filesystem::path` instead of strings to reference objects on
the file system.

.. admonition:: Rational

    There are two problems with strings 

    * users tend to not care about the different syntax of a filesystem path on
      different plattforms  which can cause problems for cross-plattform 
      software.
    * In this particular case already the type passed shows what a function
      expects as an input.
