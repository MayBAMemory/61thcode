#include <header.h>
// 客户端: 断开重连
int main(){

    char *port = "8080";
    char *ip = "192.168.106.130";

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(port));
    sockaddr.sin_addr.s_addr = inet_addr(ip);
    connect(socket_fd,(struct sockaddr *)&sockaddr, sizeof(sockaddr) );

    int epoll_fd = epoll_create(1);

    // 放入监听
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = STDIN_FILENO;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &event);

    event.data.fd = socket_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &event);


    int flag = 0;
    while(1){

        struct epoll_event list[10];
        memset(list, 0, sizeof(list));

        int epoll_num = epoll_wait(epoll_fd, list, 10, -1);

        for(int i=0; i<epoll_num; i++){
            int fd = list[i].data.fd;

            if(fd == STDIN_FILENO){
                char buf[60] = {0};
                read(STDIN_FILENO, buf, sizeof(buf));
                send(socket_fd, buf, sizeof(buf), 0);
            }
            if(fd == socket_fd){
                char buf[60] = {0};
                ssize_t ret = recv(socket_fd, buf, sizeof(buf), 0);
                if(ret == 0){
                    printf("对端关闭 \n");
                    flag = 1;
                    break;
                }
                printf("buf: %s \n", buf);

            }
        }

        if(flag != 0){
            break;
        }
    }

    close(socket_fd);

    return 0;
}

