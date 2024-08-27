#include "head.h"

typedef struct train_s{
    int len;
    char buf[1000];
} train_t;

// 给客户端回传文件
// 参数: 用来和指定客户端通信的socket的文件描述符
int sendFile(int net_fd){

    // 第一个传输文件版本: 有问题, 数据没有边界, 客户端接收的时候无法区分
    // 给客户端发送个文件名
    //char *file_name = "1.txt";
    //send(net_fd, file_name, strlen(file_name), 0);
    // 发送文件内容: 先读取, 再发送
    //int file_fd = open(file_name, O_RDONLY);
    //char buf[1000] = {0};
    //ssize_t read_num = read(file_fd,buf, sizeof(buf));
    //send(net_fd, buf, read_num, 0);

    // 第二个版本: 给数据传输加边界 (高级一点: 在应用层自定义了一个协议 )
    train_t file_name;
    bzero(&file_name, sizeof(file_name));

    char *str = "1.txt";
    memcpy(file_name.buf, str, strlen(str));
    file_name.len = strlen(str);

    //send(net_fd, &file_name.len, sizeof(int), 0);
    //send(net_fd, file_name.buf, file_name.len, 0);

    send(net_fd, &file_name, sizeof(int)+file_name.len, 0);

    // 发送文件内容
    int file_fd = open(str, O_RDONLY);
    char buf[1000] = {0};
    int read_num = read(file_fd, buf, sizeof(buf));

    send(net_fd, &read_num, sizeof(int), 0);
    send(net_fd, buf, read_num, 0);


    return 0;
}


