option(H5CPP_WITH_MPI "Enable MPI support" OFF)

if (H5CPP_WITH_MPI)
  if (CMAKE_SYSTEM_NAME MATCHES Windows)
    h5cpp_message(FATAL_ERROR "MPI not supported on the Windows platform!")
  endif ()

  if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-literal-suffix")
  endif()

  find_package(MPI REQUIRED)
  h5cpp_message(STATUS "Found MPI headers in: ${MPI_C_INCLUDE_PATH}")
  h5cpp_message(STATUS "Found MPI libraries: ${MPI_C_LIBRARIES}")

endif ()
