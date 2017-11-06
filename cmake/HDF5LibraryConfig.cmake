if(WITH_MPI)
    set(HDF5_PREFER_PARALLEL TRUE)
endif()

find_package(HDF5 REQUIRED COMPONENTS C)
message(STATUS "Found HDF5 libraries in: ${HDF5_LIBRARY_DIRS}")
message(STATUS "Found HDF5 libraries: ${HDF5_LIBRARIES}")
message(STATUS "Found HDF5 headers: ${HDF5_INCLUDE_DIRS}")

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    add_definitions(-DH5_BUILT_AS_DYNAMIC_LIB)
endif()

if(WITH_MPI)
    if(NOT HDF5_IS_PARALLEL)
        message(FATAL_ERROR "The HDF5 version found does not support MPI")
    endif()
endif()
