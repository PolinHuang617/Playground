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
    addr.sin_family = PF_INET;
    addr.sin_port = htons(8000);
    inet_pton(PF_INET, "192.168.218.6", &addr.sin_addr.s_addr);

    // Create socket fd
    int clientfd = socket(PF_INET, SOCK_STREAM, 0);
    if (clientfd == -1) {
        perror("Client socket error.\n");
        close(clientfd);
        return EXIT_FAILURE;
    }

    // Connect to server
    if (connect(clientfd, (struct sockaddr*)&addr, sizeof(struct sockaddr)) == -1) {
        perror("Client connect error.\n");
        close(clientfd);
        return EXIT_FAILURE;
    }

    char buffer[1024];
    bzero(buffer, sizeof(buffer));

    // Recv hello message
    if (recv(clientfd, buffer, sizeof(buffer), 0) == -1) {
        perror("Client recv error.\n");
        close(clientfd);
        return EXIT_FAILURE;
    }
    printf("Recv message: %s\n", buffer);

    while (true) {
        // Send message
        printf("Input something: ");
        scanf("%s", buffer);
        if (strcmp(buffer, "Quit") == 0 or strcmp(buffer, "quit") == 0) {
            break;
        }
        send(clientfd, buffer, strlen(buffer), 0);
        bzero(buffer, strlen(buffer));

        // Suspending until revc echo message from server
        recv(clientfd, buffer, sizeof(buffer), 0);

        printf("Echo message: %s\n", buffer);
    }
    // Close socket fd
    close(clientfd);

    return EXIT_SUCCESS;
}
