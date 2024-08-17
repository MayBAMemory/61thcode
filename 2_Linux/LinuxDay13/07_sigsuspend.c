#include <header.h>

void func(int num){
    printf("2号信号\n");
}
int main(){

    signal(2, func);
    sigset_t set, old;
    sigemptyset(&set);
    sigemptyset(&old);
    sigaddset(&set, 2);

    sigprocmask(SIG_BLOCK, &set, &old );

    // 使用sleep代指一个很重要
    // 需要耗时10s才能结束的任务
    // -> 不希望他被信号打断
    sleep(10);

    printf("block over \n");

    //sigprocmask(SIG_UNBLOCK, &set, &old );
    //pause();

    sigset_t sus_set;
    sigemptyset(&sus_set);
    printf("---- \n");
    sigsuspend(&sus_set);
    printf("---- \n");


    printf("over \n");

    sigprocmask(SIG_UNBLOCK, &set, &old );
    while(1);
    return 0;
}

