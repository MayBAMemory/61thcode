#include "queue.h"

// 定义一个结构体, 用来记录主线程和子线程, 大家都需要的一些数据
typedef struct status_s{

    // list: 用来记录所有子线程的线程id
    pthread_t *list;
    // num: 用来记录子线程的个数
    int num;

    // queue: 队列, 用来在当前的生产者-消费者模型中, 存储net_fd, 用于主线程和子线程之间流转任务
    queue_t  queue;

    // lock: 互斥锁, 用来让主线程和子线程, 互斥访问共享数据
    pthread_mutex_t lock;

    // cond: 条件变量, 用来在主线程和子线程的生产者和消费者模型, 用来做同步唤醒的机制
    pthread_cond_t cond;


}status_t;

// 初始化参数, 并且启动子线程
int initStatus(status_t *status, int num);

// 子线程的入口函数
void * threadMain(void *p);
