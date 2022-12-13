set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/thread_pool)

add_executable(thread_pool main.cpp thread_pool.hpp safe_queue.hpp)
set_property(TARGET thread_pool PROPERTY CXX_STANDARD 17)
target_link_libraries(thread_pool pthread)
