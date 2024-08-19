#include <header.h>

// 新的子线程入口函数 (这个函数对于被创建的子线程,   等价于main对于主线程 )
void * func(void *p){

    printf("son_thread_id: %ld \n", pthread_self());

    return NULL;
}
int main(){

    // 创建一个子线程
    pthread_t son_id;
    pthread_create(&son_id, NULL, func, NULL);

    printf("main_thread_id: %ld \n", pthread_self());


    // 主线程结束一定会导致子线程结束吗? 不一定
    // 进程结束: 所有依赖于这个进程存在的线程, 都会结束(确定)
    // 主线程的不同的退出方式是有可能导致进程退出:  (主线程在入口函数中return, 或者 主线程调用exit)

    // exit(0);
    pthread_exit(NULL);
    return 0;
}

