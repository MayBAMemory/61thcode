#include <header.h>

void func(int num){
    printf("num: %d \n", num);
    sleep(20);
    printf("over \n");
}

int main(){

    // 使用sigaction， 注册一个2号信号

    struct sigaction act, oldact;
    memset(&act, 0, sizeof(act));

    act.sa_handler = func;// 指明信号处理 函数



    // 在2号信号执行处理2号信号函数的过程中， 不要被3号信号打断
    sigset_t set;// set中存储3号信号
    sigemptyset(&set);
    sigaddset(&set, 3);

    act.sa_mask = set;

    sigaction(2, &act, &oldact);

    while(1);

    return 0;
}

