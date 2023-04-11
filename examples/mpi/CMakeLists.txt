add_executable(writer_simple writer.cpp)
target_link_libraries(writer_simple PRIVATE h5cpp::h5cpp)

add_executable(writer_extend writer_extend.cpp)
target_link_libraries(writer_extend PRIVATE h5cpp::h5cpp)

add_dependencies(examples
  writer_simple
  writer_extend
  )
