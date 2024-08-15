#include <header.h>

// 通过fork函数, 创建子进程
int main(){

    printf("123 \n");

    pid_t pid = fork();

    printf("pid: %d \n", pid);

    while(1);

    return 0;
}

