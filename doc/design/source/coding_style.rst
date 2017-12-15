================
Coding guidlines
================

.. attention::

    Everything in this chapter should be considered as a topic for dicussion
    and nothing is chisled in stone yet!

Some ideas here have been inspired by the `Ada Style Guide`_. Though not
written for the C++ language I personally like the authors approach to put a
*rational* after each suggestion to clarifying that they are not only a matter
of mere personal taste but are the result of rational reasoning (at least to
some extent).

The aim of these coding guidelines is to produce easily readable code with 
or without using a sophisticated IDE. Thus, arguing that some of these 
conventions are not necessary as the IDE will, for instance, discriminate 
between type and variable names with appropriate syntax highlightening is 
not valid. 
The code should remain readable even in the most basic text editor on a 
command line.  

Naming conventions
==================

* all class and type names are lowercase
* type and class names end with an ``_t``
* the `_` underscore is used to separate words

Some examples would be

.. code-block:: cpp

    using hdims_t = std::vector<hsize_t>;

    class dataset_t
    {

    };



.. admonition:: Rational

    This convention is quite contrary to the far more common Pascal- and
    Camelcase convention used today. However, there are, in my opinion, good
    reasons to prefer the above rules 

    * all lower case is simpler to type 
    * the underscore is much closer to a blank an separates word more clearly
    * this convention is closer to what programmers are used to from the C++
      standard  library.
    * avoid nameclashes between type and variable names.
    
A more elaborate rational on the `_t` suffix
--------------------------------------------

It is reasonable to have self-explanatory type names as it is for variable 
names (names of instances of a particular type). However, this can 
lead to name-clashes if both names are obvious choices. 

Consider as an example IDs in HDF5. It is reasonable to have a type 
:cpp:class:`id` encapsulating a single :cpp:type:`hid_t` value, taking care 
about alle the reference counting. However, at the same time it would be 
reasonable to give an instance of this type the name *id*. 
Which would lead to something like 

.. code-block:: cpp

    id id;
    
which is wrong for obvious reasons. Other languages like Java or C# use 
CamelCase or PascalCase conventions for class names and we could do the same 
for C++ (and many projects are doing it). However, this causes some other 
issues

* neither Camel- nor PascalCase conventions are used in the STL or anywhere 
  else in the C or C++ standard libraries.
* it leads to inconsistencies has it is unclear why, for instance, a type is 
  named :cpp:class:`DataSet` and the other :cpp:type:`uint8_t`.
  
.. admonition:: Conclusion

   We should use `_t` for the following additional reasons
   
   * the meaning of the `_t` suffix is well known among C and C++ programmers.
   * `_t` itself has no other meaning than indicating that the name 
     refers to a type (class). From :cpp:class:`dataset_t` it is still 
     clear that the type describes a dataset within an HDF5 file.
   * it is **consistent** with what is already around.
   * using `_type` as some parts of the STL do is difficult as *type* itself
     is an English noun. Is :cpp:class:`dataset_type` describing a single 
     dataset or is it maybe an enumeration distinguishing between different
     types of datasets?     


Indentation
===========

We use 4 blanks for indentation no tab characters. Every block should be
indented except for nested namespaces. 

.. code-block:: cpp

    namespace first{
    namespace second{  //no indentation required here


        void function(int arg)
        {
            //add here some code
        }
        
    

    } // end of namespace second
    } // end of namespace first


.. admonition:: Rational

    * 4 characters indicate a new block clear enough without reducing the 
      number of available characters per line too much
    * tab characters are no good choice as their size depends on the local
      configuration of the users text editor. 

Bracketing style
================

This is most probably one of the most controversial points. There is a 
nice Wiki page with `indentation styles`_ available. 
I personally go with the BSD style 

.. code-block:: cpp

    while(true)
    {

    }

where the opening bracket is placed on a new line. 

.. note::

    This will most probably require some discussion. 


Maximum line length
===================

Lines must not exceed a maximum number of 80 characters. 

.. admonition:: Rational

    Though some people may claim that the times of 80 character displays are
    gone (I totally agree with  this) there is another good reason why to limit 
    the number of character per line: **it is simpler to read!!**
    
    
Comments
========

.. todo::

    Under construction


.. _Ada Style Guide: https://en.wikibooks.org/wiki/Ada_Style_Guide
.. _indentation styles: https://en.wikipedia.org/wiki/Indent_style#Styles
