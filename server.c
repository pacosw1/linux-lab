/*
* server1.c - a simple local server program.
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int server_sockfd, client_sockfd;
    int server_len, client_len;

    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    /* Remove any old socket and create an unnamed socket for the server. */
    unlink("server_socket");

    int ClientPort = 4000;
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    /* Name the socket. */
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(ClientPort); /* Local port */

    server_len = sizeof(server_address);

    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
    /* Create a connection queue and wait for clients. */
    listen(server_sockfd, 5);
    while (1)
    {
        char ch;
        printf("server waiting\n");
        printf("%s", (inet_ntoa(client_address.sin_addr)));
        /* Accept a connection. */
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd,
                               (struct sockaddr *)&client_address, &client_len);

        if (client_sockfd)
        {
            printf("Client connected");
        }
        /* We can now read/write to client on client_sockfd. */
        read(client_sockfd, &ch, 1);

        write(client_sockfd, &ch, 1);
        close(client_sockfd);
    }
}