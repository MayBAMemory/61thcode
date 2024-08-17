#include <header.h>

int main(){

    sigset_t set, old;
    sigemptyset(&set);
    sigemptyset(&old);

    sigaddset(&set, 2);
    sigaddset(&set, 3);

    sigprocmask(SIG_BLOCK, &set, &old );

    // 使用sleep代指一个很重要
    // 需要耗时40s才能结束的任务
    // -> 不希望他被信号打断
    sleep(40);

    sigprocmask(SIG_UNBLOCK, &set, &old );

    printf("over \n");

    return 0;
}

