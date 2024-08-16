#include <header.h>

void func(int num){

    printf("num: %d \n", num);
}
int main(){

    // 使用signal修改2号信号的处理行为
    signal( 2, func );

    signal( 3, func );
    while(1);


    return 0;
}

