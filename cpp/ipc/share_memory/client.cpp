#include <cstdio>
#include <unistd.h>
#include <sys/shm.h>

#include <chrono>

#include "../utils.hpp"

int main(int argc, char** argv)
{
    int shmid = shmget((key_t)1234, sizeof(struct Data), 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        perror("shmget err.\n");
        return EXIT_FAILURE;
    }

    void* shm = shmat(shmid, (void*)0, 0);
    if (shm == (void*)-1)
    {
        perror("shmat err.\n");
        return EXIT_FAILURE;
    }

    struct Data* data = static_cast<struct Data*>(shm);

    size_t size = 0;
    size_t counter = 0;
    auto start = std::chrono::high_resolution_clock::now();
    while (true)
    {
        if (data->iSignal != 0)
        {
            size = strlen(data->buffer);
#ifdef DEBUG
            printf("[%ld] Current txt (%ld bytes): %s\n", counter, size, data->buffer);
#endif
            bzero(data->buffer, BUFFER_LEN);
            
            data->iSignal = 0;
            
            ++counter;
        }

        if (counter >= RUN_TIMES)
        {
            break;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double>(end - start);
    printf("Process %ld bytes package %ld times, cost %fs\n", size, counter, duration.count());

    data = nullptr;
    shmdt(shm);
    shmctl(shmid, IPC_RMID, 0);

    printf("End proress.\n");

    return EXIT_SUCCESS;
}