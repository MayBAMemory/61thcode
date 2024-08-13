#include <header.h>

int main(){

    int fd = open("1.pipe", O_RDONLY);
    printf("打开读端 \n");

    char buf[60] = {0};
    read(fd, buf, sizeof(buf));
    printf("buf: %s \n", buf);

    close(fd);
    return 0;
}

