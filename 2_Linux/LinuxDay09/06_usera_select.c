#include <header.h>

int main(){

    int fd_write = open("1.pipe", O_WRONLY);
    int fd_read = open("2.pipe", O_RDONLY);
    printf("管道打开 \n");


    // 构建一个select监听所需要的文件描述符集合
    fd_set  set;


    while(1){
        // 每一次都需要重置监听集合
        // FD_ZERO: 初始化fd_set, (清空)
        FD_ZERO( &set  );
        // 把标准输入,管道; 把这两个文件描述符
        // 放到集合中
        FD_SET(STDIN_FILENO, &set);
        FD_SET(fd_read, &set);

        // 调用select 监听set集合中两个文件描述符, 是否读就绪 
        select(fd_read+1, &set, NULL, NULL, NULL);
        // 走到这: 意味着, 要么标准输入可读, 要么管道可读
        //                  也有可能是两个都可读

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
        }
    }

    close(fd_read);
    close(fd_write);
    return 0;
}

