#include <header.h>

int main(){

    char *port = "8080";
    char *ip = "192.168.106.130";

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(port));
    sockaddr.sin_addr.s_addr = inet_addr(ip);

    connect(socket_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr));
    
    // 第一版: 信息没有边界
    // 接收文件名, 并创建
    //char file_name[60] = {0};
    //recv(socket_fd, file_name, sizeof(file_name), 0);
    //int file_fd = open(file_name, O_RDWR|O_CREAT, 0666);
    // 接收文件内容, 写入
    //char buf[1000] = {0};
    //ssize_t recv_num = recv(socket_fd, buf, sizeof(buf), 0);
    //write(file_fd, buf, recv_num);


    // 信息在应用层有边界
    int file_name_len;
    recv(socket_fd, &file_name_len, sizeof(int), 0);

    char file_name[60] = {0};
    recv(socket_fd,file_name, file_name_len, 0 );

    int file_fd = open(file_name, O_RDWR|O_CREAT, 0600);

    int len;
    recv(socket_fd, &len, sizeof(int), 0);
    char buf[1000] = {0};
    recv(socket_fd,buf, len, 0 );

    write(file_fd, buf, len);

    close(file_fd);
    close(socket_fd);
    return 0;
}

