set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/future)

add_executable(future future.cpp)
set_property(TARGET future PROPERTY CXX_STANDARD 17)
target_link_libraries(future pthread)

add_executable(package_task package_task.cpp)
set_property(TARGET package_task PROPERTY CXX_STANDARD 17)
target_link_libraries(package_task pthread)

add_executable(async async.cpp)
set_property(TARGET async PROPERTY CXX_STANDARD 17)
target_link_libraries(async pthread)
