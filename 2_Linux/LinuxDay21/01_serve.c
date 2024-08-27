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

    int epoll_fd = epoll_create(1);

    // 放入监听
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = socket_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &event);

    while(1){

        struct epoll_event list[10];
        int epoll_num = epoll_wait(epoll_fd, list, 10, -1);

        for(int i=0; i<epoll_num; i++){
            int fd = list[i].data.fd;

            if(fd == socket_fd){
                net_fd = accept(socket_fd, NULL, NULL);
                // 移除socket_fd监听
                // 放入标准输入和net_fd的监听
                epoll_ctl(epoll_fd, EPOLL_CTL_DEL, socket_fd, NULL);

                event.data.fd = STDIN_FILENO;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &event);

                event.data.fd = net_fd;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, net_fd, &event);
                continue;
            }

            if(fd == STDIN_FILENO){
                char buf[60] = {0};
                read(STDIN_FILENO, buf, sizeof(buf));
                send(net_fd, buf, sizeof(buf), 0);

            }
            if(fd == net_fd){
                char buf[60] = {0};
                ssize_t ret = recv(net_fd, buf, sizeof(buf), 0);
                if(ret == 0){
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, STDIN_FILENO, NULL);
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, net_fd, NULL);
                    close(net_fd);

                    event.data.fd = socket_fd;
                    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &event);

                    continue;
                }
                printf("buf: %s \n", buf);

            }

        }
    }


    close(net_fd);
    close(socket_fd);

    return 0;
}

