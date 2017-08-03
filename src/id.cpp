#include "id.h"
#include <vector>

namespace h5cpp
{

id::id()
{}

id::id(hid_t object)
{
  ssize_t size = H5Fget_name(object, NULL, 0);
  std::vector<char> namec(size + 2, '\0');
  size = H5Fget_name(object, namec.data(), size);
  file_name_ = std::string(namec.data());

  H5O_info_t info;
  H5Oget_info(object, &info);
  file_num_ = info.fileno;
  obj_addr_ = info.addr;
}

std::ostream & operator<<(std::ostream &os, const id& p)
{
  os << p.file_num_ << ":" << p.obj_addr_
     << " \"" << p.file_name_ << "\"";
  return os;
}

bool id::operator== (const id& other) const
{
  return (
        (file_name_ == other.file_name_) &&
//        (file_num_ == other.file_num_) &&
        (obj_addr_ == other.obj_addr_)
        );
}

bool id::operator< (const id& other) const
{
  return (
        (file_name_ < other.file_name_) &&
//        (file_num_ < other.file_num_) &&
        (obj_addr_ < other.obj_addr_)
        );
}

std::string id::file_name() const
{
  return file_name_;
}

unsigned long id::file_num() const
{
  return file_num_;
}

haddr_t id::obj_addr() const
{
  return obj_addr_;
}


}
