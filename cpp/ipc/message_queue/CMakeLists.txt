set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/message_queue)

add_executable(mq_server server.cpp)
set_property(TARGET mq_server PROPERTY CXX_STANDARD 17)

add_executable(mq_client client.cpp)
set_property(TARGET mq_client PROPERTY CXX_STANDARD 17)

