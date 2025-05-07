if(H5CPP_WITH_MPI)
  set(HDF5_PREFER_PARALLEL TRUE)
endif()

find_package(HDF5 REQUIRED COMPONENTS C HL)
# We cannot use the `VERSION` argument to `find_package` due to a bug in the `FindHDF5.cmake`
# script provided by cmake (see https://gitlab.kitware.com/cmake/cmake/-/issues/25358)
# Until this has been fixed, we check for the minimum required HDF5 version ourself:
if(NOT HDF5_VERSION VERSION_GREATER_EQUAL "1.8.13")
  message(FATAL_ERROR "The HDF5 version is too low. At least 1.8.13 is required.")
endif()
message(STATUS "==============================================================")
message(STATUS "========================Found HDF5============================")
message(STATUS "==============================================================")
message(STATUS "Found HDF5 libraries in: ${HDF5_LIBRARY_DIRS}")
message(STATUS "Found HDF5 libraries: ${HDF5_LIBRARIES}")
message(STATUS "Found HDF5 HL libraries: ${HDF5_HL_LIBRARIES}")
message(STATUS "Found HDF5 headers: ${HDF5_INCLUDE_DIRS}")
message(STATUS "Found HDF5 definitions: ${HDF5_DEFINITIONS}")
message(STATUS "Found HDF5 HDF5_VERSION = ${HDF5_VERSION}")
message(STATUS "Found HDF5 HDF5_IS_PARALLEL = ${HDF5_IS_PARALLEL}")
message(STATUS "==============================================================")


if(H5CPP_WITH_MPI)
  if(NOT HDF5_IS_PARALLEL)
    message(FATAL_ERROR "The HDF5 version found does not support MPI")
  endif()
endif()
