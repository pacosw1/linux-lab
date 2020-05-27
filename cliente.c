/*
* client1.c - a simple local client program.
*/
#include <sys/types.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("Missing input");
        return 0;
    }

    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;

    char ch = *argv[1];

    /* Create a socket for the client. */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    /* Name the socket, as agreed with the server. */
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    len = sizeof(address);
    /* Now connect our socket to the server's socket. */
    result = connect(sockfd, (struct sockaddr *)&address, len);
    if (result == -1)
    {
        perror("Conection error");
        exit(1);
    }
    /* We can now read/write via sockfd. */
    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);
    printf("char from server = %c\n", ch);
    close(sockfd);
    return 0;
}