#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>

int main(int argc, char* argv[]) {

    // Initial sockaddr
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = PF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(8000);

    // Create socket fd
    int serverfd = socket(PF_INET, SOCK_STREAM, 0);
    if (serverfd == -1) {
        perror("Server socket error.\n");
        close(serverfd);
        return EXIT_FAILURE;
    }

    // Bind sockaddr to socket fd
    if (bind(serverfd, (struct sockaddr*)&addr, sizeof(struct sockaddr)) == -1) {
        perror("Server bind error.\n");
        close(serverfd);
        return EXIT_FAILURE;
    }

    // Start listen client request
    if (listen(serverfd, 5) == -1) {
        perror("Server bind error.\n");
        close(serverfd);
        return EXIT_FAILURE;
    }

    // Accept client request
    struct sockaddr_in clientaddr;
    socklen_t size = sizeof(clientaddr);
    int clientfd = accept(serverfd, (struct sockaddr*)&clientaddr, &size);
    if (clientfd == -1) {
        perror("Server bind error.\n");
        close(serverfd);
        return EXIT_FAILURE;
    }

    char buffer[1024];
    bzero(buffer, sizeof(buffer));
    // Send check-in message
    printf("Accept client %s\n", inet_ntoa(clientaddr.sin_addr));
    strcpy(buffer, "Welcome to server.");
    send(clientfd, buffer, strlen(buffer), 0);
    bzero(buffer, strlen(buffer));

    while (true) {
        // Recv client message
        if (recv(clientfd, buffer, sizeof(buffer), 0) <= 0) {
            perror("Server recv error.\n");
        } else if (strcmp(buffer, "Quit") == 0 or strcmp(buffer, "quit") == 0) {
            break;
        } else {
            // Echo back message
            printf("Recv from client: %s\n", buffer);
            send(clientfd, buffer, strlen(buffer), 0);
            bzero(buffer, strlen(buffer));
        }
    }

    // Close socket fds
    close(serverfd);
    close(clientfd);

    return EXIT_SUCCESS;
}
