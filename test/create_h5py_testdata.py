import h5py
import numpy

f = h5py.File("h5py_test_data.h5","w")
d = f.create_dataset("fix_string_scalar",shape=(1,),dtype="S30")
d[...] = "hello from h5py"

d = f.create_dataset("fix_string_array",shape=(2,3),dtype="S30")
data = numpy.array([["hello","world","this"],["is","a","test"]])
d[...] = data[...]
