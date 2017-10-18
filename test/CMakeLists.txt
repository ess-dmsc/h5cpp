include_directories(${PROJECT_SOURCE_DIR}/src/include)
set(WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test)

include(${PROJECT_SOURCE_DIR}/cmake/TestCoverage.cmake)
find_package(GTest)

set(Common_SRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/iteration_index_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/iteration_order_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/object_id_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/path_test.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/fixture.cpp
)

set(Common_INC    
#  ${CMAKE_CURRENT_SOURCE_DIR}/fixture.hpp
)

add_subdirectory(ObjectHandle)
add_subdirectory(property)
add_subdirectory(datatype)
add_subdirectory(dataspace)
add_subdirectory(logs)
add_subdirectory(file)
add_subdirectory(node)
#add_subdirectory(attribute)
#add_subdirectory(examples)

add_executable(unit_tests ${Common_SRC} ${Common_INC})
add_dependencies(unit_tests h5cpp_unit_test)
target_include_directories(unit_tests PRIVATE ${GTEST_INCLUDE_DIRS} h5cpp_unit_test)
target_link_libraries(unit_tests h5cpp_unit_test ${GTEST_LIBRARIES})

add_custom_target(run_tests COMMAND unit_tests "--gtest_output=xml:unit_tests_run.xml" DEPENDS unit_tests)

set(COVERAGE_RESULTS_PATH ${PROJECT_BINARY_DIR}/test/)

find_program(GCOV_PATH gcov)
find_program(GCOVR_PATH gcovr PATHS ${CMAKE_SOURCE_DIR}/test)
if (NOT GCOV_PATH OR NOT GCOVR_PATH)
      message(WARNING "Unable to enable coverage target as gcov and/or gocvr was not found.")
else()
    add_custom_target(generate_coverage COMMAND ${GCOVR_PATH} "-r" "${CMAKE_SOURCE_DIR}/src" "-x" "${PROJECT_BINARY_DIR}" "-o" "${COVERAGE_RESULTS_PATH}/coverage.xml" DEPENDS run_tests)
endif()
