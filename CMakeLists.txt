cmake_minimum_required(VERSION 3.0.0)
project(h5cpp
    LANGUAGES CXX C
    VERSION 0.0.1
    )

include(CTest)

#=============================================================================
# setting up conan for use from within cmake
#=============================================================================
set(WITH_CONAN OFF CACHE BOOL "Enable dependency build with conan")

if(WITH_CONAN)
	include(cmake/ConanSetup.cmake)
	
	conan_cmake_run(CONANFILE conanfile.txt
		            BASIC_SETUP
		            BUILD missing)
endif()

if(EXISTS ${PROJECT_BINARY_DIR}/conanbuildinfo.cmake)
    message(STATUS "Using existing conanbuildinfo.cmake file")
    include(${PROJECT_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endif()


#=============================================================================
# some general configuration
#=============================================================================
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(cmake/InstallConfig.cmake)
include(cmake/OutputDirConfig.cmake)
include(cmake/EnsureBuildType.cmake)
include(cmake/WindowsUtils.cmake)
include(cmake/PackageConfig.cmake)
include(Sphinx)
include(utilities)
include(DoxygenUtilities)

#=============================================================================
# Internal compiler options
#=============================================================================
# C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(NOT CMAKE_CXX_STANDARD OR CMAKE_CXX_STANDARD LESS 11)
  set(CMAKE_CXX_STANDARD 11)
endif()

#=============================================================================
# compiler and library configuration
#=============================================================================
include(cmake/CompilerConfig.cmake)
include(cmake/HDF5LibraryConfig.cmake)
include(cmake/BoostLibraryConfig.cmake)


add_custom_target(html)
add_subdirectory(src)
add_subdirectory(doc)
add_subdirectory(test)

#=============================================================================
# create package file
#=============================================================================

#
# create and install the version file
#
write_basic_package_version_file(
	${PROJECT_BINARY_DIR}/${PACKAGE_VERSION_FILE_NAME}
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY AnyNewerVersion)

install(FILES ${PROJECT_BINARY_DIR}/${PACKAGE_VERSION_FILE_NAME}
	    DESTINATION ${CMAKE_INSTALL_PACKAGEDIR}
	    COMPONENT development)
	   
#
# create and install the package file
#
configure_file(${PACKAGE_CONFIG_FILE_NAME} ${PACKAGE_CONFIG_FILE_NAME} COPYONLY)
install(FILES ${PROJECT_BINARY_DIR}/${PACKAGE_CONFIG_FILE_NAME}
	    DESTINATION ${CMAKE_INSTALL_PACKAGEDIR}
	    COMPONENT development)
	   


