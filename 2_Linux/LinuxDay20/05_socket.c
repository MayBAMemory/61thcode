#include <header.h>

// 先通过fork创建一个子进程
// 在父进程中打开一个文件对象, 
// 我们希望通过某种方式让父进程把这个文件对象信息, 能传给子进程
// 让父子进程同时持有同一个文件对象
int main(){

    int pipe_fd[2];
    pipe(pipe_fd);

    if(fork() == 0){
        // 子进程
        close(pipe_fd[1]);

        int file_fd;
        read(pipe_fd[0], &file_fd, sizeof(int));
        printf("file_fd: %d \n", file_fd);

        int ret = write(file_fd, "hello", 5);
        ERROR_CHECK(ret, -1, "write");

        close(pipe_fd[0]);
    }else{
        // 父进程
        close(pipe_fd[0]);

        int file_fd = open("1.txt", O_WRONLY);
        
        write(pipe_fd[1], &file_fd, sizeof(int));

        close(pipe_fd[1]);
    }

    return 0;
}

