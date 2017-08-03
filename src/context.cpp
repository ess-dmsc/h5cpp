#include "context.hpp"
#include <list>

namespace h5
{

void context::open(const hid_t& hid)
{
  std::lock_guard<std::mutex> guard(mutex_);
  objects_[id(hid)] = hid;
}

bool context::is_open(const hid_t& hid) const
{
  std::lock_guard<std::mutex> guard(mutex_);
  return objects_.count(id(hid));
}

void context::close(const hid_t& hid)
{
  std::lock_guard<std::mutex> guard(mutex_);
  close(id(hid));
}

void context::close(const id& i)
{
  //could do actual object destruction?

  objects_.erase(i);
}

context::~context()
{
  std::list<id> ids;
  for (auto o : objects_)
    ids.push_back(o.first);
  for (auto i : ids)
    close(i);
}


}
