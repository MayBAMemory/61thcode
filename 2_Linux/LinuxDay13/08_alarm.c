#include <header.h>

void func(int num){
    printf("num: %d \n", num);
}
int main(){

    signal(14, func);

    alarm(10);
    printf("--- \n");

    while(1);

    return 0;
}

