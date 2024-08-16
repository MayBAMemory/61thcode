#include <header.h>

void func(int num){
    printf("1 \n");
    sleep(20);
    printf("2 \n");
}
int main(){

    signal(2, func);

    printf("before sleep \n");
    sleep(1000);
    printf("after sleep \n");


    return 0;
}

