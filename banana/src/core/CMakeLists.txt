set(src_list "*.cpp")

set(library_output_path ${project_source_dir}/bin)

add_library(core static ${src_list})
