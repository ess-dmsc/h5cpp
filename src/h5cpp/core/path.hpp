//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5cpp.
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
// ===========================================================================
//
// Authors:
//    Eugen Wintersberger <eugen.wintersberger@desy.de>
//    Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 24, 2017
//
#pragma once

#include <list>
#include <string>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {

//!
//! \brief path to a node object
//!
//! Every object within an HDF5 file can be addressed via a path. Such a path is a
//! list of link names separated by a slash /.
//! While HDF5s C-API uses a simple string to represent a path, the C++ wrapper
//! provides a class for this purpose.
//!
//! Though an HDF5 path look quit similar to an Unix filesystem path there is
//! one major difference: \c .. has no special meaning. On a Unix filesystem
//! \c .. would reference to the directory above the current one. In HDF5
//! \c .. simply means nothing. It would be even allowed to use \c .. as a
//! name for a group, dataset or committed datatype.
//!
class DLL_EXPORT Path
{
  public:
    using value_type = std::string;
    using iterator = std::list<value_type>::iterator;
    using const_iterator = std::list<value_type>::const_iterator;
    using reverse_iterator = std::list<value_type>::reverse_iterator;
    using const_reverse_iterator= std::list<value_type>::const_reverse_iterator;

    //!
    //! \brief default constructor
    //!
    //! After default construction is list of path elements is empty and the
    //! absolute path flag is set to false.
    //!
    Path();

    //!
    //! \brief constructor
    //!
    //! Construct a path from a string. We use an explicit constructor here
    //! to avoid accidental conversions.
    //!
    explicit Path(const std::string &str);

    //!
    //! \brief copy constructor
    //!
    Path(const Path &p) = default;

    explicit operator std::string() const
    {
      return to_string();
    }

    //!
    //! \brief return number of path elements
    //!
    size_t size() const;

    //!
    //! \brief const iterator to first path element
    //!
    const_iterator begin() const;

    //!
    //! \brief const iterator to last + 1 element
    //!
    const_iterator end() const;


    //@{
    //!
    //! \brief get reverse iterator
    //!
    //! rbegin() and rend() return the pair of reverse iterators for the path.
    //!
    //! \code
    //! Path p("/run/sensors/temperature");
    //! std::for_each(p.rbegin(),p.rend(),
    //!               [](const std::string &name) { std::cout<<name<<" "; });
    //! //output: temperature sensors run
    //! \endcode
    //!
    //! \return instance of a const reverse iterator
    //!
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;
    //@}

    //!
    //! \brief returns true if a path is absolute
    //!
    //! A path is considered absolute if its first element references the
    //! root node. This is indicated by a leading \c / of the path string.
    //!
    //! \code
    //! hdf5::Path p("/log/data");
    //! if(p.absolute())
    //! {
    //!    std::cout<<"got absolute path"<<std::endl;
    //! }
    //! \endcode
    //!
    //! \return true if path is absolute, false otherwise
    //!
    bool absolute() const noexcept;

    //!
    //! \brief set a path to be absolute
    //!
    //! Use this flag to set or unset the absolut flag.
    //!
    //! \code
    //! Path p("data/modules");
    //! std::cout<<p<<std::endl; // output: data/modules
    //! p.absolute(true);
    //! std::cout<<p<<std::endl; // output: /data/modules
    //! p.absolute(false);
    //! std::cout<<p<<std::endl; // output: data/modules
    //! \endcode
    //!
    //! \param value boolean value deciding whether a path is absolute or not
    //!
    void absolute(bool value) noexcept;

    //!
    //! \brief true if the path refers to the root group
    //!
    //! A path is considered to reference the root group if the list
    //! of elements is empty but the absolute path flag is set.
    //!
    bool is_root() const;

    //!
    //! \brief get object name from a path
    //!
    //! The object name is the last element of a path. In the case
    //! of the root group it is empty.
    //!
    std::string name() const;

    //!
    //! \brief get parent path
    //!
    //! This is basically the path with the last component stripped of.
    //!
    Path parent() const;

    //!
    //! \brief append a path to this instance
    //!
    //! Adding path p to this instance. Basically this
    //!
    //! \code
    //! hdf5::Path base_path("/entry/instrument");
    //! hdf5::Path detector_transforms("detector/transformations");
    //! hdf5::Path p = base_path.append(detector_transforms);
    //! std::cout<<p<<std::endl;
    //! //output: /entry/instrument/detector/transformations
    //! \endcode
    //!
    void append(const Path& p);

    Path relative_to(const Path& base) const;

    Path& operator+=(const Path &other);

    //!
    //! \brief checks two paths for equality
    //!
    //! Two paths are considered equal if each of their elements is
    DLL_EXPORT friend bool operator==(const Path &lhs, const Path &rhs);
    DLL_EXPORT friend Path common_base(const Path& lhs, const Path& rhs);

  private:
    bool absolute_;
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
    std::list<std::string> link_names_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

    void from_string(const std::string &str);
    std::string to_string() const;

    void sanitize();
};


DLL_EXPORT bool operator!=(const Path &lhs, const Path &rhs);

DLL_EXPORT Path operator+(const Path &lhs,const Path &rhs);

DLL_EXPORT Path operator+(const std::string &link_name,const Path &path);
DLL_EXPORT Path operator+(const Path &path,const std::string &link_name);

DLL_EXPORT std::ostream &operator<<(std::ostream &stream,const Path &path);

} // namespace hdf5
