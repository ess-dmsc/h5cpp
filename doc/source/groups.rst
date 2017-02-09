===================
Working with groups
===================

.. code-block:: cpp

    h5::group g = root_group.create("new_group",....);

Need to find a good way how to handle group creation property lists. 

Groups should provide a STL compliant iterator interface 

.. code-block:: cpp

    std::vector<h5::dataset> datasets; 
    h5::group g = ....;

    std::copy_if(g.begin(),g.end(),std::back_inserter(datasets),
                 [](const auto &o) { return h5::is_dataset(o); });

