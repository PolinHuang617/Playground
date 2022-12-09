set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/tutorial/date_timer)

set(BOOST_ROOT /home/polin/Library/boost_1_80_0)
# set(Boost_NO_SYSTEM_PATH ON)

find_package(Boost REQUIRED)
if(Boost_FOUND)
    MESSAGE( STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}." )
	MESSAGE( STATUS "Boost_LIBRARY_DIRS = ${Boost_LIBRARY_DIRS}." )
	MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}." )
	MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}." )

	include_directories(${Boost_INCLUDE_DIRS})

    add_executable(sync_tcp_client sync_tcp_client.cpp)
    set_property(TARGET sync_tcp_client PROPERTY CXX_STANDARD 17)
    target_link_libraries(sync_tcp_client ${Boost_LIBRARIES} pthread)
    
    add_executable(sync_tcp_server sync_tcp_server.cpp)
    set_property(TARGET sync_tcp_server PROPERTY CXX_STANDARD 17)
    target_link_libraries(sync_tcp_server ${Boost_LIBRARIES} pthread)

    add_executable(async_tcp_server async_tcp_server.cpp)
    set_property(TARGET async_tcp_server PROPERTY CXX_STANDARD 17)
    target_link_libraries(async_tcp_server ${Boost_LIBRARIES} pthread)
   
    add_executable(sync_udp_client sync_udp_client.cpp)
    set_property(TARGET sync_udp_client PROPERTY CXX_STANDARD 17)
    target_link_libraries(sync_udp_client ${Boost_LIBRARIES} pthread)
    
    add_executable(sync_udp_server sync_udp_server.cpp)
    set_property(TARGET sync_udp_server PROPERTY CXX_STANDARD 17)
    target_link_libraries(sync_udp_server ${Boost_LIBRARIES} pthread)

    add_executable(combined_server combined_server.cpp)
    set_property(TARGET combined_server PROPERTY CXX_STANDARD 17)
    target_link_libraries(combined_server ${Boost_LIBRARIES} pthread)

endif()