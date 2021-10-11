# Building h5cpp with meson

In the simplest case just use 

```{bash}
$ meson setup builddir
$ cd builddir
$ ninja all
```

and to run the tests

```{bash}
$ ninja test
```