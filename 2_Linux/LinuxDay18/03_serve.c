#include <header.h>
// 服务端
int main(){

    char *port = "8080";
    char *ip = "192.168.106.130";

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(port));
    sockaddr.sin_addr.s_addr = inet_addr(ip);
    bind(socket_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr) );
    listen(socket_fd, 10);
    int net_fd = accept(socket_fd, NULL, NULL);

    // ------
    while(1){
        // 读取标准输入
        char buf[60] = {0};
        read(STDIN_FILENO, buf, sizeof(buf));
        send(net_fd, buf, sizeof(buf), 0);

        // 读网络数据-> 打印
        bzero(buf, sizeof(buf));
        recv(net_fd, buf, sizeof(buf), 0);
        printf("buf: %s \n", buf);

    }


    close(net_fd);
    close(socket_fd);

    return 0;
}

