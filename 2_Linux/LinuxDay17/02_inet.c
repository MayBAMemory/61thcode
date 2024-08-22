#include <header.h>

int main(){

    char *port = "8080";
    char *ip = "192.168.2.38";

    struct sockaddr_in  sockaddr;
    sockaddr.sin_family = AF_INET; // 指明底层使用ipv4协议
    sockaddr.sin_port =  htons(atoi(port)); // 先把字符串 -> int  (小端) -> 大端端口
    sockaddr.sin_addr.s_addr = inet_addr(ip);


    return 0;
}

