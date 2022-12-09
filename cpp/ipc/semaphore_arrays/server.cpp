#include <sys/shm.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>

#include "../utils.hpp"
#include "sem.hpp"

int main(int argc, char* argv[])
{
    int semID = getSem(100);

    if (!setSem(semID))
    {
        perror("Set sem failed.\n");
        return EXIT_FAILURE;
    }

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
        int ret = semctl(semID, 0, GETVAL);
        if (ret < 1)
        {
            // V
            strcpy(data->buffer, str.c_str());
            semUp(semID);
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

    return EXIT_SUCCESS;
}