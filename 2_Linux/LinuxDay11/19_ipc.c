#include <header.h>

int main(){

    mkfifo("x.pipe", 0666);

    if(fork() == 0){
        int pipe_fd = open("x.pipe", O_RDONLY);

        char buf[60] = {0};
        read(pipe_fd, buf, sizeof(buf));
        printf("son: %s \n", buf);

        close(pipe_fd);
    }else{

        int pipe_fd = open("x.pipe", O_WRONLY);
        sleep(10);
        write(pipe_fd, "hello", 5);

        close(pipe_fd);
    }


    unlink("x.pipe");

    return 0;
}

