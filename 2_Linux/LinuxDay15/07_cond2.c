#include <header.h>

pthread_mutex_t lock;
// 定义一个条件变量
pthread_cond_t cond;

void *func(void *p){
    // 加锁
    pthread_mutex_lock(&lock);

    printf("------------- \n");
    // 释放锁-> 陷入阻塞 -> 等待被唤醒
    pthread_cond_wait(&cond, &lock);
    // 当被唤醒-> 重新获取锁,(如果获取不到锁, 一直等待获取锁等价于pthread_mutex_lock)
    printf("************* \n");

    // 解锁
    pthread_mutex_unlock(&lock);
    return NULL;
}
int main(){
    pthread_mutex_init(&lock, NULL);
    // 初始化条件变量
    pthread_cond_init(&cond, NULL);

    pthread_t son_id;
    pthread_create(&son_id, NULL, func, NULL);

    sleep(20);
    // 根据指定条件(条件变量)唤醒,某个因为条件变量陷入阻塞的线程
    pthread_mutex_lock(&lock);
    pthread_cond_signal(&cond);
    printf("main get lock \n");
    sleep(20);

    pthread_mutex_unlock(&lock);

    pthread_join(son_id, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;
}

