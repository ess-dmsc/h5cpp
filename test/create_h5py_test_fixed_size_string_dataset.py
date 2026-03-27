import h5py
import numpy

f = h5py.File("h5py_test_fixed_size_string_datasets.h5","w")

fix_size_nullterm_tid = h5py.h5t.C_S1.copy()
fix_size_nullterm_tid.set_size(4)
fix_size_nullterm_tid.set_strpad(h5py.h5t.STR_NULLTERM)

f.create_dataset(
  "fixed_size_string_nullterm_full",
  shape=(1,),
  data=["123"],
  dtype=h5py.Datatype(fix_size_nullterm_tid))

f.create_dataset(
    "fixed_size_string_nullterm_trunc",
    shape=(1,),
    data=["1234"],
    dtype=h5py.Datatype(fix_size_nullterm_tid),
)

f.create_dataset(
    "fixed_size_string_nullterm_part",
    shape=(1,),
    data=["1"],
    dtype=h5py.Datatype(fix_size_nullterm_tid)
)

f.create_dataset(
    "fixed_size_string_nullterm_empty",
    shape=(1,),
    data=[""],
    dtype=h5py.Datatype(fix_size_nullterm_tid)
)


fix_size_nullpad_tid = h5py.h5t.C_S1.copy()
fix_size_nullpad_tid.set_size(4)
fix_size_nullpad_tid.set_strpad(h5py.h5t.STR_NULLPAD)
f.create_dataset(
    "fixed_size_string_nullpad_full",
    shape=(1,),
    data=["1234"],
    dtype=h5py.Datatype(fix_size_nullpad_tid)
)
f.create_dataset(
    "fixed_size_string_nullpad_trunc",
    shape=(1,),
    data=["12345"],
    dtype=h5py.Datatype(fix_size_nullpad_tid),
)
f.create_dataset(
    "fixed_size_string_nullpad_part",
    shape=(1,),
    data=["1"],
    dtype=h5py.Datatype(fix_size_nullpad_tid)
)
f.create_dataset(
    "fixed_size_string_nullpad_empty",
    shape=(1,),
    data=[""],
    dtype=h5py.Datatype(fix_size_nullpad_tid)
)

fix_size_spacepad_tid = h5py.h5t.C_S1.copy()
fix_size_spacepad_tid.set_size(4)
fix_size_spacepad_tid.set_strpad(h5py.h5t.STR_SPACEPAD)
f.create_dataset(
    "fixed_size_string_spacepad_full",
    shape=(1,),
    data=["1234"],
    dtype=h5py.Datatype(fix_size_spacepad_tid),
)
f.create_dataset(
    "fixed_size_string_spacepad_trunc",
    shape=(1,),
    data=["12345"],
    dtype=h5py.Datatype(fix_size_spacepad_tid),
)
f.create_dataset(
    "fixed_size_string_spacepad_part",
    shape=(1,),
    data=["1"],
    dtype=h5py.Datatype(fix_size_spacepad_tid)
)
f.create_dataset(
    "fixed_size_string_spacepad_empty",
    shape=(1,),
    data=[""],
    dtype=h5py.Datatype(fix_size_spacepad_tid)
)
