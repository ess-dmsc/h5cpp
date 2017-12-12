#
# some default configurations for cmake packages
#

include(CMakePackageConfigHelpers)

#---------------------------------------------------------------------------------
# setup the name for the package version and configuration file
#
# This can easily be done from a very basic project configuration
#---------------------------------------------------------------------------------
set(PACKAGE_VERSION_FILE_NAME "${PROJECT_NAME}-config-version.cmake")
set(PACKAGE_CONFIG_FILE_NAME "${PROJECT_NAME}-config.cmake")
