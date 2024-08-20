#include <header.h>

// 读写锁
pthread_rwlock_t rLock = PTHREAD_RWLOCK_INITIALIZER;

void *func(void *p){
    sleep(1);

    // 加写锁
    pthread_rwlock_wrlock(&rLock);

    printf("son  lock \n");

    // 解锁
    pthread_rwlock_unlock(&rLock);

    return NULL;
}
int main(){

    pthread_t son_id;
    pthread_create(&son_id, NULL, func, NULL);

    // 加读锁
    pthread_rwlock_rdlock(&rLock);

    // TODO: 读某些共享数据
    sleep(20);

    // 解锁
    pthread_rwlock_unlock(&rLock);

    pthread_join(son_id, NULL);

    return 0;
}

