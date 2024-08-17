#include <header.h>

void func(int num){

}
int main(){

    signal(2, func);

    printf("pause before \n");
    pause();
    printf("pause after \n");

    return 0;
}

