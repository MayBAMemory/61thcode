#include <header.h>

void func(int num){

    printf("num: %d \n", num);
}

void func3(int num){
    printf("3号信号 \n");
}
int main(){

    // 使用signal修改2号信号的处理行为
    signal( 2, func );

    signal( 3, func3 );
    while(1);


    return 0;
}

