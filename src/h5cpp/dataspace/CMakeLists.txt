set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
    ${dir}/hyperslab.cpp
    ${dir}/dataspace.cpp
    ${dir}/scalar.cpp
    ${dir}/selection.cpp
    ${dir}/selection_manager.cpp
    ${dir}/simple.cpp
    ${dir}/type.cpp
    ${dir}/view.cpp
    ${dir}/points.cpp
    ${dir}/pool.cpp
    )

set(HEADERS
    ${dir}/hyperslab.hpp
    ${dir}/dataspace.hpp
    ${dir}/scalar.hpp
    ${dir}/selection_manager.hpp
    ${dir}/selection.hpp
    ${dir}/simple.hpp
    ${dir}/type.hpp
    ${dir}/type_trait.hpp
    ${dir}/view.hpp
    ${dir}/points.hpp
    ${dir}/pool.hpp
    )

install(FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp/dataspace)

set(h5cpp_headers ${h5cpp_headers} ${HEADERS} PARENT_SCOPE)
set(h5cpp_sources ${h5cpp_sources} ${SOURCES} PARENT_SCOPE)
