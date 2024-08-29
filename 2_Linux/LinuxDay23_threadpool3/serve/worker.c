#include "head.h"


void cleanLock(void *p){
    pthread_mutex_t *lock = (pthread_mutex_t *)p;

    pthread_mutex_unlock(lock);
}
void * threadMain(void *p){

    status_t *status = (status_t *)p;

    while(1){

        int net_fd = 0;

        // 判断是否有任务
        pthread_mutex_lock(&status->lock );
        pthread_cleanup_push(cleanLock, &status->lock );
        while(status->queue.size <= 0){
            // 没任务 -> 阻塞
            pthread_cond_wait(&status->cond , &status->lock );
            // 被唤醒-> 代表有任务了
        }

        // 取任务: 取队列头部的net_fd
        net_fd = status->queue.head->net_fd ;
        deQueue(&status->queue);

        //pthread_mutex_unlock(&status->lock );
        pthread_cleanup_pop(1);

        // 和客户端进行交互
        sendFile(net_fd);
    }

    return 0;
}


