//
// (c) Copyright 2017 DESY, ESS
//
// This file is part of h5cpp
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
//
// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty ofMERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the
// Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor
// Boston, MA  02110-1301 USA
//
// ===========================================================================
//
// Created on: Feb 12, 2016
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#ifdef _MSC_VER
	#ifdef DLL_BUILD
		#define DLL_EXPORT __declspec(dllexport)
	#else
		#define DLL_EXPORT __declspec(dllimport)
	#endif
#else 
	#define DLL_EXPORT
#endif

#ifdef _MSC_VER
#include <BaseTsd.h>

using ssize_t = SSIZE_T;

#endif

