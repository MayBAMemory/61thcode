#include <header.h>

void a(){

    //_exit(0);
    _Exit(0);
    printf("a \n");

    return ;
}
int main(){

    printf("123 \n");

    a();
    //exit(0);

    printf("456 \n");
    return 0;
}

