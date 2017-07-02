cmake_minimum_required(VERSION 2.6)
project(bananasvr)

# set(CXX_FLAGS
 # -g
 # # -DVALGRIND
 # # -DMUDUO_STD_STRING
 # -DCHECK_PTHREAD_RETURN_VALUE
 # -D_FILE_OFFSET_BITS=64
 # -Wall
 # -Wextra
 # -Werror
 # -Wconversion
 # -Wno-unused-parameter
 # -Wold-style-cast
 # -Woverloaded-virtual
 # -Wpointer-arith
 # -Wshadow
 # -Wwrite-strings
 # -march=native
 # # -MMD
 # # -std=c++0x
 # -rdynamic
 # )

set(DEPS_DIR ${project_source_dir}/src/deps)
set(DEPS_INCLUDE_DIR ${DEPS_DIR}/include)
set(DEPS_LIB_DIR ${DEPS_DIR}/lib)
set(UTILS_DIR ${project_source_dir}/src/utils)
set(CORE_DIR ${project_source_dir}/src/core)
 
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g -Wall -std=c++11")
set(cmake_build_type debug)


 
include_directories(${DEPS_INCLUDE_DIR})

link_directories(${DEPS_LIB_DIR})


set(executable_output_path ${project_binary_dir}/bin)
set(library_output_path ${project_binary_dir}/lib)


set(PROJECT_UTILS_NAME utils)
set(PROJECT_CORE_NAME core)
set(PROJECT_TEST_NAME tests)

add_subdirectory(src/utils)
add_subdirectory(src/core)
add_subdirectory(src/tests)




