set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
    ${dir}/array.cpp
    ${dir}/compound.cpp
    ${dir}/datatype.cpp
    ${dir}/float.cpp
    ${dir}/integer.cpp
    ${dir}/string.cpp
    ${dir}/types.cpp
    ${dir}/enum.cpp
    )

set(HEADERS
    ${dir}/datatype.hpp
    ${dir}/factory.hpp
    ${dir}/float.hpp
    ${dir}/integer.hpp
    ${dir}/type_trait.hpp
    ${dir}/types.hpp
    ${dir}/compound.hpp
    ${dir}/string.hpp
    ${dir}/array.hpp
    ${dir}/enum.hpp
    )

install(FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp/datatype)

set(h5cpp_headers ${h5cpp_headers} ${HEADERS} PARENT_SCOPE)
set(h5cpp_sources ${h5cpp_sources} ${SOURCES} PARENT_SCOPE)
