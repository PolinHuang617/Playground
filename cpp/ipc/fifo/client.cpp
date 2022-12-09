#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <sys/stat.h>

#include <memory>
#include <chrono>

#include "../utils.hpp"

int main(int argc, char* argv[])
{
    int fd = open("/tmp/fifo", O_RDONLY);
    if (fd == -1)
    {
        perror("fifo error");
        return EXIT_FAILURE;
    }

    mkfifo("/tmp/feedback", 0664);
    int feedbackfd = open("/tmp/feedback", O_WRONLY);
    if (feedbackfd == -1)
    {
        perror("feedback error");
        return EXIT_FAILURE;
    }

    std::unique_ptr<struct Data> data(new struct Data);

    size_t size = 0;
    size_t counter = 0;
    auto start = std::chrono::high_resolution_clock::now();
    while (counter < RUN_TIMES)
    {
        read(fd, data->buffer, BUFFER_LEN);
        size = strlen(data->buffer);
#ifdef DEBUG
        printf("[%ld] Current txt (%ld bytes): %s\n", counter, size, data->buffer);
#endif
        data->iSignal = 0;
        bzero(data->buffer, BUFFER_LEN);
        write(feedbackfd, data.get(), sizeof(data->iSignal));

        ++counter;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double>(end - start);
    printf("Process %ld bytes package %ld times, cost %fs\n", size, counter, duration.count());

    close(fd);
    close(feedbackfd);

    return EXIT_SUCCESS;
}