import h5py
import numpy as np

f = h5py.File("h5py_test_string_attributes.h5", "w")


fix_size_nullterm_tid = h5py.h5t.C_S1.copy()
fix_size_nullterm_tid.set_size(4)
fix_size_nullterm_tid.set_strpad(h5py.h5t.STR_NULLTERM)
f.attrs.create(
    "fixed_size_string_nullterm_full", "123", dtype=h5py.Datatype(fix_size_nullterm_tid)
)
f.attrs.create(
    "fixed_size_string_nullterm_trunc",
    "1234",
    dtype=h5py.Datatype(fix_size_nullterm_tid),
)
f.attrs.create(
    "fixed_size_string_nullterm_part", "1", dtype=h5py.Datatype(fix_size_nullterm_tid)
)
f.attrs.create(
    "fixed_size_string_nullterm_empty", "", dtype=h5py.Datatype(fix_size_nullterm_tid)
)


fix_size_nullpad_tid = h5py.h5t.C_S1.copy()
fix_size_nullpad_tid.set_size(4)
fix_size_nullpad_tid.set_strpad(h5py.h5t.STR_NULLPAD)
f.attrs.create(
    "fixed_size_string_nullpad_full", "1234", dtype=h5py.Datatype(fix_size_nullpad_tid)
)
f.attrs.create(
    "fixed_size_string_nullpad_trunc",
    "12345",
    dtype=h5py.Datatype(fix_size_nullpad_tid),
)
f.attrs.create(
    "fixed_size_string_nullpad_part", "1", dtype=h5py.Datatype(fix_size_nullpad_tid)
)
f.attrs.create(
    "fixed_size_string_nullpad_empty", "", dtype=h5py.Datatype(fix_size_nullpad_tid)
)

fix_size_spacepad_tid = h5py.h5t.C_S1.copy()
fix_size_spacepad_tid.set_size(4)
fix_size_spacepad_tid.set_strpad(h5py.h5t.STR_SPACEPAD)
f.attrs.create(
    "fixed_size_string_spacepad_full",
    "1234",
    dtype=h5py.Datatype(fix_size_spacepad_tid),
)
f.attrs.create(
    "fixed_size_string_spacepad_trunc",
    "12345",
    dtype=h5py.Datatype(fix_size_spacepad_tid),
)
f.attrs.create(
    "fixed_size_string_spacepad_part", "1", dtype=h5py.Datatype(fix_size_spacepad_tid)
)
f.attrs.create(
    "fixed_size_string_spacepad_empty", "", dtype=h5py.Datatype(fix_size_spacepad_tid)
)
