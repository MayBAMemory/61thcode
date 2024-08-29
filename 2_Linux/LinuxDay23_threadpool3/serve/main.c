#include "head.h"

// 管道
int pipe_fd[2];

void func(int num){
    // 写管道
    write(pipe_fd[1], "1", 1);
}
int main(){

    pipe(pipe_fd);

    if(fork() != 0){
        // 父进程
        signal(2, func);

        wait(NULL);
        printf("子进程退出 \n");
        exit(0);
    }
    // 子进程
    // 脱离前台进程组
    setpgid(0, 0);


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

    // epoll监听管道的读端
    addEpoll(epoll_fd, pipe_fd[0]);
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
            }else if(fd == pipe_fd[0]){
                // 走到这, 说明管道可读, 说明有人写管道 -> 父进程的信号捕捉的函数
                // -> 父进程收到了信号
                // -> 要求子进程退出
                char buf[10] = {0};
                read(pipe_fd[0], buf, sizeof(buf));
                
                // 走到这 -> 有退出的需求 -> 希望子线程先退出


                for(int j=0; j<4; j++){
                    pthread_cancel(status.list[j]);
                }

                for(int k=0; k<4; k++){
                    pthread_join(status.list[k], NULL);
                }
                // 走到-> 所有子线程退出
                // 主线程也退出
                printf("所有子线程退出, 主线程也退出 \n");
                pthread_exit(NULL);
            }
        }

    }
    return 0;
}

