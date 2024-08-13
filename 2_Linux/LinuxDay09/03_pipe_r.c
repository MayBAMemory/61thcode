#include <header.h>

int main(){

    int fd = open("1.pipe", O_RDONLY);
    printf("打开读端 \n");

    while(1){
        sleep(1);
        char buf[1024] = {0};
        read(fd, buf, sizeof(buf));
        printf("read once \n");

    }

    close(fd);
    return 0;
}

