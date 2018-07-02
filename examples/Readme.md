# Building the examples

In order to build the examples copy this directory somewhere to your 
filesystem where you have sufficient permissions and create a build 
directory and call *cmake*

```bash
$ mkdir examples_build
$ cd examples_build
$ cmake -DCMAKE_BUILD_TYPE=Release -Dh5cpp_DIR=<PATH TO CMAKE PACKAGE FILE DIRECTORY> ../examples
```

a subsequent *make* should build the examples

```bash
$ make
```

| Examples         | source files

