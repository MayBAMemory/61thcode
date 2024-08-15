#include <header.h>

int main(){

    if(fork() == 0){
        sleep(10);
        exit(0);
    }else{
        while(1);
    }

    return 0;
}

