#include "head.h"

// 父进程的控制逻辑
int main(){

    // 启动子进程
    son_status_t list[4];
    initPool(list, 4);

    // 初始化socket链接
    int socket_fd;
    initSocket(&socket_fd, "8080", "192.168.106.130");

    int epoll_fd = epoll_create(1);
    // 放入监听: 三次握手的socket,  和子进程进行通信的本地socket
    addEpoll(epoll_fd, socket_fd);
    for(int i=0; i<4; i++){
        addEpoll(epoll_fd, list[i].local_socket);
    }

    while(1){
        struct epoll_event events[10];
        memset(events, 0, sizeof(events));
        
        int epoll_num = epoll_wait(epoll_fd, events, 10, -1);

        for(int i=0; i<epoll_num; i++){
            int fd = events[i].data.fd;

            if(fd == socket_fd){
                // 有新链接进来
                int net_fd = accept(socket_fd, NULL, NULL);
                // 把这个新的socket对象交给空闲的子进程处理
                toSonNetFd(list, 4, net_fd);

                close(net_fd);
                continue;
            }

            // 走到这:有子进程发信息
            for(int j=0; j<4; j++){
                if(list[j].local_socket == fd){
                    // 说明当前子进程, 要由忙状态改为闲状态
                    list[j].flag = FREE;
                    break;
                }
            }
        }
    }

    return 0;
}

