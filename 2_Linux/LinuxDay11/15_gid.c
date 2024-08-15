#include <header.h>

// 获得当前进程id, 同时,获得这个进程所在的组的id
int main(){

    if(fork() == 0){
        printf("son pid: %d;  group id: %d \n",getpid(), getpgrp());

    }else{
        printf("main pid: %d;  group id: %d \n",getpid(), getpgrp());

    }

    return 0;
}

