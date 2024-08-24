#include <header.h>

// 群聊的客户端
int main(){

    char *port = "8080";
    char *ip = "192.168.106.130";

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(port));
    sockaddr.sin_addr.s_addr = inet_addr(ip);
    connect(socket_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr));


    fd_set set;
    while(1){
        FD_ZERO(&set);
        FD_SET(STDIN_FILENO, &set);
        FD_SET(socket_fd, &set);

        select(10, &set, NULL, NULL, NULL);

        if(FD_ISSET(STDIN_FILENO, &set)){
            char buf[60] = {0};
            read(STDIN_FILENO, buf, sizeof(buf));
            send(socket_fd, buf, sizeof(buf), 0);
        }
        if(FD_ISSET(socket_fd, &set)){
            char buf[60] = {0};
            int ret = recv(socket_fd, buf, sizeof(buf), 0);
            if(ret == 0){
                //socket对象可读, 并且读到数据0个
                printf("服务端断开链接 \n");
                break;
            }
            printf("buf: %s \n", buf);

        }
    }

    close(socket_fd);
    return 0;
}

