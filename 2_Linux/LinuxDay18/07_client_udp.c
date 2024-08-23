#include <header.h>
//基于udp协议的socket通信的客户端
int main(){

    char *port = "8080";
    char *ip = "192.168.106.130";

    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

    // 给服务器发送数据
    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(port));
    sockaddr.sin_addr.s_addr = inet_addr(ip);
    sendto(socket_fd, "hello", 5, 0, (struct sockaddr *)&sockaddr, sizeof(sockaddr));

    // 接收服务器回复的数据
    char buf[60] = {0};
    printf("---- \n");
    recvfrom(socket_fd, buf, sizeof(buf), 0, NULL, NULL);
    printf("buf: %s \n", buf);

    close(socket_fd);
    return 0;
}

