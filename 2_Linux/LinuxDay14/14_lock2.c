#include <header.h>

// 两个线程都需要锁1和锁2, 但是双方都持有其中一个锁, 等待对方的锁, 导致死锁
pthread_mutex_t lock1;
pthread_mutex_t lock2;

void *func(void *p){

    while(1){
        sleep(1);
        // 锁2
        pthread_mutex_lock(&lock2);
        sleep(2);
        // 锁1
        int ret = pthread_mutex_trylock(&lock1);
        if(ret != 0){
            // 说明没有拿到锁1, 说明锁1被别人拿走, 为了避免死锁, 不如把锁2也释放
            pthread_mutex_unlock(&lock2);
            continue;
        }

        // 访问共享资源

        // 释放锁
        pthread_mutex_unlock(&lock1);
        pthread_mutex_unlock(&lock2);
        break;
    }

    return NULL;
}
int main(){

    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    pthread_t son_id;
    pthread_create(&son_id, NULL, func, NULL);

    // 锁1
    pthread_mutex_lock(&lock1);
    sleep(2);
    // 锁2
    pthread_mutex_lock(&lock2);

    // 释放锁
    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);

    pthread_join(son_id, NULL);

    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);

    return 0;
}

