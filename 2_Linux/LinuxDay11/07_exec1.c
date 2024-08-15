#include <header.h>

int main(){

    if(fork() == 0){
        printf("pid: %d;  ppid: %d \n", getpid(), getppid());

        //execl("./07_test",  "./07_test", (char *)0);

        char * paramer[] = {"./07_test", (char *) 0 };
        execv("./07_test", paramer);

        printf("123 \n");

    }else{

        // 父进程
        //while(1);
        sleep(1);

    }

    return 0;
}

