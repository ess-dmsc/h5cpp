#pragma once
#include <h5cpp/hdf5.hpp>
#include <string>


hdf5::file::File create_file(const std::string &filename);
