cmake_minimum_required(VERSION 2.6)
project(banana)

set(CXX_FLAGS
 -g
 # -DVALGRIND
 # -DMUDUO_STD_STRING
 -DCHECK_PTHREAD_RETURN_VALUE
 -D_FILE_OFFSET_BITS=64
 -Wall
 -Wextra
 -Werror
 -Wconversion
 -Wno-unused-parameter
 -Wold-style-cast
 -Woverloaded-virtual
 -Wpointer-arith
 -Wshadow
 -Wwrite-strings
 -march=native
 # -MMD
 # -std=c++0x
 -rdynamic
 )

set(cmake_build_type_debug)
set(cmake_c_flags_debug "-g-Wall")

set(executable_output_path ${project_binary_dir}/bin)
set(library_output_path ${project_binary_dir}/lib)

add_subdirectory(src/core)
add_subdirectory(src/tests)




