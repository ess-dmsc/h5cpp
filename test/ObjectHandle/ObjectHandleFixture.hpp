

extern "C" { 
  #include <hdf5.h>
}

#include <string>

struct ObjectHandleTestFixture{
  
  std::string filename;


  hid_t create_file();
  hid_t create_group();

};

