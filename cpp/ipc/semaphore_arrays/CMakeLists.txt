set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/semaphore_arrays)

add_executable(sem_server server.cpp sem.hpp)
set_property(TARGET sem_server PROPERTY CXX_STANDARD 17)

add_executable(sem_client client.cpp sem.hpp)
set_property(TARGET sem_client PROPERTY CXX_STANDARD 17)

