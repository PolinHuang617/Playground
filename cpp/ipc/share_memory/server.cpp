#include <cstdio>
#include <unistd.h>
#include <sys/shm.h>

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
    data->iSignal = 0;
    bzero(data->buffer, BUFFER_LEN);
    std::string str = message;
    for (size_t i = 0; i < (BUFFER_LEN / message.size() - 1); ++i)
    {
        str += message;
    }

    size_t counter = 0;
    while (true)
    {
        if (data->iSignal != 1)
        {
            strcpy(data->buffer, str.c_str());
            data->iSignal = 1;
#ifdef DEBUG
            printf("[%ld] write text (%ld bytes) to shared memory: %s\n", counter, strlen(data->buffer), data->buffer);
#endif
            ++counter;
        }

        if (counter >= RUN_TIMES)
        {
            break;
        }
    }

    data = nullptr;
    shmdt(shm);
    printf("End proress.\n");

    return EXIT_SUCCESS;
}