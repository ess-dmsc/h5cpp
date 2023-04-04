cmake_minimum_required(VERSION 3.0.0)
project(h5cpp-examples LANGUAGES CXX C)

get_directory_property(IS_TOP_LEVEL PARENT_DIRECTORY)
if (NOT IS_TOP_LEVEL)
  find_package(h5cpp REQUIRED)
endif()

if (NOT H5CPP_BOOST_ENABLED)
  set(CMAKE_CXX_STANDARD 17)
else()
  set(CMAKE_CXX_STANDARD 11)
endif()

if(WIN32)
  add_executable(basic_files WIN32 basic_files.cpp)
else()
  add_executable(basic_files basic_files.cpp)
endif()
target_link_libraries(basic_files PRIVATE h5cpp::h5cpp)

if(WIN32)
  add_executable(selecting_datasets WIN32 selecting_datasets.cpp)
else()
  add_executable(selecting_datasets selecting_datasets.cpp)
endif()
target_link_libraries(selecting_datasets PRIVATE h5cpp::h5cpp)

if(WIN32)
  add_executable(std_vector_io WIN32 std_vector_io.cpp)
else()
  add_executable(std_vector_io std_vector_io.cpp)
endif()
target_link_libraries(std_vector_io PRIVATE h5cpp::h5cpp)

if(WIN32)
  add_executable(complex_io WIN32 complex_io.cpp)
else()
  add_executable(complex_io complex_io.cpp)
endif()
target_link_libraries(complex_io PRIVATE h5cpp::h5cpp)

if(WIN32)
  add_executable(writing_image WIN32 writing_image.cpp
    rgbpixel.cpp)
else()
  add_executable(writing_image writing_image.cpp
    rgbpixel.cpp)
endif()
target_link_libraries(writing_image PRIVATE h5cpp::h5cpp)

if(WIN32)
  add_executable(write_single_vector WIN32 write_single_vector.cpp)
else()
  add_executable(write_single_vector write_single_vector.cpp)
endif()
target_link_libraries(write_single_vector PRIVATE h5cpp::h5cpp)

if(WIN32)
  add_executable(read_dataset WIN32 read_dataset.cpp)
else()
  add_executable(read_dataset read_dataset.cpp)
endif()
target_link_libraries(read_dataset PRIVATE h5cpp::h5cpp)

if(WIN32)
  add_executable(append_scalar_data WIN32 append_scalar_data.cpp)
else()
  add_executable(append_scalar_data append_scalar_data.cpp)
endif()
target_link_libraries(append_scalar_data PRIVATE h5cpp::h5cpp)

if(WIN32)
  add_executable(write_vector_list WIN32 write_vector_list.cpp)
else()
  add_executable(write_vector_list write_vector_list.cpp)
endif()
target_link_libraries(write_vector_list PRIVATE h5cpp::h5cpp)

if(WIN32)
  add_executable(append_vector_data WIN32 append_vector_data.cpp)
else()
  add_executable(append_vector_data append_vector_data.cpp)
endif()
target_link_libraries(append_vector_data PRIVATE h5cpp::h5cpp)


add_custom_target(examples)
add_dependencies(examples
  basic_files
  selecting_datasets
  std_vector_io
  complex_io
  writing_image
  append_scalar_data
  append_vector_data
  )

#
# build this only for new versions of HDF5
#

add_subdirectory(attributes)

if (H5CPP_SWMR_ENABLED)
  add_subdirectory(swmr)
endif ()

if (H5CPP_MPI_ENABLED)
  add_subdirectory(mpi)
endif ()
