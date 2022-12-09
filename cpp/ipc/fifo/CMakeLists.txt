set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/fifo)

add_executable(fifo_server server.cpp)
set_property(TARGET fifo_server PROPERTY CXX_STANDARD 17)

add_executable(fifo_client client.cpp)
set_property(TARGET fifo_client PROPERTY CXX_STANDARD 17)
