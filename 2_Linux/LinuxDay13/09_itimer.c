#include <header.h>

void func(int num){
    printf("num: %d \n", num);
}
int main(){

    signal(14, func);

    struct itimerval new_value, old_value;
    new_value.it_value.tv_sec = 10;
    new_value.it_value.tv_usec = 0;

    new_value.it_interval.tv_sec = 1;
    new_value.it_interval.tv_usec = 0;

    setitimer( ITIMER_REAL, &new_value,  &old_value );


    while(1);

    return 0;
}

