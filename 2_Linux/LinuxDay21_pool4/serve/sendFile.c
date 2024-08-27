#include "head.h"

typedef struct train_s{
    int len;
    char buf[1000];
} train_t;

void func(int num){
    printf("num: %d \n", num);
}

// 给客户端回传文件
// 参数: 用来和指定客户端通信的socket的文件描述符
int sendFile(int net_fd){

    signal(13, func);

    train_t file_name;
    bzero(&file_name, sizeof(file_name));

    char *str = "1b.txt";
    memcpy(file_name.buf, str, strlen(str));
    file_name.len = strlen(str);
    send(net_fd, &file_name, sizeof(int)+file_name.len, 0);

    // 发送文件内容
    int file_fd = open(str, O_RDONLY);


    // 循环读取大文文件, 循环发送
    while(1){

        sleep(1);
        printf("send once \n");

        char buf[1000] = {0};
        int read_num = read(file_fd, buf, sizeof(buf));
        if(read_num == 0){
            // 文件读完
            break;
        }
        
        int ret = send(net_fd, &read_num, sizeof(int), MSG_NOSIGNAL);
        if(ret == -1){
            // 说明对方断开链接
            printf("对方断开链接 \n");
            break;
        }
        ret = send(net_fd, buf, read_num, MSG_NOSIGNAL);
        if(ret == -1){
            // 说明对方断开链接
            printf("对方断开链接 \n");
            break;
        }
    }

    close(file_fd);
    return 0;
}


