#include <header.h>

void func(int num){
    printf("num: %d \n", num);
}

int main(){

    // 使用sigaction， 注册一个2号信号

    struct sigaction act, oldact;
    memset(&act, 0, sizeof(act));

    act.sa_handler = func;// 指明信号处理 函数
    act.sa_flags = SA_RESTART;

    sigaction(2, &act, &oldact);

    char buf[60] = {0};
    read(STDIN_FILENO, buf, sizeof(buf));
    printf("buf: %s \n", buf);


    return 0;
}

