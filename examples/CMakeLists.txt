cmake_minimum_required(VERSION 3.0.0)
project(h5cpp-examples LANGUAGES CXX C)

find_package(h5cpp REQUIRED)

set(EXTRA_MODULES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)

include(${EXTRA_MODULES_DIR}/CompilerConfig.cmake)
include(${EXTRA_MODULES_DIR}/MPIConfig.cmake)



add_executable(basic_files basic_files.cpp)
target_link_libraries(basic_files h5cpp_shared)

add_executable(selecting_datasets selecting_datasets.cpp)
target_link_libraries(selecting_datasets h5cpp_shared)

add_executable(writing_vector writing_vector.cpp)
target_link_libraries(writing_vector h5cpp_shared)

add_executable(writing_complex writing_complex.cpp)
target_link_libraries(writing_complex h5cpp_shared)

add_executable(writing_image writing_image.cpp
  rgbpixel.cpp)
target_link_libraries(writing_image h5cpp_shared)

#add_executable(write_single_vector write_single_vector.cpp)
#target_link_libraries(write_single_vector h5cpp_shared)

add_executable(append_scalar_data append_scalar_data.cpp)
target_link_libraries(append_scalar_data h5cpp_shared)

#add_executable(write_vector_list write_vector_list.cpp)
#target_link_libraries(write_vector_list h5cpp_shared)
add_executable(append_vector_data append_vector_data.cpp)
target_link_libraries(append_vector_data h5cpp_shared)


add_custom_target(examples)
add_dependencies(examples
  basic_files
  selecting_datasets
  writing_vector
  writing_complex
  writing_image
  append_scalar_data
  append_vector_data
  )

#
# build this only for new versions of HDF5
#

if (WITH_SWMR)
  add_subdirectory(swmr)
endif ()

if (WITH_MPI)
  add_subdirectory(mpi)
endif ()

