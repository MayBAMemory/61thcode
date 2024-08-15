#include <header.h>

int main(){

    if(fork() == 0){
        // 子进程
        //while(1);

        sleep(20);

    }else{
        // 父进程

        // wait函数的作用, '等待'一个子进程退出, 给子进程收尸
        wait(NULL);
    }

    return 0;
}

