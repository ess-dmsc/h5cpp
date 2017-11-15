

#include <h5cpp/hdf5_capi.hpp>

#include <string>

struct ObjectHandleTestFixture{
  
  std::string filename;


  hid_t create_file();
  hid_t create_group();

};

