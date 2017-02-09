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

Naming conventions
==================

* all class and type names are lowercase
* type and class names end with an ``_t``
* the `_` underscore is used to separate words

Some examples would be

.. code-block:: cpp

    using dims_t = std::vector<hsize_t>;

    class dataset_t
    {

    };


Rational
--------

This convention is quite contrary to the far more common Pascal- and Camelcase
convention used today. However, there are, in my opinion, good reasons to
prefer the above rules 

* all lower case is simpler to type 
* the underscore is much closer to a blank an separates word more clearly
* this convention is closer to what programmers are used to from the C++
  standard  library.


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

Rational
--------

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

Rational
--------

Though some people may claim that the times of 80 character displays are gone
(I totally agree with  this) there is another good reason why to limit 
the number of character per line: **it is simpler to read!!**


.. _Ada Style Guide: https://en.wikibooks.org/wiki/Ada_Style_Guide
.. _indentation styles: https://en.wikipedia.org/wiki/Indent_style#Styles
