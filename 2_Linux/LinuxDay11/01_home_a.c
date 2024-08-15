#include <header.h>

int main(){

    int fd = open("1.pipe", O_WRONLY);

    printf("hello1 \n");

    int temp = 10;
    dup2(STDOUT_FILENO, temp);
    dup2(fd, STDOUT_FILENO);
    printf("hello2 \n");

    dup2(10, STDOUT_FILENO);
    printf("hello3 \n");

    return 0;
}
