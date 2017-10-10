set(HEADERS attribute_creation_list.hpp
	class.hpp
	creation_order.hpp
	dataset_access_list.hpp
	dataset_creation_list.hpp
	dataset_transfer_list.hpp
	datatype_access_list.hpp
	
	file_access_list.hpp
	file_creation_list.hpp
	file_mount_list.hpp
	group_access_list.hpp
	group_creation_list.hpp
	link_access_list.hpp
	link_creation_list.hpp
	list.hpp
	object_creation_list.hpp
	string_creation_list.hpp
	type_creation_list.hpp
	object_copy_list.hpp
)

add_doxygen_source_deps(${HEADERS})
install(FILES ${HEADERS}
	    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp/property)