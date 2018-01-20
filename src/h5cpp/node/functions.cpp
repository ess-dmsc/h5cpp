//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5pp.
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
// Author: Martin Shetty <martin.shetty@esss.se>
// Created on: Sep 9, 2017
//
#include <sstream>
#include <h5cpp/node/functions.hpp>

namespace hdf5 {
namespace node {

void copy(const Node &source, const Group& base, const Path &relative_path,
          const property::ObjectCopyList &ocpl,
          const property::LinkCreationList &lcpl)
{
  //what if relative_path is actually absolute?

  bool exists = false;
  try
  {
    exists = base.links.exists(static_cast<std::string>(relative_path));
  }
  catch (...)
  {
    std::stringstream ss;
    ss << "node::copy failed. "
       << base.link() << " / " << relative_path << " already exists!";
    std::throw_with_nested(std::runtime_error(ss.str()));
  }

  if (exists)
  {
    std::stringstream ss;
    ss << "node::copy failed. "
       << base.link() << " / " << relative_path << " already exists!";
    throw std::runtime_error(ss.str());
  }

  if (0 > H5Ocopy(static_cast<hid_t>(source.link().parent()), //parent
                  source.link().path().name().c_str(),        //object name
                  static_cast<hid_t>(base),                   //destination parent
                  static_cast<std::string>(relative_path).c_str(), //destination name
                  static_cast<hid_t>(ocpl),                   //object copy property list
                  static_cast<hid_t>(lcpl)))                  //link creation property list
  {
    std::stringstream ss;
    ss << "node::copy failed. Could not copy "
       << source.link() << " to "
       << base.link() << " / " << relative_path;
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

void copy(const Node &source, const Group& destination,
          const property::ObjectCopyList &ocpl,
          const property::LinkCreationList &lcpl)
{
  //what if rel_path is actually absolute?
  auto name = source.link().path().name(); //this feels awkward
  bool exists = false;

  try
  {
    exists = destination.links.exists(name);
  }
  catch(...)
  {
    std::stringstream ss;
    ss << "node::copy failed. "
       << destination.link() << " / " << name << " already exists!";
    std::throw_with_nested(std::runtime_error(ss.str()));
  }

  if (exists)
  {
    std::stringstream ss;
    ss << "node::copy failed. "
       << destination.link() << " / " << name << " already exists!";
    throw std::runtime_error(ss.str());
  }


  if (0 > H5Ocopy(static_cast<hid_t>(source.link().parent()), //parent
                  name.c_str(),                               //object name
                  static_cast<hid_t>(destination),            //destination parent
                  name.c_str(),                               //...same name
                  static_cast<hid_t>(ocpl),                   //object copy property list
                  static_cast<hid_t>(lcpl)))                  //link creation property list
  {
    std::stringstream ss;
    ss << "node::copy failed. Could not copy "
       << source.link() << " to "
       << destination.link() << " / " << name;
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

void remove(const Node &object,
            const property::LinkAccessList &lapl)
{
  remove(object.link().parent(), Path(object.link().path().name()), lapl);
}

void remove(const Group &base, const Path &object_path,
            const property::LinkAccessList &lapl)
{
  bool exists = false;
  try
  {
    exists = base.links.exists(static_cast<std::string>(object_path));
  }
  catch(...)
  {
    std::stringstream ss;
    ss << "node::remove failed. "
       << base.link() << " / " << object_path << " does not exist.";
    std::throw_with_nested(std::runtime_error(ss.str()));
  }

  if (!exists)
  {
    std::stringstream ss;
    ss << "node::remove failed. "
       << base.link() << " / " << object_path << " does not exist.";
    throw std::runtime_error(ss.str());
  }

  if (0 > H5Ldelete(static_cast<hid_t>(base),
                    static_cast<std::string>(object_path).c_str(),
                    static_cast<hid_t>(lapl)))
  {
    std::stringstream ss;
    ss << "node::remove failed. Could not remove"
       << base.link() << " / " << object_path;
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

void move(const Node &source,
          const Group &destination,
          const property::LinkCreationList &lcpl,
          const property::LinkAccessList &lapl)
{
  move(source,
       destination,
       Path(source.link().path().name()),
       lcpl, lapl);
}

void move(const Node &source,
          const Group &base,
          const Path &relative_path,
          const property::LinkCreationList &lcpl,
          const property::LinkAccessList &lapl)
{
  auto name = static_cast<std::string>(relative_path);

  bool exists = false;
  try
  {
    exists = base.links.exists(name);
  }
  catch (...)
  {
    std::stringstream ss;
    ss << "node::move failed. "
       << base.link() << " / " << name << " already exists!";
    std::throw_with_nested(std::runtime_error(ss.str()));
  }

  if (exists)
  {
    std::stringstream ss;
    ss << "node::move failed. "
       << base.link() << " / " << name << " already exists!";
    throw std::runtime_error(ss.str());
  }

  if (0 > H5Lmove(static_cast<hid_t>(source.link().parent()),
                  source.link().path().name().c_str(),
                  static_cast<hid_t>(base),
                  name.c_str(),
                  static_cast<hid_t>(lcpl),
                  static_cast<hid_t>(lapl)))
  {
    std::stringstream ss;
    ss << "node::move failed. Could not move "
       << source.link() << " to "
       << base.link() << " / " << relative_path;
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

void link(const boost::filesystem::path &target_file,
          const Path &target_path,
          const Group &link_base,
          const Path &link_path,
          const property::LinkCreationList &lcpl,
          const property::LinkAccessList &lapl)
{
  auto base = link_base;
  if (link_path.absolute())
    base = link_base.link().file().root();
  auto lpath = static_cast<std::string>(link_path);

  bool exists = false;
  try
  {
    exists = link_base.links.exists(lpath);
  }
  catch (...)
  {
    std::stringstream ss;
    ss << "node::link (external) failed. "
       << base.link() << " / " << link_path << " already exists!";
    std::throw_with_nested(std::runtime_error(ss.str()));
  }

  if (exists)
  {
    std::stringstream ss;
    ss << "node::link (external) failed. "
       << base.link() << " / " << link_path << " already exists!";
    throw std::runtime_error(ss.str());
  }

  if (0 > H5Lcreate_external(target_file.string().c_str(),
                             static_cast<std::string>(target_path).c_str(),
                             static_cast<hid_t>(base),
                             lpath.c_str(),
                             static_cast<hid_t>(lcpl),
                             static_cast<hid_t>(lapl)))
  {
    std::stringstream ss;
    ss << "node::link (external) failed. "
       << link_base.link() << " / " << link_path
       << " -> "
       << target_file << " / " << target_path;
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

void link(const Node &target,
          const Group &link_base,
          const Path &link_path,
          const property::LinkCreationList &lcpl,
          const property::LinkAccessList &lapl)
{
  //if target and link base are in a different file we create an
  //external link
  if (target.id().file_number() != link_base.id().file_number())
  {
    link(target.id().file_name(),
         target.link().path(),
         link_base, link_path, lcpl, lapl);
  }
  else
  {
    //we are in the same file - can create a symbolic link
    auto link_parent = link_path.parent();
    auto link_name   = link_path.name();

    //need to get the real base node for the link
    Node real_base_node = get_node(link_base,link_parent);
    if(real_base_node.type()!=Type::GROUP)
    {
      std::stringstream ss;
      ss<<"Node ["<<real_base_node.link().path()<<"] is not a group and thus,"
        <<" cannot be used as a base for link ["<<link_name<<"]!";
      throw std::runtime_error(ss.str());
    }

    if (0 > H5Lcreate_soft(
          static_cast<std::string>(target.link().path()).c_str(),
          static_cast<hid_t>(Group(real_base_node)),
          link_name.c_str(),
          static_cast<hid_t>(lcpl),
          static_cast<hid_t>(lapl)))
    {
      std::stringstream ss;
      ss << "node::link (soft) failed. "
         << link_base.link() << " / " << link_path
         << " -> "
         << target.link();
      error::Singleton::instance().throw_with_stack(ss.str());
    }
  }
}

Node get_node(const Group &base,const Path &node_path,const property::LinkAccessList &lapl)
{

  Group search_base(base);
  Path search_path(node_path);

  //if there is nothing to search we can simply return the base group
  if(node_path.size()==0 && !node_path.is_root())
    return base;

  //if the search path is the root node we just return the root node of the
  //search base
  if(node_path.is_root())
    return base.link().file().root();

  //if the path is absolute we have to change the base group and the search path
  if(node_path.absolute())
  {
    search_base = base.link().file().root();
    search_path = node_path;
    search_path.absolute(false); //make search path relative to root group

    //and start it all over again
    return get_node(search_base,search_path,lapl);
  }
  else
  {
    auto iter = search_path.begin(); //get the first path element
    Node result;
    if(search_base.nodes.exists(*iter,lapl))
    {
      result = search_base.nodes[*iter];

      search_path = Path(++iter,search_path.end());
      if(search_path.size()==0)
      {
        return result;
      }
      else
      {
        return get_node(Group(result),search_path);
      }
    }
    else
    {
      std::stringstream ss;
      ss<<"No node ["<<*iter<<"] below ["<<search_base.link().path()<<"]!";
      throw std::runtime_error(ss.str());
    }

  }

}

bool is_group(const Node &node)
{
  return node.type() == Type::GROUP;
}

bool is_dataset(const Node &node)
{
  return node.type() == Type::DATASET;
}

Group get_group(const Group &base,const Path &group_path,
                const property::LinkAccessList &lapl)
{
  Node n = get_node(base,group_path,lapl);
  if(!is_group(n))
  {
    std::stringstream ss;
    ss<<"Node ["<<n.link().path()<<"] is not a group!";
    throw std::runtime_error(ss.str());
  }

  return n;
}

Dataset get_dataset(const Group &base,const Path &dataset_path,
                    const property::LinkAccessList &lapl)
{
  Node n = get_node(base,dataset_path,lapl);
  if(!is_dataset(n))
  {
    std::stringstream ss;
    ss<<"Node ["<<n.link().path()<<"] is not a dataset!";
    throw std::runtime_error(ss.str());
  }

  return n;
}

} // namespace node
} // namespace hdf5




