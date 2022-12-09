set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/pipe)

add_executable(pipe pipe.cpp)
set_property(TARGET pipe PROPERTY CXX_STANDARD 17)