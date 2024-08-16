#include <header.h>

int main(){


    FILE * pipe = popen("./03_printf", "r");

    char buf[60] = {0};
    fread(buf, 1, sizeof(buf), pipe);

    printf("03_popen: %s \n", buf);

    pclose(pipe);
    return 0;
}

