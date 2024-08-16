#include <header.h>

int main(){

    // 通过ftok产生一个共享内存的标识， 用户标识共享内存

    key_t key_id = ftok("./01_test", 10);

    printf("key_id: %d \n", key_id);

    // 通过指定的标识的key， 创建一个共享内存段
    int shmid = shmget(key_id, 4096, 0600|IPC_CREAT);

    // shmid: 就是通过shmget函数 获取/创建  的共享内存的id编号
    




    return 0;
}

