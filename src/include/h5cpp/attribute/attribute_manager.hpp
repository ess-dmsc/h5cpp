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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Sep 14, 2017
//
#pragma once

#include <string>
#include "attribute.hpp"
#include "../types.hpp"
#include "../windows.hpp"
#include "../iterator_config.hpp"
#include "../datatype/factory.hpp"
#include "../dataspace/scalar.hpp"
#include "../dataspace/simple.hpp"
#include "../property/attribute_creation_list.hpp"

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

class DLL_EXPORT AttributeManager
{
  public:
    AttributeManager() = delete;
    AttributeManager(node::Node &node);
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
    //! \param old _name the old name of the attribute
    //! \param the new name of the attribute
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
    //! \return instance of the newly created attribute
    //!
    template<typename T>
    Attribute create(const std::string &name,const Dimensions &shape,
                     const property::AttributeCreationList &acpl =
                           property::AttributeCreationList()) const;

    IteratorConfig &iterator_config() noexcept;
    const IteratorConfig &iterator_config() const noexcept;
    const node::Node &node() const;

    AttributeIterator begin() const;
    AttributeIterator end() const;

  private:
    node::Node &node_;
    IteratorConfig iter_config_;


};

template<typename T>
Attribute AttributeManager::create(const std::string &name,
                                   const property::AttributeCreationList &acpl) const
{
  auto type = datatype::create<T>();
  dataspace::Scalar space;

  return this->create(name,type,space,acpl);
}

template<typename T>
Attribute AttributeManager::create(const std::string &name,
                                   const Dimensions &shape,
                                   const property::AttributeCreationList &acpl) const
{
  auto type = datatype::create<T>();
  dataspace::Simple space(shape);

  return create(name,type,space,acpl);

}

} // namespace attribute
} // namespace hdf5
