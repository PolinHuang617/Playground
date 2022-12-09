set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/asio_local_socket)

set(BOOST_ROOT /home/polin/Library/boost_1_80_0)

find_package(Boost REQUIRED)
if(Boost_FOUND)
    MESSAGE( STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}." )
	MESSAGE( STATUS "Boost_LIBRARY_DIRS = ${Boost_LIBRARY_DIRS}." )
	MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}." )
	MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}." )

    include_directories(${Boost_INCLUDE_DIRS})

    add_executable(asio_local_socket_server server.cpp)
    set_property(TARGET asio_local_socket_server PROPERTY CXX_STANDARD 17)
    target_link_libraries(asio_local_socket_server ${Boost_LIBRARIES} pthread)

    add_executable(asio_local_socket_client client.cpp)
    set_property(TARGET asio_local_socket_client PROPERTY CXX_STANDARD 17)
    target_link_libraries(asio_local_socket_client ${Boost_LIBRARIES} pthread)

endif()