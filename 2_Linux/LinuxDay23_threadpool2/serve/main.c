#include "head.h"

int main(){

    // 初始化参数
    // 同时创建子线程
    status_t status;
    initStatus(&status, 4);

    // 初始化socket
    int socket_fd;
    initSocket(&socket_fd, "8080", "192.168.106.130");

    // epoll
    int epoll_fd = epoll_create(1);
    addEpoll(epoll_fd, socket_fd);

    while(1){

        struct epoll_event list[10];
        int epoll_num = epoll_wait(epoll_fd, list, 10, -1);

        for(int i=0; i<epoll_num; i++){
            int fd = list[i].data.fd;

            if(fd == socket_fd){
                // 说明有新链接进来 -> 放入队列
                int net_fd = accept(socket_fd, NULL, NULL);

                pthread_mutex_lock(&status.lock);
                enQueue(&status.queue, net_fd);
                pthread_cond_broadcast(&status.cond );
                pthread_mutex_unlock(&status.lock);
            }
        }

    }
    return 0;
}

