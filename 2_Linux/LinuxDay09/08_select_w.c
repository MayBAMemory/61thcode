#include <header.h>

int main(){

    int fd = open("1.pipe", O_RDWR);


    fd_set set_r, set_w;
    while(1){

        FD_ZERO(&set_r);
        FD_ZERO(&set_w);


        FD_SET(fd, &set_r);
        FD_SET(fd, &set_w);

        select(10, &set_r, &set_w, NULL, NULL);


        if(FD_ISSET(fd, &set_r)){
            // 可读
            char buf[1024] = {0};
            read(fd, buf, sizeof(buf));
            printf("read once \n");
        }

        if(FD_ISSET(fd, &set_w)){
            printf("write before \n");
            // 可写
            char buf[4096] = {0};
            write(fd, buf, sizeof(buf));
            printf("write after \n");
        }





    }

    return 0;
}

