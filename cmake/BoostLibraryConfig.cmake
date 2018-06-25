
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.41 COMPONENTS filesystem system REQUIRED)

if (CMAKE_CXX_COMPILER_ID MATCHES MSVC)
  add_definitions(-DBOOST_ALL_DYN_LINK)
endif ()
