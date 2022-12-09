#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <sys/msg.h>

#include <memory>
#include <chrono>

#include "../utils.hpp"

int main(int argc, char* argv[])
{
    int msgid = msgget((key_t)1234, O_RDONLY);
    if (msgid == -1)
    {
        perror("msgget error\n");
        return EXIT_FAILURE;
    }

    std::unique_ptr<struct Data> data(new struct Data);

    size_t size = 0;
    size_t counter = 0;
    auto start = std::chrono::high_resolution_clock::now();
    while (counter < RUN_TIMES)
    {
        msgrcv(msgid, data->buffer, BUFFER_LEN, data->iSignal, 0);
        size = strlen(data->buffer);
#ifdef DEBUG
        printf("[%ld] Current txt (%ld bytes)\n", counter, size);
        // printf("[%ld] Current txt (%ld bytes): %s\n", counter, size, data->buffer);
#endif
        bzero(data->buffer, BUFFER_LEN);
        ++counter;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double>(end - start);
    printf("Process %ld bytes package %ld times, cost %fs\n", size, counter, duration.count());

    msgctl(msgid, IPC_RMID, nullptr);

    return EXIT_SUCCESS;
}