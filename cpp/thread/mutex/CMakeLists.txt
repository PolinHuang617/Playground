set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/mutex)

add_executable(mutex mutex.cpp)
set_property(TARGET mutex PROPERTY CXX_STANDARD 17)
target_link_libraries(mutex pthread)