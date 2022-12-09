set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/basic_echo)

add_executable(basic_echo_server server.cpp)
set_property(TARGET basic_echo_server PROPERTY CXX_STANDARD 17)

add_executable(basic_echo_client client.cpp)
set_property(TARGET basic_echo_client PROPERTY CXX_STANDARD 17)