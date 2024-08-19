#include <header.h>

// 定义一个锁
pthread_mutex_t lock;

int num = 0;

void *func(void *p){

    // +10000000
    for(int i=0; i<10000000; i++){
        // 加锁
        pthread_mutex_lock(&lock);
        num++;
        // 解锁
        pthread_mutex_unlock(&lock);
    }

    return NULL;
}
int main(){

    // 初始化锁
    pthread_mutex_init(&lock,  NULL);

    pthread_t son_id;
    pthread_create(&son_id, NULL, func, NULL);

    // +10000000
    for(int i=0; i<10000000; i++){
        // 加锁
        pthread_mutex_lock(&lock);
        num++;
        // 解锁
        pthread_mutex_unlock(&lock);
    }

    pthread_join(son_id, NULL);
    printf("num: %d \n", num);

    pthread_mutex_destroy(&lock);
    return 0;
}

