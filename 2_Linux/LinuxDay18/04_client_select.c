#include <header.h>
// 客户端
int main(){

    char *port = "8080";
    char *ip = "192.168.106.130";

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(port));
    sockaddr.sin_addr.s_addr = inet_addr(ip);
    connect(socket_fd,(struct sockaddr *)&sockaddr, sizeof(sockaddr) );

    fd_set set;
    while(1){
        // 设置监听集合
        FD_ZERO(&set);
        FD_SET(STDIN_FILENO, &set);
        FD_SET(socket_fd, &set);

        // 使用select监听set集合是否可读
        select(socket_fd+1, &set, NULL, NULL, NULL);

        // 走到这: 有就绪
        if(FD_ISSET(STDIN_FILENO, &set)){
            // 读取标准输入, 给对方会信息
            char buf[60] = {0};
            read(STDIN_FILENO, buf, sizeof(buf));
            send(socket_fd, buf, sizeof(buf), 0);

        }
        if(FD_ISSET(socket_fd, &set)){
            // 读取网络数据-> 打印
            char buf[60] = {0};
            ssize_t ret = recv(socket_fd, buf, sizeof(buf), 0);
            if(ret == 0){
                printf("对端关闭 \n");
                break;
            }
            printf("buf: %s \n", buf);
        }

    }



    close(socket_fd);

    return 0;
}

