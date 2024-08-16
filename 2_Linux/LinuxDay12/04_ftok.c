#include <header.h>

int main(){

    // 通过ftok产生一个共享内存的标识， 用户标识共享内存

    key_t key_id = ftok("./01_test", 10);

    printf("key_id: %d \n", key_id);

    return 0;
}

