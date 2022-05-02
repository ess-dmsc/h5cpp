.. _advanced-cpp-datastructures:

============================
C++ data structures and HDF5
============================

.. todo::

    Add here some content about C++ data structures and about the principal
    difficulties with them when working with HDF5.

The HDF5 library is a C-library and thus it is primarily intended to be
used with C-style data structures. These are

* simple scalar values of a primitive type
* `struct` instances
* pointers and array of pointers.

C++ provides a far more richer set of data structures including for instances
classes. But also more elaborate compound types could be built in particular
when making use of STL containers.

STL containers
==============

Recall now the concept of the memory storage introduced in the users guide
(see :ref:`design-overview` for details). Except for three situations
where which will be covered also in the advanced chapter of the
documentation HDF5 always assumes that the memory storage from which it
reads or to which it writes data is contiguous and can be adressed linearly.
The only two data structures in the STL which satisfy this requirement are the
two templates

* :cpp:class:`std::vector`
* :cpp:class:`std::array`.

In this case the :cpp:func:`data` method provided by both templates would be
already sufficient for low level HDF5 IO as the pointer returned by this
method would reference a block of memory that entirely satisifies the
requirements for memory storage.

However, already defining a vector of vectors would make no longer be
compliant with a memor storage. Cnsider the following example

.. code-block:: cpp

    using BinType    = unsigned int;
    using MCAReadout = std::vector<BinType>;
    using MCAStack = std::vector<MCAReadout>;

    static const int nbins = 1024;
    static const int nmcas = 100;

    using namespace hdf5;

    // create the dataset
    node::Gruop data_group = ....;
    auto file_type = datatype::create<BinType>;
    dataspace::Simple file_space({nmcas,nbins})
    node::Dataset dset = data_gruop.create_dataset("mcas",file_type,file_space);

    // create the data
    MCAStack mcas;
    MCAReader reader;
    std::generate_n(std::back_inserter(mcas),nmcas,reader);


    //now lets try to write the data
    dset.write(mcas);
