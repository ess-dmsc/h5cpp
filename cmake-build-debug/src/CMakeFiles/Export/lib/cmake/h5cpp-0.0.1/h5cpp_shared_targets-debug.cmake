#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "h5cpp_shared" for configuration "Debug"
set_property(TARGET h5cpp_shared APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(h5cpp_shared PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libh5cpp_shared.so.0.0.1"
  IMPORTED_SONAME_DEBUG "libh5cpp_shared.so.0.0.1"
  )

list(APPEND _IMPORT_CHECK_TARGETS h5cpp_shared )
list(APPEND _IMPORT_CHECK_FILES_FOR_h5cpp_shared "${_IMPORT_PREFIX}/lib/libh5cpp_shared.so.0.0.1" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
