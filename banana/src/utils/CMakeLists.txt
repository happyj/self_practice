aux_source_directory(./ src_list)
aux_source_directory(./fmt src_list)

add_library(${PROJECT_UTILS_NAME} STATIC ${src_list})
target_link_libraries(${PROJECT_UTILS_NAME})
