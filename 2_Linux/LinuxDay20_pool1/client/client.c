#include <header.h>

int main(){

    char *port = "8080";
    char *ip = "192.168.106.130";

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(port));
    sockaddr.sin_addr.s_addr = inet_addr(ip);

    connect(socket_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr));
    

    char buf[60] = {0};
    recv(socket_fd, buf, sizeof(buf), 0);
    printf("buf: %s \n", buf);


    close(socket_fd);
    return 0;
}

