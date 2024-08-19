#include <header.h>

// trylock:
pthread_mutex_t lock1;

void *func(void *p){
    sleep(2);
    // 锁1
    printf("son lock 1 \n");
    pthread_mutex_lock(&lock1);
    printf("son lock 2 \n");

    // 释放锁
    pthread_mutex_unlock(&lock1);

    return NULL;
}
int main(){

    pthread_mutex_init(&lock1, NULL);

    pthread_t son_id;
    pthread_create(&son_id, NULL, func, NULL);

    // 锁1
    pthread_mutex_lock(&lock1);
    while(1);

    // 释放锁
    pthread_mutex_unlock(&lock1);

    pthread_join(son_id, NULL);

    pthread_mutex_destroy(&lock1);
    return 0;
}

