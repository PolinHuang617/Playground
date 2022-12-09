#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>

#include <memory>
#include <chrono>

#include "../utils.hpp"

int main(int argc, char* argv[])
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_LOCAL;  // Local

    int sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("Client socket error.\n");
        return EXIT_FAILURE;
    }

    if (connect(sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr)) == -1)
    {
        perror("Client connect error.\n");
        return EXIT_FAILURE;
    }

    printf("Connect to server.\n");

    std::unique_ptr<struct Data> data(new struct Data);

    size_t size = 0;
    size_t counter = 0;
    auto start = std::chrono::high_resolution_clock::now();
    while (counter < RUN_TIMES)
    {
        recv(sockfd, data->buffer, BUFFER_LEN, 0);
        size = strlen(data->buffer);
#ifdef DEBUG
        printf("[%ld] Current txt (%ld bytes): %s\n", counter, size, data->buffer);
#endif
        data->iSignal = 0;
        send(sockfd, data.get(), sizeof(data->iSignal), 0);

        ++counter;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double>(end - start);
    printf("Process %ld bytes package %ld times, cost %fs\n", size, counter, duration.count());

    close(sockfd);

    return EXIT_SUCCESS;
}