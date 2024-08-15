#include <header.h>

int main(){

    if(fork() == 0){
        printf("child process \n");
        sleep(20);
        return 100;
    }else{
        int status;
        int s_pid = wait(&status);

        
        printf("wait child: child pid=%d \n", s_pid);
        if(WIFEXITED(status)){// 子进程正常退出
            printf("child status: %d \n", WEXITSTATUS(status));
        }else if(WIFSIGNALED(status)){//子进程信号退出
            printf("child signed: %d \n", WTERMSIG(status));
        }
    }


    return 0;
}

