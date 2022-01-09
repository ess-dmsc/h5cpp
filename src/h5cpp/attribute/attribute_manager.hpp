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
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Sep 14, 2017
//
#pragma once

#include <string>
#include <h5cpp/attribute/attribute.hpp>
#include <h5cpp/core/types.hpp>
#include <h5cpp/core/windows.hpp>
#include <h5cpp/core/iterator_config.hpp>
#include <h5cpp/datatype/factory.hpp>
#include <h5cpp/dataspace/scalar.hpp>
#include <h5cpp/dataspace/simple.hpp>
#include <h5cpp/property/attribute_creation.hpp>

//
// forward declarations
//
namespace hdf5 {
namespace node {

class Node;

} // namespace node
} // namespace hdf5

namespace hdf5 {
namespace attribute {

//forward declaration
class AttributeIterator;

//!
//! \brief provides STL interface for attributes
//!
//! The AttributeManager class provides an STL compliant interface to access
//! attribute attached to a Node.
//!
class DLL_EXPORT AttributeManager
{
  public:
    AttributeManager() = delete;

    //!
    //! \brief constructor
    //!
    //! Creates a new instance of AttributeManager which must be attached to
    //! a Node instance.
    //!
    //! \throws std::runtime_error in case of a failure
    //! \param node reference to the parent node of the manager
    //!
    AttributeManager(node::Node &node);

    //!
    //! \brief copy constructor
    //!
    //! Use the compiler provided default implementation here.
    //!
    AttributeManager(const AttributeManager &manager) = default;

    //!
    //! \brief get attribute by index
    //!
    Attribute operator[](size_t index) const;

    //!
    //! \brief get attribute by name
    //!
    Attribute operator[](const std::string &name) const;

    //!
    //! \brief get number of attributes
    //!
    size_t size() const;

    //!
    //! \brief remove attribute by name
    //!
    void remove(const std::string &name) const;

    //!
    //! \brief remove attribute by index
    //!
    //! \throw std::runtime_error in case of a failure
    //!
    //! \pre `index` must be < size()
    //!
    void remove(size_t index) const;

    //!
    //! \brief check existence
    //!
    //! Returns true if an attribute of given name exists. Otherwise false
    //! is returned.
    //!
    bool exists(const std::string &name) const;

    //!
    //! \brief rename an attribute
    //!
    //! \throws std::runtime_error in case of a failure
    //! \param old_name old name of the attribute
    //! \param new_name new name of the attribute
    //!
    void rename(const std::string &old_name,const std::string &new_name) const;

    //!
    //! \brief create an attribute
    //!
    //! This is the most generic method to create attributes.
    //! See the template method below for more simple construction.
    //!
    Attribute create(const std::string &name,
                     const datatype::Datatype &datatype,
                     const dataspace::Dataspace &dataspace,
                     const property::AttributeCreationList &acpl =
                           property::AttributeCreationList()) const;

    //!
    //! \brief create scalar attribute
    //!
    //! Create a scalar attribute of given name. The datatype is determined
    //! from the templat parameter.
    //!
    //! \throws std::runtime_error in case of an error
    //! \tparam T element data type of the attribute
    //! \param name the name of the attribute
    //! \param acpl attribute creation property list
    //! \return instance of the newly created attribute
    //!
    template<typename T>
    Attribute create(const std::string &name,
                     const property::AttributeCreationList &acpl =
                           property::AttributeCreationList()) const;

    //!
    //! \brief create a multidimensional attribute
    //!
    //! Create a multidimensional attribute of given name and shape. The
    //! datatype is derived from the template parameter.
    //!
    //! \throws std::runtime_error in case of a failure
    //! \tparam T element data type
    //! \param name the name for the attribute
    //! \param shape the number of elements along each dimension
    //! \param acpl attribute creation property list
    //! \return instance of the newly created attribute
    //!
    template<typename T>
    Attribute create(const std::string &name,const Dimensions &shape,
                     const property::AttributeCreationList &acpl =
                           property::AttributeCreationList()) const;

    //!
    //! \brief create a new attribute of a given value
    //!
    //! This is a convenience method to create a new attribute with a given
    //! value. Technically this is a create() including a subsequent call
    //! to write.
    //!
    //! \code
    //! Node n = ....;
    //! n.attributes.create_from("date","12-03-2017");
    //! \endcode
    //!
    //! \throws std::runtime_error in case of a failure
    //! \param name the name of the attribute
    //! \param value reference to the new value
    //! \return new instance of Attribute
    //!
    template<typename T>
    Attribute create_from(const std::string &name,const T &value);

    //!
    //! \brief get iterator configuration
    //!
    //! Use this method to get a reference to the iterator configuration for
    //! the attributes of a  node.
    //! \return reference to iterator configuration
    //!
    IteratorConfig &iterator_config() noexcept;
    const IteratorConfig &iterator_config() const noexcept;

    //!
    //! \brief get parent node
    //!
    //! Return a reference to the parent node of the manager instance.
    //!
    const node::Node &node() const noexcept;

    //!
    //! \brief get iterator to first attribute
    //!
    AttributeIterator begin() const;

    //!
    //! \brief get iterator to last+1 attribute
    //!
    AttributeIterator end() const;

  private:
    node::Node &node_;
    IteratorConfig iter_config_;


};

template<typename T>
Attribute AttributeManager::create(const std::string &name,
                                   const property::AttributeCreationList &acpl) const
{
  hdf5::datatype::DatatypeHolder mem_type_holder;
  dataspace::Scalar space;

  return this->create(name,mem_type_holder.get<T>(),space,acpl);
}

template<typename T>
Attribute AttributeManager::create(const std::string &name,
                                   const Dimensions &shape,
                                   const property::AttributeCreationList &acpl) const
{
  hdf5::datatype::DatatypeHolder mem_type_holder;
  dataspace::Simple space(shape);

  return create(name,mem_type_holder.get<T>(),space,acpl);

}

template<typename T>
Attribute AttributeManager::create_from(const std::string &name,const T &value)
{
  hdf5::datatype::DatatypeHolder mem_type_holder;
  auto space = dataspace::create(value);

  Attribute a = create(name,mem_type_holder.get<T>(),space);
  a.write(value);
  return a;
}

} // namespace attribute
} // namespace hdf5
