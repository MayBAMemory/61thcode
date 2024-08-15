#include <header.h>

int main(){


    // 创建一个管道: (实际上开辟内存缓冲区)

    int pipe_fd[2];
    pipe(pipe_fd);

    if(fork() == 0){
        close(pipe_fd[1]);

        char buf[60] = {0};
        read(pipe_fd[0], buf, sizeof(buf));
        printf("buf: %s \n", buf);

        close(pipe_fd[0]);
    }else{
        close(pipe_fd[0]);

        write(pipe_fd[1], "hello", 5);

        close(pipe_fd[1]);
    }



    return 0;
}

