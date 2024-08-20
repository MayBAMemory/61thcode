#include <header.h>

// spinlock: 自旋锁
pthread_spinlock_t spinlock;

void *func(void *p){
    sleep(1);
    // 加锁
    pthread_spin_lock(&spinlock);

    sleep(1);

    // 解锁
    pthread_spin_unlock(&spinlock);

    return NULL;
}
int main(){

    pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);

    pthread_t son_id;
    pthread_create(&son_id, NULL, func, NULL);

    // 加锁
    pthread_spin_lock(&spinlock);
    sleep(20);
    // 解锁
    pthread_spin_unlock(&spinlock);


    pthread_join(son_id, NULL);

    pthread_spin_destroy(&spinlock);

    return 0;
}

