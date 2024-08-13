#include <header.h>

int main(){

    int fd_write = open("1.pipe", O_WRONLY);
    int fd_read = open("2.pipe", O_RDONLY);
    printf("管道打开 \n");

    while(1){

        // 读标准输入, 写管道
        char buf[60] = {0};
        read(STDIN_FILENO, buf, sizeof(buf));
        write(fd_write, buf, sizeof(buf));

        // 读管道, 打印
        bzero(buf, sizeof(buf));
        read(fd_read, buf, sizeof(buf));
        printf("buf: %s \n", buf);
    }

    close(fd_read);
    close(fd_write);
    return 0;
}

