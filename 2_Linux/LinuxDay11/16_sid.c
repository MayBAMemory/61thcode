#include <header.h>

int main(){


    // 脱离当前会话, 自己创建一个新的会话, 并且成为会话领导者
    // 脱离当前会话的进程, 不能是进程组组长

    if(fork() == 0){
        // 子进程 , 不是组长
        setsid();
        while(1);
    }

    return 0;
}

