import pni.io.nx.h5 as nx

fl = nx.create_file("pniio_test_boolattr.h5", True)
rt = fl.root()
rt.attributes.create("bool_true", "bool")[...] = True
rt.attributes.create("bool_false", "bool")[...] = False
rt.attributes.create("bool_array", "bool", shape=[4])[...] \
    = [False, True, True, False]
rt.create_field("ds_bool_scalar_false", "bool")[...] = False
rt.create_field("ds_bool_scalar_true", "bool")[...] = True
rt.create_field("ds_bool_array", "bool", [4], [4])[...] \
    = [False, True, True, False]
fl.close()
