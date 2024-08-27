#include <header.h>

// 自己手动实现一个recvn函数
// 要求这个函数具有读取指定的size字节个数据, 没有读到, 就不要返回
int recvn(int net_fd, char *buf, int size){

    return 0;
}
int main(){

    char *port = "8080";
    char *ip = "192.168.106.130";

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(port));
    sockaddr.sin_addr.s_addr = inet_addr(ip);

    connect(socket_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr));
    

    // 信息在应用层有边界
    int file_name_len;
    recv(socket_fd, &file_name_len, sizeof(int), 0);

    char file_name[60] = {0};
    recv(socket_fd,file_name, file_name_len, 0 );

    int file_fd = open(file_name, O_RDWR|O_CREAT, 0600);



    // 接收文件大小
    off_t file_size = 0;
    recv(socket_fd, &file_size, sizeof(off_t), MSG_WAITALL);
    printf("client: file_size: %ld \n", file_size);


    int current_size = 0;

    // 接收文件内容: 大文件, 循环接收, 循环写入磁盘文件
    while(1){

        int size;
        //int ret = recv(socket_fd, &size, sizeof(size), 0);
        int ret = recv(socket_fd, &size, sizeof(size), MSG_WAITALL);
        if(ret == 0){
            // 说明服务端传输完毕数据, 断开了链接
            break;
        }
        //printf("size: %d \n", size);

        char buf[1000] = {0};
        //ret = recv(socket_fd, buf, size, 0);
        ret = recv(socket_fd, buf, size, MSG_WAITALL);
        if(ret == 0){
            break;
        }

        write(file_fd, buf, size);

        current_size += size;

        printf(" \r current: %.2f ", 100 * (double)current_size/file_size);


    }

    close(file_fd);
    close(socket_fd);
    return 0;
}

