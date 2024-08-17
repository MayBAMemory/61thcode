#include <header.h>

void func(int num){
    printf("num: %d \n", num);

    alarm(5);
}
int main(){

    signal(14, func);

    alarm(5);
    printf("--- \n");

    while(1);

    return 0;
}

