set(SWMR_SOURCES swmr_environment.cpp swmr_builder.cpp)
add_executable(swmr_write swmr_write.cpp ${SWMR_SOURCES})
target_link_libraries(swmr_write PRIVATE h5cpp::h5cpp)

add_executable(swmr_read swmr_reader.cpp ${SWMR_SOURCES})
target_link_libraries(swmr_read PRIVATE h5cpp::h5cpp)

add_dependencies(examples
  swmr_write
  swmr_read
  )
