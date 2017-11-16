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
    set(COVERAGE_LIBRARIES gcov)
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

function(create_coverage_targets run_target bin_dir source_dir output_path)
  if (${COV})
    file(MAKE_DIRECTORY ${output_path})
    if (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang OR ${CMAKE_CXX_COMPILER_ID} STREQUAL AppleClang)
      find_program(LLVM_COV_PATH NAMES "llvm-cov-mp-4.0" "llvm-cov")
      find_program(LLVM_PROF_PATH NAMES "llvm-profdata-mp-4.0" "llvm-profdata")
      if (NOT LLVM_PROF_PATH OR NOT LLVM_COV_PATH)
        message(WARNING "Unable to enable coverage as llvm-cov and/or llvm-profdata was not found.")
      else ()
        add_custom_target(generate_coverage_html COMMAND ${LLVM_PROF_PATH} "merge" "default.profraw" "-o" "default.profdata" ";" ${LLVM_COV_PATH} "show" "${bin_dir}/bin/unit_tests" "-instr-profile=default.profdata" "-format=html" ">${output_path}/coverage.html" DEPENDS ${run_target}) # ";" ${LLVM_COV_PATH} "report" "${bin_dir}/lib"
      endif ()
    elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
      find_program(GCOV_PATH gcov)
      find_program(GCOVR_PATH gcovr PATHS ${CMAKE_SOURCE_DIR}/test)
      if (NOT GCOV_PATH OR NOT GCOVR_PATH)
        message(WARNING "Unable to enable coverage target as gcov and/or gocvr was not found.")
      else ()
        add_custom_target(generate_coverage_xml COMMAND ${GCOVR_PATH} "-r" "${source_dir}" "-x" "${bin_dir}" "-o" "${output_path}/coverage.xml" "${bin_dir}" DEPENDS ${run_target})
        add_custom_target(generate_coverage_html COMMAND ${GCOVR_PATH} "-r" "${source_dir}" "--html" "--html-details" "-o" "${output_path}/index.html" "${bin_dir}" DEPENDS ${run_target})
        add_custom_target(generate_coverage DEPENDS generate_coverage_xml generate_coverage_html)
      endif ()
    endif ()
  endif ()
endfunction()
