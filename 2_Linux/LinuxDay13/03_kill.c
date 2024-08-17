#include <header.h>

int main(){

    kill(getpid(), 9);

    printf("123 \n");

    return 0;
}

