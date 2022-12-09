#include <sys/shm.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>

#include <chrono>

#include "../utils.hpp"
#include "sem.hpp"

int main(int argc, char* argv[])
{
    int semID = getSem(100);

    int shmID = shmget((key_t)1234, sizeof(struct Data), IPC_CREAT | 0666);
    if (shmID == -1)
    {
        perror("shmget err.\n");
        return EXIT_FAILURE;
    }

    void* shm = shmat(shmID, (void*)0, 0);
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
        int ret = semctl(semID, 0, GETVAL);
        if (ret > 0  and strlen(data->buffer) > 0)
        {
            size = strlen(data->buffer);
#ifdef DEBUG
            printf("[%ld] Current txt (%ld bytes): %s\n", counter, size, data->buffer);
#endif
            bzero(data->buffer, BUFFER_LEN);
            // P
            semDown(semID);

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
    shmctl(shmID, IPC_RMID, 0);

    delSem(semID);

    return EXIT_SUCCESS;
}
