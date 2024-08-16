#include <header.h>

void func(int num){
    printf("num: %d \n", num);
}

int main(){

    // 使用sigaction， 注册一个2号信号

    struct sigaction act, oldact;
    memset(&act, 0, sizeof(act));

    act.sa_handler = func;// 指明信号处理 函数

    sigaction(2, &act, &oldact);

    while(1);

    return 0;
}

