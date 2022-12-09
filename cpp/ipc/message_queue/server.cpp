#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <sys/msg.h>

#include <memory>

#include "../utils.hpp"

int main(int argc, char* argv[])
{
    int msgid = msgget((key_t)1234, IPC_CREAT | O_WRONLY | 0664);
    if (msgid == -1)
    {
        perror("msgget error\n");
        return EXIT_FAILURE;
    }

    std::unique_ptr<struct Data> data(new struct Data);
    data->iSignal = 1;
    strcpy(data->buffer, message.c_str());
    for (size_t i = 0; i < (BUFFER_LEN / message.size() - 1); ++i)
    {
        strcat(data->buffer, message.c_str());
    }

    size_t counter = 0;
    while (counter < RUN_TIMES)
    {
        msgsnd(msgid, data->buffer, BUFFER_LEN, 0);
#ifdef DEBUG
        printf("[%ld] write text (%ld bytes) to message queue\n", counter, strlen(data->buffer));
        // printf("[%ld] write text (%ld bytes) to message queue: %s\n", counter, strlen(data->buffer), data->buffer);
#endif            
        ++counter;
    }

    return EXIT_SUCCESS;
}