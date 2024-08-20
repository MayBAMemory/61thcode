#include <header.h>

// 可重入锁
int main(){

    // 定义了一个可重入锁的属性
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    
    // 用可重入的属性: 初始化锁
    pthread_mutex_t lock;
    pthread_mutex_init(&lock , &attr);


    pthread_mutex_lock(&lock);

    int ret = pthread_mutex_lock(&lock);
    THREAD_ERROR_CHECK(ret, "lock");

    printf("----- \n");
    // TODO:....

    pthread_mutex_unlock(&lock);
    pthread_mutex_unlock(&lock);


    return 0;
}

