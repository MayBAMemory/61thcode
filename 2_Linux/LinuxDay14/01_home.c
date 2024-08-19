#include <header.h>
void func(int num){
    printf("begin \n");

    sleep(20);

    sigset_t set;
    sigemptyset(&set);
    sigpending(&set);

    if(sigismember(&set, 3)){
        printf("有3号信号处于未决 \n");
    }

    printf("over \n");
}
int main(){


    struct sigaction act, old;
    memset(&act, 0, sizeof(act));
    act.sa_handler = func;
    act.sa_flags = SA_RESTART;

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, 3);
    act.sa_mask = set;


    sigaction(2, &act, &old);

    char buf[60] = {0};
    read(STDIN_FILENO, buf, sizeof(buf));
    printf("buf: %s \n", buf);

    return 0;
}

