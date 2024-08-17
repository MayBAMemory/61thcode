#include <header.h>

void func(int num){

    sleep(40);

    sigset_t set;
    sigemptyset(&set);
    sigpending(&set);

    if(sigismember(&set, 3)){
        printf("此时此刻有一个3号信号处于未决\n");
    }

    printf("123 \n");
}
int main(){


    struct sigaction act, old;
    memset(&act, 0, sizeof(act));

    act.sa_handler = func;

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, 3);
    act.sa_mask = set; 

    sigaction(2, &act, &old);

    while(1);

    return 0;
}

