#pragma once

#ifdef WITH_BOOST
  #include <boost/filesystem.hpp>
  namespace fs = boost::filesystem;
#else
  #include <filesystem>
  namespace fs = std::filesystem;
#endif
