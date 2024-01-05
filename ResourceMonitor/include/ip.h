#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

void getIP() {
    char hostbuffer[256];
    int hostname;
    struct addrinfo hints, *res;

    hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    if (hostname == -1) {
        perror("gethostname");
        exit(1);
    }
    printf("\033[21;20HHostname: %s", hostbuffer);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if(getaddrinfo(hostbuffer, "http", &hints, &res) != 0) {
        perror("getaddrinfo");
        exit(1);
    }

    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &((struct sockaddr_in *)res->ai_addr)->sin_addr, ip, INET_ADDRSTRLEN);
    printf("\033[21;5HIP: %s", ip);
    freeaddrinfo(res);
}
