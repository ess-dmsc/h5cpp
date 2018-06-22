
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.41 COMPONENTS filesystem REQUIRED)

if (CMAKE_CXX_COMPILER_ID MATCHES MSVC)
  add_definitions(-DBOOST_ALL_DYN_LINK)
endif ()

# Prevents requiring boost system,
# may not be required when boost version >=1.67.0 is used
add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)
