#include <cstdio>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <memory>

#include "../utils.hpp"

int main(int argc, char* argv[])
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;  // IPv4
    addr.sin_addr.s_addr = htonl(INADDR_ANY);  // localhost
    addr.sin_port = htons(PORT+1);

    int serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverfd == -1)
    {
        perror("Server socket error.\n");
        return EXIT_FAILURE;
    }

    if (bind(serverfd, (struct sockaddr*)&addr, sizeof(struct sockaddr)) == -1)
    {
        perror("Server bind error.\n");
        return EXIT_FAILURE;
    }

    if (listen(serverfd, 1) == -1)
    {
        perror("Server listen error.\n");
        return EXIT_FAILURE;
    }

    struct sockaddr_in clientaddr;
    socklen_t size = sizeof(clientaddr);
    int clientfd = accept(serverfd, (struct sockaddr*)&clientaddr, &size);
    if (clientfd == -1)
    {
        perror("Server accept error.\n");
        return EXIT_FAILURE;
    }

    // printf("Accept client %s\n", inet_ntoa(clientaddr.sin_addr));
    // send(clientfd, "Welcome to server\n", 21, 0);

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
            send(clientfd, data->buffer, BUFFER_LEN, 0);
#ifdef DEBUG
            printf("[%ld] write text (%ld bytes) to socket: %s\n", counter, strlen(data->buffer), data->buffer);
#endif
            ++counter;
        }
        recv(clientfd, data.get(), sizeof(data->iSignal), 0);
    }

    close(serverfd);
    close(clientfd);

    return EXIT_SUCCESS;
}