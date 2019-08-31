include_directories(${PROJECT_SOURCE_DIR}/src ${HDF5_INCLUDE_DIRS})

foreach(HDF5_LIB ${HDF5_LIBRARIES})
    get_filename_component(LIB_PATH ${HDF5_LIB} DIRECTORY)
    link_directories(${LIB_PATH})
endforeach()

add_executable(issue_412_1 issue_412_1.cpp)
target_link_libraries(issue_412_1 h5cpp)

add_executable(issue_412_2 issue_412_2.cpp)
target_link_libraries(issue_412_2 h5cpp)