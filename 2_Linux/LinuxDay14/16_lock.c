#include <header.h>

// 自旋锁
pthread_mutex_t lock1;

void *func(void *p){

    sleep(1);
    while(1){
        // 锁1
        int ret = pthread_mutex_trylock(&lock1);
        if(ret != 0){
            continue;
        }

        // 访问共享资源

        // 释放锁
        pthread_mutex_unlock(&lock1);
        break;
    }

    return NULL;
}
int main(){

    pthread_mutex_init(&lock1, NULL);

    pthread_t son_id;
    pthread_create(&son_id, NULL, func, NULL);


    pthread_mutex_lock(&lock1);
    sleep(30);
    // 做了一些事情: 访问共享资源

    pthread_mutex_unlock(&lock1);

    pthread_join(son_id, NULL);

    pthread_mutex_destroy(&lock1);

    return 0;
}

