#include <header.h>

int main(){

    // 通过ftok产生一个共享内存的标识， 用户标识共享内存

    key_t key_id = ftok("./01_test", 10);

    printf("key_id: %d \n", key_id);

    // 通过指定的标识的key， 创建一个共享内存段
    int shmid = shmget(key_id, 4096, 0600|IPC_CREAT);

    // shmid: 就是通过shmget函数 获取/创建  的共享内存的id编号
    

    // 把共享内存（一个实际的物理页），指定的映射到当前进程， 某个虚拟地址空间

    void * p = shmat(shmid, NULL, 0);
    // p指针， 指向那个虚拟地址的首地址

    strcpy((char *)p, "helo");

    return 0;
}

