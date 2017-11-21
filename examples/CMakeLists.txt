
add_executable(basic_files EXCLUDE_FROM_ALL basic_files.cpp)
target_link_libraries(basic_files h5cpp_shared)

add_executable(selecting_datasets EXCLUDE_FROM_ALL selecting_datasets.cpp)
target_link_libraries(selecting_datasets h5cpp_shared)

add_executable(writing_vector EXCLUDE_FROM_ALL writing_vector.cpp)
target_link_libraries(writing_vector h5cpp_shared)

add_executable(writing_complex EXCLUDE_FROM_ALL writing_complex.cpp)
target_link_libraries(writing_complex h5cpp_shared)

add_executable(writing_image EXCLUDE_FROM_ALL writing_image.cpp
  rgbpixel.cpp)
target_link_libraries(writing_image h5cpp_shared)

#add_executable(write_single_vector EXCLUDE_FROM_ALL write_single_vector.cpp)
#target_link_libraries(write_single_vector h5cpp_shared)

add_executable(append_scalar_data EXCLUDE_FROM_ALL append_scalar_data.cpp)
target_link_libraries(append_scalar_data h5cpp_shared)

#add_executable(write_vector_list EXCLUDE_FROM_ALL write_vector_list.cpp)
#target_link_libraries(write_vector_list h5cpp_shared)
add_executable(append_vector_data EXCLUDE_FROM_ALL append_vector_data.cpp)
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
if (HDF5_VERSION VERSION_GREATER 1.10.0)
  set(SWMR_SOURCES swmr_environment.cpp swmr_builder.cpp)
  add_executable(swmr_write EXCLUDE_FROM_ALL swmr_write.cpp ${SWMR_SOURCES})
  target_link_libraries(swmr_write h5cpp_shared)

  add_executable(swmr_read EXCLUDE_FROM_ALL swmr_reader.cpp ${SWMR_SOURCES})
  target_link_libraries(swmr_read h5cpp_shared)

  add_dependencies(examples
    swmr_write
    swmr_read
    )

endif ()

if (WITH_MPI)
  add_subdirectory(mpi)
  add_dependencies(examples
    writer_simple
    writer_extend
    )
endif ()

