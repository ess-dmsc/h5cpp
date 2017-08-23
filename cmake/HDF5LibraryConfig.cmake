
find_package(HDF5 REQUIRED COMPONENTS C)
message(STATUS "Found HDF5 libraries: ${HDF5_LIBRARY_DIRS}")
message(STATUS "Found HDF5 headers: ${HDF5_INCLUDE_DIRS}")

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    add_definitions(-DH5_BUILT_AS_DYNAMIC_LIB)
endif()

