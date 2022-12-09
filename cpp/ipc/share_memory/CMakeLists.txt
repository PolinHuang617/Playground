set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/share_memory)

add_executable(shm_server server.cpp)
set_property(TARGET shm_server PROPERTY CXX_STANDARD 17)

add_executable(shm_client client.cpp)
set_property(TARGET shm_client PROPERTY CXX_STANDARD 17)

