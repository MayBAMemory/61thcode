#include <header.h>

int main(){

    printf("current process uid: %d \n", getuid());
    printf("current process group uid: %d \n", getgid());
    printf("current effective process uid: %d \n", geteuid());
    printf("current effective process group uid: %d \n", getegid());
    while(1);

    return 0;
}

