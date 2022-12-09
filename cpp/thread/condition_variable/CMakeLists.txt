set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/condition_variable)

add_executable(cv cv.cpp)
set_property(TARGET cv PROPERTY CXX_STANDARD 17)
target_link_libraries(cv pthread)