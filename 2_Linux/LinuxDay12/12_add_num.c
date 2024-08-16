#include <header.h>

int main(int argc,char*argv[])
{
    // 创建、获取共享内存的id
    int shmid = shmget(100, 4096, 0600|IPC_CREAT);
    // 把共享内存 和当前进程的虚拟地址空间， 做个映射
    int *p = (int *)shmat(shmid, NULL, 0);


    // 存储0
    p[0] = 0;

    if(fork() == 0){
        for(int i = 0; i < 10000000; i++){
            p[0]++;
        }
    }else{
        for(int i = 0; i < 10000000; i++){
            p[0]++;
        }

        wait(NULL);
        printf("%d \n", p[0]);
    }
    return 0;
}
