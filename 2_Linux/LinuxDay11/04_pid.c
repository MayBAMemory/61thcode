#include <header.h>

// 获取当前进程的id  和 其父id
int main(){

    printf("pid: %d \n", getpid());
    printf("ppid: %d \n", getppid());

    while(1);
    return 0;
}

