# Building the library with MESON

** WARNING **: this is a highly experimental feature. Do not use this in production environments.

## Default build

```{bash}
$ mkdir builddir
$ meson setup builddir
$ cd builddir
$ ninja
```


## Building with MPI support

All steps are the same as for the default build with the exception of the `setup` step.
In order to enable and MPI build the `with-mpi` option must be passed ot `meson` like this:

```{bash}
$ meson setup -Dwith-mpi=true builddir
```