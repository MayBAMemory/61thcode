#include <header.h>

int main(){

    int pipe_fd = open("1.pipe", O_RDONLY);

    char buf_name[60] = {0};
    char buf[60] = {0};

    int name_len = 0;
    read(pipe_fd, &name_len, sizeof(int));
    read(pipe_fd, buf_name, name_len);

    int str_len = 0;
    read(pipe_fd, &str_len, sizeof(int));
    read(pipe_fd, buf, str_len);

    printf("buf_name: %s \n", buf_name);
    printf("buf: %s \n", buf);

    return 0;
}

