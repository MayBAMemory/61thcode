#include <header.h>

int main(){

    int fd_write = open("1.pipe", O_WRONLY);
    int fd_read = open("2.pipe", O_RDONLY);
    printf("管道打开 \n");


    // 构建一个select监听所需要的文件描述符集合
    fd_set  set;

    struct timeval tv;
    tv.tv_sec = 10;
    tv.tv_usec = 0;

    while(1){
        FD_ZERO( &set  );
        FD_SET(STDIN_FILENO, &set);
        FD_SET(fd_read, &set);


        int ret_select = select(fd_read+1, &set, NULL, NULL, &tv);

        if(ret_select == 0){
            break;
        }

        printf("select over: %d  \n", ret_select);
        printf("time: %ld \n", tv.tv_sec);


        if(FD_ISSET(STDIN_FILENO, &set)){
            // 说明上面标准输入就绪了, 导致select返回

            // 读标准输入, 写管道
            char buf[60] = {0};
            read(STDIN_FILENO, buf, sizeof(buf));
            write(fd_write, buf, sizeof(buf));

        }
        if(FD_ISSET(fd_read, &set)){
            // 上面select返回原因是因为管道可读
            // 读管道, 打印
            char buf[60] = {0};
            int ret = read(fd_read, buf, sizeof(buf));
            if(ret == 0){
                // select觉得fd_read可读
                // 但是没有读到东西, 直接read返回了0
                // -> 对端关闭
                break;
            }
            printf("buf: %s \n", buf);
            tv.tv_sec = 10;
        }
    }

    close(fd_read);
    close(fd_write);
    return 0;
}

