#include <header.h>

// 检错锁
int main(){

    // 定义了一个检错锁的属性
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
    
    // 用检错锁的实行: 初始化锁
    pthread_mutex_t lock;
    pthread_mutex_init(&lock , &attr);


    pthread_mutex_lock(&lock);

    int ret = pthread_mutex_lock(&lock);
    THREAD_ERROR_CHECK(ret, "lock");

    // TODO:....


    return 0;
}

