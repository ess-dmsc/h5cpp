set(SWMR_SOURCES swmr_environment.cpp swmr_builder.cpp)
if(WIN32)
  add_executable(swmr_write WIN32 swmr_write.cpp ${SWMR_SOURCES})
else()
  add_executable(swmr_write swmr_write.cpp ${SWMR_SOURCES})
endif()
target_link_libraries(swmr_write PRIVATE h5cpp::h5cpp)

if(WIN32)
  add_executable(swmr_read WIN32 swmr_reader.cpp ${SWMR_SOURCES})
else()
  add_executable(swmr_read swmr_reader.cpp ${SWMR_SOURCES})
endif()
target_link_libraries(swmr_read PRIVATE h5cpp::h5cpp)

add_dependencies(examples
  swmr_write
  swmr_read
  )
