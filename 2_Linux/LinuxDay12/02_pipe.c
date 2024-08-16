#include <header.h>

int main(){

    // 初始化一个匿名管道
    int pipe_fd[2];
    pipe(pipe_fd);


    if(fork() == 0){
        // 子进程
        // 关闭写端： 
        close(pipe_fd[1]);

        char buf[60] = {0};
        read(pipe_fd[0], buf, sizeof(buf));
        printf("buf: %s \n", buf);

        close(pipe_fd[0]);

    }else{
       // 父进程
       // 关闭读端
       close(pipe_fd[0]);

       write(pipe_fd[1], "hello123", 8);

       close(pipe_fd[1]);
    }

    return 0;
}

