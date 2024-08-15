#include <header.h>

// 获得当前进程id, 同时,获得这个进程所在的组的id
int main(){

    if(fork() == 0){
        printf("son pid: %d;  group id: %d \n",getpid(), getpgrp());

        // 准备让子进程, 脱离当前进程组 (不想和父进程保持在同一个进程组了)

        setpgid( 0, 0);
        printf("son pid: %d;  group id: %d \n",getpid(), getpgrp());

    }else{
        printf("main pid: %d;  group id: %d \n",getpid(), getpgrp());

        sleep(1);
    }

    return 0;
}

