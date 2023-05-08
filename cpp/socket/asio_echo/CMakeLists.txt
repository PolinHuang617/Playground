set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/asio_echo)

# set(BOOST_ROOT /home/polin/Library/boost_1_80_0)
# set(Boost_NO_SYSTEM_PATH ON)

find_package(Boost REQUIRED)
if(Boost_FOUND)
    MESSAGE( STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}." )
	MESSAGE( STATUS "Boost_LIBRARY_DIRS = ${Boost_LIBRARY_DIRS}." )
	MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}." )
	MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}." )

	include_directories(${Boost_INCLUDE_DIRS})

    add_executable(asio_echo_server server.cpp)
    set_property(TARGET basic_echo_server PROPERTY CXX_STANDARD 17)
    target_link_libraries(asio_echo_server ${Boost_LIBRARIES} pthread)

    add_executable(asio_echo_client client.cpp)
    set_property(TARGET asio_echo_client PROPERTY CXX_STANDARD 17)
    target_link_libraries(asio_echo_client ${Boost_LIBRARIES} pthread)

    add_executable(test_server test_server.cpp)
    set_property(TARGET test_server PROPERTY CXX_STANDARD 11)
    target_link_libraries(test_server ${Boost_LIBRARIES} pthread)

    add_executable(test_client test_client.cpp)
    set_property(TARGET test_client PROPERTY CXX_STANDARD 11)
    target_link_libraries(test_client ${Boost_LIBRARIES} pthread)

    # 目前在gcc中默认不启用协程，需要传递-fcoroutines，编译器才会打开协程功能
    # add_definitions(-fcoroutines)
    # add_executable(co_server co_server.cpp)
    # set_property(TARGET co_server PROPERTY CXX_STANDARD 20)
    # target_link_libraries(co_server ${Boost_LIBRARIES} pthread)

endif()