#include <header.h>

int main(){

    int fd_read = open("1.pipe", O_RDONLY);
    int fd_write = open("2.pipe", O_WRONLY);
    printf("管道打开 \n");

    while(1){

        // 读管道, 读完打印
        char buf[60] = {0};
        read(fd_read, buf, sizeof(buf));
        printf("buf: %s \n", buf);

        // 读取标准输入
        bzero(buf, sizeof(buf));
        read(STDIN_FILENO, buf, sizeof(buf));
        write(fd_write, buf, sizeof(buf));
    }

    close(fd_read);
    close(fd_write);
    return 0;
}

