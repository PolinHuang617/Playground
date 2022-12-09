#include <fcntl.h>
#include <unistd.h>
#include <cstdio>

#include <string>
#include <memory>
#include <chrono>

#include "../utils.hpp"

int main(int argc, char* argv[])
{
    // Pipe fd: fd[0] - read, fd[1] - write
    int fd[2];
    int feedbackfd[2];

    std::unique_ptr<struct Data> data(new struct Data);
    size_t counter = 0;

    if (pipe(fd) == -1)
    {
        perror("pipe error");
        return EXIT_FAILURE;
    }

    if (pipe(feedbackfd) == -1)
    {
        perror("feedback error");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    // Base
    if (pid > 0)
    {
        close(fd[0]); // Close read
        close(feedbackfd[1]);  // Close feedback write 
        
        data->iSignal = 0;
        strcpy(data->buffer, message.c_str());
        for (size_t i = 0; i < (BUFFER_LEN / message.size() - 1); ++i)
        {
            strcat(data->buffer, message.c_str());
        }

        while (counter < RUN_TIMES)
        {
            if (data->iSignal != 1)
            {
                data->iSignal = 1;
                
                write(fd[1], data.get(), sizeof(data->iSignal) + BUFFER_LEN);
#ifdef DEBUG
                printf("[%ld] write text (%ld bytes) to pipe: %s\n", counter, strlen(data->buffer), data->buffer);
#endif
                data->iSignal = 0;

                ++counter;
            }
            read(feedbackfd[0], data.get(), sizeof(data->iSignal));
        }

        close(fd[1]);
        close(feedbackfd[0]);
    }
    // Derived
    else if (pid == 0)
    {
        close(fd[1]);  // Close fd write
        close(feedbackfd[0]);  // Close feedback read 
 
        size_t size = 0;
        data->iSignal = 1;
        auto start = std::chrono::high_resolution_clock::now();
        while (counter < RUN_TIMES)
        {
            read(fd[0], data.get(), sizeof(data->iSignal) + BUFFER_LEN);
            if (data->iSignal != 0)
            {
                size = strlen(data->buffer);
#ifdef DEBUG
                printf("[%ld] Current txt (%ld bytes): %s\n", counter, size, data->buffer);
#endif
                data->iSignal = 0;
                write(feedbackfd[1], data.get(), sizeof(data->iSignal));

                ++counter;
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double>(end - start);
        printf("Process %ld bytes package %ld times, cost %fs\n", size, counter, duration.count());

        close(fd[0]);
        close(feedbackfd[1]);
    }

    return EXIT_SUCCESS;
}