#include <header.h>

void func(int num){

    printf("2号信号被触发 \n");
}
int main(){
    signal(3, SIG_IGN);
    signal(2, func);
    while(1);

    return 0;
}

