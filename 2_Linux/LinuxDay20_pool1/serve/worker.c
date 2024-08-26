#include "head.h"


// 子进程的核心执行函数: 一直循环, 一直recvmsg读取任务
// 参数: 用来和父进程通信的本地socket的文件描述
int doWorker(int local_socket){

    while(1){


        // 读取任务
        int net_fd;
        recvMsg(local_socket, &net_fd);

        // 执行任务: 服务客户端, 传文件
        toClientFile(net_fd);
        close(net_fd);
        
        // 通知父进程, 修改状态
        send(local_socket, "123", 3, 0);

    }

    return 0;
}


int toClientFile(int net_fd){

    send(net_fd, "hello", 5, 0);

    return 0;
}
