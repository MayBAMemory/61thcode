#include <header.h>

int main(){

    char *file_name = "1.txt";
    char *str = "hello";

    int pipe_fd = open("1.pipe", O_WRONLY);

    int  name_len = strlen(file_name);
    int str_len = strlen(str); 

    // 
    write(pipe_fd, &name_len, sizeof(int));
    write(pipe_fd, file_name, name_len);


    // 写文件内容
    write(pipe_fd, &str_len, sizeof(int));
    write(pipe_fd, str, str_len);

    close(pipe_fd);
    return 0;
}

