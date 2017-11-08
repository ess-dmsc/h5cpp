set(HEADERS attribute_creation.hpp
	property_class.hpp
	creation_order.hpp
	dataset_access.hpp
	dataset_creation.hpp
	dataset_transfer.hpp
	datatype_access.hpp
	
	file_access.hpp
	file_creation.hpp
	file_mount.hpp
	group_access.hpp
	group_creation.hpp
	link_access.hpp
	link_creation.hpp
	property_list.hpp
	object_creation.hpp
	string_creation.hpp
	type_creation.hpp
	object_copy.hpp
)

add_doxygen_source_deps(${HEADERS})
install(FILES ${HEADERS}
	    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp/property)