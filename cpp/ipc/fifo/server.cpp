#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <sys/stat.h>

#include <memory>

#include "../utils.hpp"

int main(int argc, char* argv[])
{
    mkfifo("/tmp/fifo", 0664);

    int fd = open("/tmp/fifo", O_WRONLY);
    if (fd == -1)
    {
        perror("fifo error");
        return EXIT_FAILURE;
    }

    int feedbackfd = open("/tmp/feedback", O_RDONLY);
    if (feedbackfd == -1)
    {
        perror("feedback error");
        return EXIT_FAILURE;
    }

    std::unique_ptr<struct Data> data(new struct Data);
    data->iSignal = 0;
    strcpy(data->buffer, message.c_str());
    for (size_t i = 0; i < (BUFFER_LEN / message.size() - 1); ++i)
    {
        strcat(data->buffer, message.c_str());
    }

    size_t counter = 0;
    while (counter < RUN_TIMES)
    {
        if (data->iSignal != 1)
        {
            data->iSignal = 1;
            write(fd, data->buffer, BUFFER_LEN);
#ifdef DEBUG
            printf("[%ld] write text (%ld bytes) to fifo: %s\n", counter, strlen(data->buffer), data->buffer);
#endif            
            ++counter;
        }
        read(feedbackfd, data.get(), sizeof(data->iSignal));
    }

    close(fd);
    close(feedbackfd);

    return EXIT_SUCCESS;
}