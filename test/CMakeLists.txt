include_directories(${PROJECT_SOURCE_DIR}/src)

include(${PROJECT_SOURCE_DIR}/cmake/BoostTestLogConfig.cmake)

add_subdirectory(ObjectHandle)
add_subdirectory(property_list)
add_subdirectory(logs)
