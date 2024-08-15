#include <header.h>

int main(){



    if(fork() == 0){

        int fd = open("a.txt", O_RDWR);
        write(fd, "iamson", 6);

    }else{

        int fd = open("a.txt", O_RDWR);
        write(fd, "iammain", 7);

    }

    return 0;
}

