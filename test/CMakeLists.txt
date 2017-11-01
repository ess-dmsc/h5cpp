include_directories(${PROJECT_SOURCE_DIR}/src/include)
set(WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test)

#include(${PROJECT_SOURCE_DIR}/cmake/TestCoverage.cmake)

if(CMAKE_SYSTEM_NAME MATCHES Linux AND NOT WITH_CONAN)
	message(STATUS "Check Linux distribution")
	
	find_program(LSB_RELEASE lsb_release)
	execute_process(COMMAND ${LSB_RELEASE} -is 
		OUTPUT_VARIABLE LINUX_DISTRIBUTION
		OUTPUT_STRIP_TRAILING_WHITESPACE)
	
    if(LINUX_DISTRIBUTION MATCHES "Debian" OR LINUX_DISTRIBUTION MATCHES "Ubuntu")
		message(STATUS "Try to apply Debian fix for googletest")
		include(${PROJECT_SOURCE_DIR}/cmake/DebianGTestFix.cmake)
	else()		
		find_package(GTest REQUIRED)
	endif()

else()
find_package(GTest REQUIRED)
endif()

find_package(Threads)

#
# We definitely need a better solution for this!
# 
if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    add_definitions(/wd4251 /wd4275)
endif()


set(Common_SRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/iteration_index_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/iteration_order_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/iterator_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/object_id_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/path_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fixture.cpp
)

set(Common_INC    
  ${CMAKE_CURRENT_SOURCE_DIR}/fixture.hpp
)

add_subdirectory(ObjectHandle)
add_subdirectory(property)
add_subdirectory(datatype)
add_subdirectory(dataspace)
add_subdirectory(logs)
add_subdirectory(file)
add_subdirectory(node)
add_subdirectory(attribute)
add_subdirectory(examples)
add_subdirectory(error)

add_executable(unit_tests EXCLUDE_FROM_ALL ${Common_SRC} ${Common_INC})
add_dependencies(unit_tests h5cpp_shared)
target_include_directories(unit_tests PRIVATE ${GTEST_INCLUDE_DIRS} h5cpp_shared)
target_link_libraries(unit_tests h5cpp_shared ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

if (${COV})
    message(STATUS "Enabling code coverage in unit tests.")
    if (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang OR ${CMAKE_CXX_COMPILER_ID} STREQUAL AppleClang)
        set(cov_compile_flags "-g -O0 -fprofile-instr-generate -fcoverage-mapping")
        set(cov_link_flags "-g -O0 -fprofile-instr-generate -fcoverage-mapping")
    elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
        set(cov_compile_flags "-coverage -fprofile-generate -ftest-coverage")
        set(cov_link_flags "-g -O0 -coverage -fprofile-generate -ftest-coverage")
        target_link_libraries(unit_tests gcov)
    else()
        message(FATAL_ERROR "Unable to generate code coverage for this compiler (${CMAKE_CXX_COMPILER_ID}).")
    endif()
    set_target_properties(unit_tests PROPERTIES LINK_FLAGS ${cov_link_flags})
    set_target_properties(unit_tests PROPERTIES COMPILE_FLAGS ${cov_compile_flags})
else()
    message(STATUS "Code coverage not enabled.")
endif()

add_custom_target(run_tests COMMAND unit_tests "--gtest_output=xml:unit_tests_run.xml" DEPENDS unit_tests)
add_test(NAME "RunGoogleTests" COMMAND unit_tests)
if (${COV})
    set(COVERAGE_RESULTS_PATH ${PROJECT_BINARY_DIR}/coverage/)
    file(MAKE_DIRECTORY ${COVERAGE_RESULTS_PATH})
    if (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang OR ${CMAKE_CXX_COMPILER_ID} STREQUAL AppleClang)
        find_program(LLVM_COV_PATH NAMES "llvm-cov-mp-4.0" "llvm-cov")
        find_program(LLVM_PROF_PATH NAMES "llvm-profdata-mp-4.0" "llvm-profdata")
        if (NOT LLVM_PROF_PATH OR NOT LLVM_COV_PATH)
            message(WARNING "Unable to enable coverage as llvm-cov and/or llvm-profdata was not found.")
        else()
            add_custom_target(generate_coverage_html COMMAND ${LLVM_PROF_PATH} "merge" "default.profraw" "-o" "default.profdata" ";" ${LLVM_COV_PATH} "show" "${PROJECT_BINARY_DIR}/bin/unit_tests" "-instr-profile=default.profdata" "-format=html" ">${COVERAGE_RESULTS_PATH}coverage.html" DEPENDS run_tests) # ";" ${LLVM_COV_PATH} "report" "${PROJECT_BINARY_DIR}/lib"
        endif()
    elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    find_program(GCOV_PATH gcov)
    find_program(GCOVR_PATH gcovr PATHS ${CMAKE_SOURCE_DIR}/test)
        if (NOT GCOV_PATH OR NOT GCOVR_PATH)
            message(WARNING "Unable to enable coverage target as gcov and/or gocvr was not found.")
        else()
            add_custom_target(generate_coverage_xml COMMAND ${GCOVR_PATH} "-r" "${CMAKE_SOURCE_DIR}/src/" "-x" "${PROJECT_BINARY_DIR}" "-o" "${COVERAGE_RESULTS_PATH}/coverage.xml" "${PROJECT_BINARY_DIR}" DEPENDS run_tests)
            add_custom_target(generate_coverage_html COMMAND ${GCOVR_PATH} "-r" "${CMAKE_SOURCE_DIR}/src/" "--html" "--html-details" "-o" "${COVERAGE_RESULTS_PATH}/index.html" "${PROJECT_BINARY_DIR}" DEPENDS run_tests)
            add_custom_target(generate_coverage DEPENDS generate_coverage_xml generate_coverage_html)
          endif()
      else()
          #Cant generate targets for this compiler
      endif()
endif()
