#include <header.h>

int main(){

    char *port = "8080";
    char *ip = "192.168.106.130";

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    int buflowat= 130;
    //设置接收缓冲区下限
    setsockopt(socket_fd,SOL_SOCKET,SO_RCVLOWAT,&buflowat,sizeof(int));


    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(port));
    sockaddr.sin_addr.s_addr = inet_addr(ip);

    connect(socket_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr));

    //  
    //  创建epoll对象: 这个epoll对象在内核
    //  里面包含监听集合(红黑树), 就绪集合(线性表)
    int epoll_fd = epoll_create(1);

    // 放入监听

    struct epoll_event event;
    event.events = EPOLLIN; // 监听可读
    event.data.fd = STDIN_FILENO;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &event);

    event.events = EPOLLIN;
    event.data.fd = socket_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &event);

    int flag = 0;
    while(1){

        // 开始监听
        // epoll_wait: 是个阻塞的函数, 体现在如果没有监听的文件描述符就绪, 就卡在这里

        struct epoll_event list[10];
        memset(list, 0, sizeof(list));
        int epoll_num = epoll_wait(epoll_fd, list, 10, -1);

        // 走到这: 一定意味着, 意味着,我们所监听的文件描述符至少有一个就绪
        // 处理就绪问题: 遍历就绪集合
        for(int i=0; i<epoll_num; i++){
            // fd: 就是要遍历的文件描述符
            int fd = list[i].data.fd;

            if(fd == socket_fd){

                char buf[60] = {0};
                int ret_recv = recv(socket_fd, buf, sizeof(buf), 0);
                if(ret_recv == 0){
                    printf("对端断开 \n");
                    flag = 1;
                    break;
                }
                printf("buf: %s \n", buf);


            }else if(fd == STDIN_FILENO){
                // 说明标准输入有内容
                char buf[60] = {0};
                read(STDIN_FILENO, buf, sizeof(buf));
                send(socket_fd, buf, sizeof(buf), 0);
            }
        }
        if(flag != 0){
            break;
        }

    }

    close(socket_fd);

    return 0;
}

