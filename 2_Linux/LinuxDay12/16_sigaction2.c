#include <header.h>

void func(int num, siginfo_t *info, void *p){
    printf("num: %d \n", num);
    printf("pid: %d \n", info->si_pid);
}

int main(){

    // 使用sigaction， 注册一个2号信号

    struct sigaction act, oldact;
    memset(&act, 0, sizeof(act));

    act.sa_sigaction = func;// 指明信号处理 函数
    act.sa_flags = SA_SIGINFO;

    sigaction(2, &act, &oldact);

    while(1);

    return 0;
}

