#include <header.h>

int main(){

    int fd = open("1.pipe", O_RDONLY);

    char buf[60] = {0};
    read(fd, buf, sizeof(buf));

    printf("%s\n", buf);

    return 0;
}
