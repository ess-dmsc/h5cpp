cmake_minimum_required(VERSION 3.0.0)
project(h5++
    VERSION 0.0.1
    LANGUAGES CXX)


add_custom_target(html)

add_subdirectory(doc)

add_subdirectory(src)
