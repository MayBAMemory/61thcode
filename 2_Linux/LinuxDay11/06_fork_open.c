#include <header.h>

int main(){

    int fd = open("a.txt", O_RDWR);


    if(fork() == 0){

        write(fd, "iamson", 6);

    }else{

        write(fd, "iammain", 7);

    }

    return 0;
}

