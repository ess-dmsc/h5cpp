#pragma once

#include "id.h"
#include <map>
#include <mutex>

namespace h5cpp
{

class global
{
public:
  static global& singleton()
  {
    static global singleton_instance;
    return singleton_instance;
  }

  void open(const hid_t&);
  bool is_open(const hid_t&) const;
  void close(const hid_t&);

protected:
  mutable std::mutex mutex_;
  std::map<id, hid_t> objects_;

  void close(const id&);

private:
  //singleton assurance
  global() {}
  global(global const&);
  void operator=(global const&);
  ~global();
};


}
