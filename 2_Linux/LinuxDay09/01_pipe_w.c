#include <header.h>

int main(){

    // 打开管道:  注意, 这个和打开一个普通磁盘文件不同
    //            我们调用open打开文件, 当发现是个管道文件的时候, 并不是真的去打开文件
    //            而是去在内存中开辟了一份缓冲区
    int fd = open("1.pipe", O_WRONLY);

    printf("打开了写端 \n");

    write(fd, "hello", 5);


    close(fd);
    return 0;
}

