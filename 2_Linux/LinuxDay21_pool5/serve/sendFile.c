#include "head.h"

typedef struct train_s{
    int len;
    char buf[1000];
} train_t;

// 参数: 用来和指定客户端通信的socket的文件描述符
int sendFile(int net_fd){


    train_t file_name;
    bzero(&file_name, sizeof(file_name));

    char *str = "1b.txt";
    memcpy(file_name.buf, str, strlen(str));
    file_name.len = strlen(str);
    send(net_fd, &file_name, sizeof(int)+file_name.len, 0);

    // 发送文件内容
    int file_fd = open(str, O_RDONLY);


    // 获取文件大小
    struct stat st;
    memset(&st, 0, sizeof(st));
    fstat(file_fd, &st);
    //printf("file_size: %ld \n", st.st_size);
    // 把文件大小发送给客户端
    send(net_fd, &st.st_size, sizeof(off_t), MSG_NOSIGNAL);

    // 循环读取大文文件, 循环发送
    while(1){

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


