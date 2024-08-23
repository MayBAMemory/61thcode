#include <header.h>
// 服务端: 断开重连
int main(){

    char *port = "8080";
    char *ip = "192.168.106.130";

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    int reuse = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(port));
    sockaddr.sin_addr.s_addr = inet_addr(ip);
    int ret =bind(socket_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr) );
    ERROR_CHECK(ret, -1, "bind");
    listen(socket_fd, 10);

    int net_fd;
    fd_set base_set;
    FD_ZERO(&base_set);
    FD_SET(socket_fd, &base_set);
    while(1){
        fd_set set;
        memcpy(&set, &base_set, sizeof(base_set));

        select(100, &set, NULL, NULL, NULL);

        if(FD_ISSET(socket_fd, &set)){
            net_fd = accept(socket_fd, NULL, NULL);
            FD_SET(net_fd, &base_set);
            FD_SET(STDIN_FILENO, &base_set);
            FD_CLR(socket_fd, &base_set);
            continue;
        }
        if(FD_ISSET(STDIN_FILENO, &set)){
            // 读取标准输入
            char buf[60] = {0};
            read(STDIN_FILENO, buf, sizeof(buf));
            send(net_fd, buf, sizeof(buf), 0);
        }

        if(FD_ISSET(net_fd, &set)){
            // 读网络数据-> 打印
            char buf[60] = {0};
            ssize_t ret = recv(net_fd, buf, sizeof(buf), 0);
            if(ret == 0){
                FD_CLR(STDIN_FILENO, &base_set);
                FD_CLR(net_fd, &base_set);
                close(net_fd);
                FD_SET(socket_fd, &base_set);
                continue;
            }
            printf("buf: %s \n", buf);
        }
    }


    close(net_fd);
    close(socket_fd);

    return 0;
}

