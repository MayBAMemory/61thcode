#include <header.h>

int main(){

    int fd = open("b.txt", O_RDWR);
    ERROR_CHECK(fd, -1, "open");

    write(fd, "hello", 5);

    close(fd);

    return 0;
}

