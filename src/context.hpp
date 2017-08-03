#pragma once

#include "id.hpp"
#include <map>
#include <mutex>

namespace h5
{

class context
{
  public:
    void open(const hid_t&);
    bool is_open(const hid_t&) const;
    void close(const hid_t&);

  private:
    mutable std::mutex mutex_;
    std::map<id, hid_t> objects_;

    void close(const id&);

    //singleton assurance
  public:
    static context& singleton()
    {
      static context singleton_instance;
      return singleton_instance;
    }

    context(context const&)         = delete;
    void operator=(context const&)  = delete;

  private:
    context() {}
    ~context();
};


}
