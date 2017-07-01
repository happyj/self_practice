set(tests_src
 Buffer_unittest.cpp
 IpAddress_unittest.cpp)

include_directories(${PROJECT_SOURCE_DIR/src/deps/include})
link_directories(${PROJECT_SOURCE_DIR}/src/deps/lib)

add_executable(unittest ${tests_src})
target_link_libraries(unittest core)
