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
    act.sa_flags = SA_NODEFER;

    sigaction(2, &act, &oldact);

    while(1);

    return 0;
}

