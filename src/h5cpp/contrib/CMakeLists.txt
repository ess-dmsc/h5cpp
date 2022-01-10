set(CONTRIB_SOURCES)
set(CONTRIB_HEADERS)

if(H5CPP_ENABLE_STL)
    add_subdirectory(stl)
endif()

if(H5CPP_ENABLE_NEXUS)
    add_subdirectory(nexus)
endif()

set(h5cpp_sources ${h5cpp_sources} ${CONTRIB_SOURCES} PARENT_SCOPE)
set(h5cpp_headers ${h5cpp_headers} ${CONTRIB_HEADERS} PARENT_SCOPE)
