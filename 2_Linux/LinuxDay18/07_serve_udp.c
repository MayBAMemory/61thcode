#include <header.h>
//基于udp协议的scoket通信的服务端
int main(){

    char *port = "8080";
    char *ip = "192.168.106.130";

    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    
    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(port));
    sockaddr.sin_addr.s_addr = inet_addr(ip);

    bind(socket_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr));

    // 读取客户端的数据
    struct sockaddr_in  sockaddr_recv;
    socklen_t len = sizeof(sockaddr);
    char buf[60] = {0};
    recvfrom(socket_fd, buf, sizeof(buf), 0, (struct sockaddr *)&sockaddr_recv, &len);
    printf("buf: %s \n", buf);

    // 回数据
    sendto(socket_fd, "123", 3, 0, (struct sockaddr *)&sockaddr_recv, sizeof(sockaddr_recv));

    close(socket_fd);

    return 0;
}

