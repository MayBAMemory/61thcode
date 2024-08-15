#include <header.h>

int main(){

    mkfifo("x.pipe", 0666);

    unlink("x.pipe");

    return 0;
}

