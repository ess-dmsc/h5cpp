#=============================================================================
# Enabling code coverage
#=============================================================================
#
#   1. For each target that you want to enable coverage reporting for:
#     a. invoke enable_coverage(target_name)
#     b. include ${COVERAGE_LIBRARIES} in target_link_libraries()
#   2. Generate coverage targets with....
#
#   3. Invoke cmake woth -DCOV=1 option
#

option(COV "Enable code coverage reporting for unit tests (if possible)." OFF)

if (${COV})
  if (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang OR ${CMAKE_CXX_COMPILER_ID} STREQUAL AppleClang)
    message(STATUS "Enabling code coverage for Clang")
    set(coverage_compile_flags "-g -O0 -fprofile-instr-generate -fcoverage-mapping")
    set(coverage_link_flags "-g -O0 -fprofile-instr-generate -fcoverage-mapping")
  elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    message(STATUS "Enabling code coverage for GCC")
    set(coverage_compile_flags "-coverage -fprofile-generate -ftest-coverage")
    set(coverage_link_flags "-g -O0 -coverage -fprofile-generate -ftest-coverage")
    set(COVERAGE_LIBRARIES gcov PARENT_SCOPE)
  else ()
    message(FATAL_ERROR "Cannot enable coverage reporting. Unsupported compiler: (${CMAKE_CXX_COMPILER_ID}).")
    set(COV OFF)
  endif ()
endif ()

function(enable_coverage coverage_target)
  if (${COV})
    set_target_properties(${coverage_target} PROPERTIES COMPILE_FLAGS ${coverage_compile_flags})
    set_target_properties(${coverage_target} PROPERTIES LINK_FLAGS ${coverage_link_flags})
  else ()
    message(STATUS "Cannot enable coverage for target: ${coverage_target}. Code coverage not enabled (COV=0).")
  endif ()
endfunction()

