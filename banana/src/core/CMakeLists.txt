set(core_src
  Acceptor.cpp
  Buffer.cpp
  Epoll.cpp
  EventLoop.cpp
  IpAddress.cpp
  IpEndPoint.cpp
  Poll.cpp
  Select.cpp
  Socket.cpp
  TcpConnection.cpp
  TcpServer.cpp)

add_library(core ${core_src})
#target_link_libraries(core_cpp11 pthread rt)
#set_target_properties(core_cpp11 PROPERTIES compile_flags "-std=cxx0x")
