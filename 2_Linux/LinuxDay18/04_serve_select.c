#include <header.h>
// 服务端
int main(){

    char *port = "8080";
    char *ip = "192.168.106.130";

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    // 使用setsockopt函数, 修改socket的行为
    // 如下: 要求如果某个端口处于time_wait状态, 允许重新使用
    int reuse = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));


    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(port));
    sockaddr.sin_addr.s_addr = inet_addr(ip);
    int ret =bind(socket_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr) );
    ERROR_CHECK(ret, -1, "bind");
    listen(socket_fd, 10);
    int net_fd = accept(socket_fd, NULL, NULL);

    fd_set set;
    while(1){
        FD_ZERO(&set);
        FD_SET(STDIN_FILENO, &set);
        FD_SET(net_fd, &set);

        select(net_fd+1, &set, NULL, NULL, NULL);

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
                printf("对端关闭 \n");
                break;
            }
            printf("buf: %s \n", buf);
        }
    }


    close(net_fd);
    close(socket_fd);

    return 0;
}

