#include <header.h>
// 客户端
int main(){

    char *port = "8080";
    char *ip = "192.168.106.130";

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(port));
    sockaddr.sin_addr.s_addr = inet_addr(ip);
    // 可能服务端已经准备好(开始listen了)
    // 就意味着, 可以发起三次握手
    // connect: 进行三次握手
    connect(socket_fd,(struct sockaddr *)&sockaddr, sizeof(sockaddr) );
    


    return 0;
}

