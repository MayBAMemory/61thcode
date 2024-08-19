#include <header.h>

// 死锁: 重复加锁导致死锁
int main(){

    pthread_mutex_t lock;
    pthread_mutex_init(&lock, NULL);

    printf("before 1 \n");
    pthread_mutex_lock(&lock);
    printf("after 1 \n");

    printf("before 2 \n");
    pthread_mutex_lock(&lock);
    printf("after 2 \n");


    pthread_mutex_unlock(&lock);
    pthread_mutex_unlock(&lock);

    pthread_mutex_destroy(&lock);
    return 0;
}

