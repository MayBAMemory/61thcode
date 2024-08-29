#include "head.h"


void * threadMain(void *p){

    status_t *status = (status_t *)p;

    while(1){

        // 判断是否有任务
        pthread_mutex_lock(&status->lock );
        while(status->queue.size <= 0  && status->exit_flag == 0){
            // 没任务 -> 阻塞
            pthread_cond_wait(&status->cond , &status->lock );
            // 被唤醒-> 代表有任务了
        }

        if(status->exit_flag != 0){
            // TODO: 要退出 free, close, unlock

            pthread_mutex_unlock(&status->lock);
            pthread_exit(NULL);
        }

        // 取任务: 取队列头部的net_fd
        int net_fd = status->queue.head->net_fd ;
        deQueue(&status->queue);

        pthread_mutex_unlock(&status->lock );

        // 和客户端进行交互
        sendFile(net_fd);
    }

    return 0;
}


