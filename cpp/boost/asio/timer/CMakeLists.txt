set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/tutorial/timer)

set(BOOST_ROOT /home/polin/Library/boost_1_80_0)
# set(Boost_NO_SYSTEM_PATH ON)

find_package(Boost REQUIRED)
if(Boost_FOUND)
    MESSAGE( STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}." )
	MESSAGE( STATUS "Boost_LIBRARY_DIRS = ${Boost_LIBRARY_DIRS}." )
	MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}." )
	MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}." )

	include_directories(${Boost_INCLUDE_DIRS})

    add_executable(sync_timer sync_timer.cpp)
    set_property(TARGET sync_timer PROPERTY CXX_STANDARD 17)
    target_link_libraries(sync_timer ${Boost_LIBRARIES} pthread)

    add_executable(async_timer async_timer.cpp)
    set_property(TARGET async_timer PROPERTY CXX_STANDARD 17)
    target_link_libraries(async_timer ${Boost_LIBRARIES} pthread)
   
    add_executable(strand strand.cpp)
    set_property(TARGET strand PROPERTY CXX_STANDARD 17)
    target_link_libraries(strand ${Boost_LIBRARIES} pthread)
   
endif()