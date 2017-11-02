# h5cpp
C++ wrapper for the HDF5 C-library

*h5cpp* is a new C++ wrapper for HDF5s C-API. Unlike many others it 
strives for 

* completenes
* independent of a particular application domain 
* support for *current* major OS platforms (Windows, Linux, OXS)
* easy to use.

##Motivation

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

## Installation and using it

See the [online documentation](https://ess-dmsc.github.io/h5cpp/index.html) for 
more on this.

