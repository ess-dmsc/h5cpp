#!/bin/bash
if [ "$1" = "shared" ]; then
	echo "H5CPP_SHARED=True" >> $GITHUB_ENV
else
	echo "H5CPP_SHARED=False" >> $GITHUB_ENV
fi
if [ "$2" = "boost" ]; then
	echo "H5CPP_WITH_BOOST=True" >> $GITHUB_ENV
else
	echo "H5CPP_WITH_BOOST=False" >> $GITHUB_ENV
fi
if [ "$3" = "mpi" ]; then
	echo "H5CPP_WITH_MPI=True" >> $GITHUB_ENV
else
	echo "H5CPP_WITH_MPI=False" >> $GITHUB_ENV
fi
if [ "$4" = "clang14-libc++" ] || [ "$4" = "clang14-libstdc++" ] ; then
	echo "CC=clang-14" >> $GITHUB_ENV
	echo "CXX=clang++-14" >> $GITHUB_ENV
fi
