include(ExternalProject)

ExternalProject_Add(googletest
    DEPENDS h5cpp_shared
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/googletest
	SOURCE_DIR /usr/src/googletest/googletest
	CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}i -DBUILD_SHARED_LIBS=ON
	           -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/googletest
	INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/googletest
	)
	
set(GTEST_ROOT ${CMAKE_CURRENT_BINARY_DIR}/googltest)