#-----------------------------------------------------------------------------
# Define Sources, one file per application
#-----------------------------------------------------------------------------
set (examples
    h5ex_d_alloc.c
    h5ex_d_checksum.c
    h5ex_d_chunk.c
    h5ex_d_compact.c
    h5ex_d_extern.c
    h5ex_d_fillval.c
    h5ex_d_gzip.c
    h5ex_d_hyper.c
    h5ex_d_nbit.c
    h5ex_d_rdwr.c
    h5ex_d_soint.c
    h5ex_d_transform.c
    h5ex_d_unlimmod.c
    h5ex_d_shuffle.c
    h5ex_d_sofloat.c
    h5ex_d_unlimadd.c
    h5ex_d_unlimgzip.c
)
if (HDF5_ENABLE_SZIP_SUPPORT)
  set (examples ${examples} h5ex_d_szip.c)
endif ()
