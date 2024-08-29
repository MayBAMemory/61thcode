#include "head.h"


// 初始化参数, 并且启动子线程
int initStatus(status_t *status, int num){
    // 退出标记位
    status->exit_flag = 0;

    // 确定子线程的个数
    status->num = num;
    
    // 队列
    bzero(&status->queue , sizeof(queue_t));

    // 互斥锁  条件变量
    pthread_mutex_init(&status->lock, NULL);
    pthread_cond_init(&status->cond, NULL);

    // 创建子线程
    status->list = (pthread_t *)malloc(num*sizeof(pthread_t));
    for(int i=0; i<num; i++){
        pthread_create(&status->list[i], NULL, threadMain, status );
    }
    return  0;
}


