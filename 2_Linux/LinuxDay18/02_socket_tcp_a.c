#include <header.h>
// 服务端
int main(){

    char *port = "8080";
    char *ip = "192.168.106.130";

    // 掉用socket函数创建一个socket对象
    // 并且获得这个对象的文件描述符
    // 我们在创建这个socket对象, 要求它使用ip和tcp协议
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    // 定义ipv4格式的结构, 描述ip和端口
    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(port));
    sockaddr.sin_addr.s_addr = inet_addr(ip);
    // 给socket对象设置端口, ip
    bind(socket_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr) );

    // 开启socket对象对端口的监听
    // 取消:输入输出缓冲区
    // 创建全连接半链接队列(用来三次握手)
    listen(socket_fd, 10);

    // accept: 获取全连接队列的一个完整链接(经过三次握手)
    //         创建一个专门为某个客户端服务的socket对象
    //
    //         并且, 可以同时通过accept拿到对应客户端的ip和端口
    printf("before accept \n");
    int net_fd = accept(socket_fd, NULL, NULL);
    printf("after accept \n");

    char buf[60] = {0};
    recv(net_fd, buf, sizeof(buf), 0);
    printf("buf: %s \n", buf);

    send(net_fd, "nihao", 5, 0);


    close(net_fd);
    close(socket_fd);

    return 0;
}

