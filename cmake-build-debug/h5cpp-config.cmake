
set(BOOST_COMPONENTS)

if(NOT TARGET Boost::filesystem)
	list(APPEND BOOST_COMPONENTS filesystem)
endif()

find_package(Boost 1.41 REQUIRED COMPONENTS ${BOOST_COMPONENTS})
if(NOT Boost_FOUND)
	message(FATAL_ERROR "Could not find Boost filesystem library - cannot load h5cpp targets")
endif()

link_directories(${Boost_LIBRARY_DIRS})
include(${CMAKE_CURRENT_LIST_DIR}/h5cpp_shared_targets.cmake)