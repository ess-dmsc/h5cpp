cmake_minimum_required(VERSION 3.7.0)
project("usingh5cpp")

find_package(h5cpp REQUIRED)
add_library(core SHARED core.cpp)
target_link_libraries(core PUBLIC h5cpp::h5cpp)

add_executable(app app.cpp)
target_link_libraries(app PRIVATE core)