# set(tests_src
 # Buffer_unittest.cpp
 # IpAddress_unittest.cpp)

 aux_source_directory(./ src_list)
 
include_directories(${PROJECT_UTILS_NAME}
    ${PROJECT_CORE_NAME})
    
link_directories(${project_binary_dir}/lib)

add_executable(${PROJECT_TEST_NAME} ${src_list})

add_dependencies(${PROJECT_CORE_NAME}
    ${PROJECT_UTILS_NAME})


target_link_libraries(${PROJECT_TEST_NAME}
    ${PROJECT_UTILS_NAME}
    ${PROJECT_CORE_NAME})
