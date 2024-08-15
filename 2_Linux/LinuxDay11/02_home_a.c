#include <header.h>

int main(){

    int fd_write = open("1.pipe", O_WRONLY);
    int fd_read = open("2.pipe", O_RDONLY);
    printf("管道打开 \n");

    fd_set  set;


    while(1){
        FD_ZERO( &set  );
        FD_SET(STDIN_FILENO, &set);
        FD_SET(fd_read, &set);

        select(fd_read+1, &set, NULL, NULL, NULL);

        if(FD_ISSET(STDIN_FILENO, &set)){
            time_t t = time(NULL);
            char *time_str = ctime(&t);
            int len = strlen(time_str);
            write(fd_write, &len, sizeof(int));
            write(fd_write, time_str, len);


            char buf[60] = {0};
            read(STDIN_FILENO, buf, sizeof(buf));
            write(fd_write, buf, sizeof(buf));

        }
        if(FD_ISSET(fd_read, &set)){
            int len = 0;
            read(fd_read, &len, sizeof(int));
            char time_buf[60] = {0};
            read(fd_read, time_buf, len);
            printf("%s", time_buf);


            char buf[60] = {0};
            int ret = read(fd_read, buf, sizeof(buf));
            if(ret == 0){
                break;
            }
            printf("buf: %s \n", buf);
        }
    }

    close(fd_read);
    close(fd_write);
    return 0;
}
