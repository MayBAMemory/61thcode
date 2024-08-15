#include <header.h>

int main(){
    int num = 10;

    if(fork() == 0){
        // 子进程逻辑

        num++;
        printf("num: %d \n", num);
        

    }else{
        // 父进程逻辑

        sleep(1);
        num++;
        printf("num: %d \n", num);

    }

    return 0;
}

