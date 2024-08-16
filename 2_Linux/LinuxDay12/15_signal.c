#include <header.h>

void func2(int num){
    printf("2号信号1 \n");
    sleep(20);
    printf("2号信号2 \n");
}
void func3(int num){
    printf("3号信号1 \n");
    sleep(20);
    printf("3号信号2 \n");
}
int main(){

    signal(2, func2);
    signal(3, func3);


    while(1);
    return 0;
}

