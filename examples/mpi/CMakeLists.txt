if(WIN32)
  add_executable(writer_simple WIN32 writer.cpp)
else()
  add_executable(writer_simple writer.cpp)
endif()
target_link_libraries(writer_simple PRIVATE h5cpp::h5cpp)

if(WIN32)
  add_executable(writer_extend WIN32  writer_extend.cpp)
else()
  add_executable(writer_extend writer_extend.cpp)
endif()
target_link_libraries(writer_extend PRIVATE h5cpp::h5cpp)

add_dependencies(examples
  writer_simple
  writer_extend
  )
