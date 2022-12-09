set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/local_socket)

add_executable(local_socket_server server.cpp)
set_property(TARGET local_socket_server PROPERTY CXX_STANDARD 17)

add_executable(local_socket_client client.cpp)
set_property(TARGET local_socket_client PROPERTY CXX_STANDARD 17)
