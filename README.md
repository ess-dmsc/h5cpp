# C++ wrapper for the HDF5 C-library

*h5cpp* is a new C++ wrapper for HDF5s C-API. 

## Motivation

HDF5 is a powerful binary file format. There is virtually nothing that cannot 
be stored within an HDF5 file. To read and write data from and to an HDF5 file
you can either use the C-API or one of the wrappers for a scripting language 
(for Python there is for instance [h5py](http://www.h5py.org/) or 
[pytables](http://www.pytables.org/)). However, to keep their interfaces 
simple, many of these wrappers do not provide the full functionality HDF5 
has to offer. If you want to use all features available the C-API is most 
probably the safest way to go. 

*h5cpp* wants to provide both, an easy to use modern C++ interface but at the 
same time give you access to the full functionality HDF5 has to offer. 


### Complete and domain agnostic 

Many HDF5 wrappers which are currently around have to major issues:

1. they do not provide the full functionality of the C-API
2. they are specifically made for a particular field of application

Our goal is to keep *h5cpp* as much as application agnostic as possible and 
provide the full functionality of the C-API. 

### Easy to use 

HDF5 is a rather powerful file format and thus the C-API is rather complex. 
*h5cpp*s approach to this degree of complexity can be best described by a quote 
of [Alan Kay](http://startupquote.com/post/5626579141)

    Simple things should be simple, complex things should be possible.
    
That's what we try to achieve and hopefully we succeeded in it. 

### Support for major platforms 

We currently support the following operating systems 

* Linux 
* Windows 
* OSX

Since we are using `cmake` to build *h5cpp* and also provide a `cmake` package 
for the library, using it should be the same on each of these platforms.  

## Installation and using it

See the [online documentation](https://ess-dmsc.github.io/h5cpp/index.html) for 
more on this.

