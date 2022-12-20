set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/coroutine)

# set(BOOST_ROOT /home/polin/Library/boost_1_80_0)
# set(Boost_NO_SYSTEM_PATH ON)

find_package(Boost REQUIRED COMPONENTS context fiber)
if(Boost_FOUND)
    MESSAGE( STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}." )
	MESSAGE( STATUS "Boost_LIBRARY_DIRS = ${Boost_LIBRARY_DIRS}." )
	MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}." )
	MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}." )

	include_directories(${Boost_INCLUDE_DIRS})

    add_definitions(-fcoroutines)
    add_executable(basic_coro basic_coro.cpp)
    set_property(TARGET basic_coro PROPERTY CXX_STANDARD 20)
    # target_link_libraries(basic_coro Boost::fiber Boost::context pthread)
    target_link_libraries(basic_coro ${Boost_LIBRARIES} pthread)

endif()
