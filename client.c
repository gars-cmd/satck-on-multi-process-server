/*
** client.c -- a stream socket client demo
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "stack.h"

#include <arpa/inet.h>

#define PORT "3490" // the port client will be connecting to

#define MAXDATASIZE 1024 // max number of bytes we can get at once

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
    int sockfd, numbytes;
    char buf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    if (argc != 2)
    {
        fprintf(stderr, "usage: client hostname\n");
        exit(1);
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for (p = servinfo; p != NULL; p = p->ai_next)
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1)
        {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(sockfd);
            // perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL)
    {
        // fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
              s, sizeof s);
    printf("DEBUG:client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure
    printf("DEBUG:enter a command for the server -->");
    scanf("%[^\n]%*c", &buf);
    // printf("buf = %s\n", buf);
    if ((numbytes = send(sockfd, buf, MAXDATASIZE - 1, 0)) == -1)
    {
        perror("send...");
        exit(1);
    }

    else
    {
        // printf("buff2 = %s of size %d\n", buf, strlen(buf));
        // printf("DEBUG:the send success\n");
        fflush(stdout);
    }
    char *cmd = malloc_X(4);
    memset(cmd, 0, MAXDATASIZE);
    memcpy(cmd, buf, 4);
    if (strcmp(cmd, "TOP") != 0)
    {
        close(sockfd);
        free_X(cmd);
        exit(0);
    }
    else
    {
        // printf("cmd = -%s-\t|buf = %s\n", cmd, buf);
        free_X(cmd);
        memset(buf, 0, MAXDATASIZE);
        if ((numbytes = recv(sockfd, buf, MAXDATASIZE, 0)) == -1)
        {
            perror("ERROR:recv...");
            exit(1);
        }
        else
        {
            buf[numbytes] = '\0';
            printf("OUTPUT:%s", buf);
            close(sockfd);
        }
    }
    return 0;
}