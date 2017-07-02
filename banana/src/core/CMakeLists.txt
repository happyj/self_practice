# set(core_src
  # Acceptor.cpp
  # Buffer.cpp
  # Epoll.cpp
  # EventLoop.cpp
  # IpAddress.cpp
  # IpEndPoint.cpp
  # Poll.cpp
  # Select.cpp
  # Socket.cpp
  # TcpConnection.cpp
  # TcpServer.cpp)

include_directories(${UTILS_DIR})

link_directories(${project_binary_dir}/lib)
  
aux_source_directory(./ core_src)

add_library(${PROJECT_CORE_NAME} ${core_src})

add_dependencies(${PROJECT_CORE_NAME}
    ${PROJECT_UTILS_NAME})

target_link_libraries(${PROJECT_CORE_NAME}
    ${PROJECT_UTILS_NAME})
