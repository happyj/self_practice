set(executable_output_path ${project_source_dir}/bin)

set(SRC_LIST *.cpp)

include_directories(${PROJECT_SOURCE_DIR/src/deps/include})
link_directories(${PROJECT_SOURCE_DIR}/src/deps/lib)

add_executable(unittest ${SRC_LIST})
target_link_libraries(unittest core)
