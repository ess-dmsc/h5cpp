#pragma once

extern "C" {
#include <hdf5.h>
}

#include <string>
#include <sstream>

namespace h5
{

class id
{
  public:
    id();
    id(hid_t object);

    bool operator== (const id& other) const;
    bool operator< (const id& other) const;

    friend std::ostream & operator<<(std::ostream &os, const id& p);

    std::string   file_name() const;
    unsigned long file_num() const;
    haddr_t       obj_addr() const;

  private:
    std::string   file_name_;
    unsigned long file_num_ {0};
    haddr_t       obj_addr_ {0};
};


}
