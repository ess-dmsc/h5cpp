===============
The big picture
===============


.. figure:: images/package_overview.png
   :align: center
   :width: 75%
   
All objects reside in the toplevel namespace :cpp:any:`h5`. There are some
subnamespaces which contain special functions and classes usually not required
for normal operations. 

The following namespaces are available

+------------------------------+----------------------------------------+
| namespace                    | description                            |
+==============================+========================================+
| :cpp:any:`h5`                | the top-level namespace of the library |
+------------------------------+----------------------------------------+
| :cpp:any:`h5::id`            | classes and functions dealing with ID  |
|                              | management                             |
+------------------------------+----------------------------------------+
| :cpp:any:`h5::object`        | classes and functions for general      |
|                              | object management                      |
+------------------------------+----------------------------------------+
| :cpp:any:`h5::property_list` | property list classes and related      |
|                              | functions                              |
+------------------------------+----------------------------------------+
| :cpp:any:`h5::attribute`     | attribute related classes and          |
|                              | functions                              |
+------------------------------+----------------------------------------+
| :cpp:any:`h5::link`          | classes and functions related to links |
+------------------------------+----------------------------------------+

Classes which are used in everyday business are directly placed below the 
top-level namespace :cpp:any:`h5`.

Ok let's give this a try again. Feels much better. No more slow editing 
window. 