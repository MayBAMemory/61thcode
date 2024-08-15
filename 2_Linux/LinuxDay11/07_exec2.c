#include <header.h>

int main(){

    if(fork() == 0){
        printf("pid: %d;  ppid: %d \n", getpid(), getppid());

        execl("./07_sum",  "./07_sum", "5", "6", (char *)0);

        printf("123 \n");

    }else{

        // 父进程
        //while(1);
        sleep(1);

    }

    return 0;
}

