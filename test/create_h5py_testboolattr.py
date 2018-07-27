import h5py

f = h5py.File("h5py_test_boolattr.h5", "w")

f.attrs["bool_scalar_true"] = True
f.attrs["bool_scalar_false"] = False
f.attrs["bool_simple_true"] = [True]
f.attrs["bool_simple_false"] = [False]
f.attrs["bool_array"] = [False, True, True, False]
f.create_dataset("ds_bool_scalar_true",data=True)
f.create_dataset("ds_bool_scalar_false",data=False)
f.create_dataset("ds_bool_simple_true",data=[True])
f.create_dataset("ds_bool_simple_false",data=[False])
f.create_dataset("ds_bool_array", data=[False, True, True, False])
f.close()
