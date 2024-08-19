#include <header.h>

int main(){

    sigset_t set, old;
    sigemptyset(&set);
    sigemptyset(&old);

    sigaddset(&set, 2);
    sigprocmask(SIG_BLOCK, &set, &old);

    sleep(5);

    sigset_t setpending;
    sigemptyset(&setpending);

    sigpending(&setpending);
    if(sigismember(&setpending, 2)){
        printf("有2号信号处于未决 \n");
    }

    sigprocmask(SIG_UNBLOCK, &set, &old);

    return 0;
}

