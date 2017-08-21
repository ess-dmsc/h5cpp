=====================
Working with datasets
=====================

Dataset creation
================

.. todo::

    There will be something like a :cpp:func:`create_dataset` method for 
    :cpp:class:`group_t`. However, the signature is not entirely determined
    yet. 

The only thing we have right now is some pseudocode

.. code-block:: cpp

    dataset_t dset = group.create_dataset(...);

Extending the size of a dataset
===============================

Provided that the dataset has a chunked layout one can alter its size.


.. todo:: 

    Not determined how the interface should look like. Maybe we should try to 
    stick to the API names as close as possible in order to avoid confusion 
    for people how know the C-API.

Reading and writing data
========================

To read and write an entire dataset use the :cpp:func:`read` and
:cpp:func:`write` methods (see also :ref:`design-read-write`). 


.. code-block:: cpp

    dataset_t dset = group["temperatures"];

    std::vector<double> temperatures;
    dset.read(temperatures);

    //or for writing
    dset.write(temperatures)



Partial IO
----------

In many cases the the total amount of data stored in a single dataset might be
to large to fit in your machines memory. In such situations we have to read 
the data in smaller pieces. This can be done using partial IO. 

.. code-block:: cpp

    dataset_t dset = group["images"]; 
    dims_t cdims   = dset.current_dimensions();

    std::vector<uint16> frame(cdims[1]*cdims[2]);

    index_range_t rx(0,cdims[1]), ry(0,cdims[2]);

    for(size_t frame_index=0;frame_index<cdims[0];frame_index++)
    {

        //the dataset_t::operator()(....) uses a variadic template to 
        //gather all the indexes and returns an instance of hyperslab_t 
        //which by itself provides the read and write methods to 
        //read and write data to the selection determined by the hyperslab.
        dset(frame_index,r1,r2).read(frame);

        //do something with the frame
    }



Dataset container adapter
=========================

To simplify the above concept of looping along a particular dimension of 
a dataset one could use the :cpp:class:`container_adapter`

.. code-block:: cpp

    class container_adapter_t
    {
        public:
            using const_iterator = ...;

            hyperslab_t operator[](size_t index) const;
            hyperslab_t at(size_t index) const;

            size_t size() const;

            template<
                     typename T,
                     typename std::enable_if<!is_container<T>::value,int>::type=0
                    >
            void push_back(const T &value);

            template<
                     typename T,
                     typename = std::enable_if_t<is_container<T>::value>
                    >
            void push_back(const T &value);

            const_iterator begin() const;
            const_iterator end() const;
    };

The container adapter for datasets provides an STL compliant container
interface for a multidimensional dataset along one dimension. 

Reading data from 

.. code-block:: cpp

    using frame_t = std::vector<uint16_t>;

    h5::dataset_t d = group["detector_data"];

    //container adapter for dataset d along the first dimension
    container_adapter_t frames(d,0);
    frame_t frame;

    for(auto slab: frames)
    {
        //process the frame
        slab.read(frame);
    }

Appending data
--------------

The :cpp:class:`container_adapter` template also provides a
:cpp:func:`push_back` method.

.. code-block:: cpp

    using frame_t = std::vector<uint32_t>;

    h5::dataset_t d = group["detector_data"];
    container_adapter_t frames(d,0);
    frame_t data;

    while(measurement_running)
    {
        data = .....; //read some data
        frames.push_back(data);  //store data in the dataset
    }



Stream IO
=========

It would be nice to have something like IO streams for datasets. 

.. code-block:: cpp

    h5::dataset_t dataset = group["temperatures"]; 

    //create a new stream along the first dimension of a dataset
    h5::dataset_stream_t stream(dataset,0);

    while(measurement_running)
    {
        double temperature = read_temperature();
        stream<<temperature;
    }

Or the other way around for reading 

.. code-block:: cpp

    h5::dataset_t datset = group["temperature"];
    h5::dataset_stream_t stream(dataset,0);

    double temperature = 0.0;
    while(!stream.eof())
    {
        stream>>temperature;
    }

A possible implementation could be done based upon the
:cpp:class:`container_adapter_t` 

.. code-block:: cpp

    class dataset_stream_t
    {
        private:
            container_adapter _adapter;
            size_t _position;
        public:
            dataset_stream_t();

    };


