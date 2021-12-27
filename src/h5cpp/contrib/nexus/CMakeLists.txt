set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/ebool.cpp)
set(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/ebool.hpp)

install(FILES ${HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp/contrib/nexus)

set(h5cpp_sources ${h5cpp_sources} ${SOURCES} PARENT_SCOPE)
set(h5cpp_headers ${h5cpp_headers} ${HEADERS} PARENT_SCOPE)