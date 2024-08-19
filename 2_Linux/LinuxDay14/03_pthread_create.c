#include <header.h>

// 新的子线程入口函数 (这个函数对于被创建的子线程,   等价于main对于主线程 )
void * func(void *p){

    while(1){
        sleep(1);
        printf("son_pid: %d \n", getpid());
        printf("son_thread_id: %ld \n", pthread_self());
    }

    return NULL;
}
int main(){

    // 创建一个子线程

    // 定义一个线程的id类型, 当调用pthread_create创建一个新的线程完成的时候, 获得这个新的线程的id
    pthread_t son_id;

    pthread_create(&son_id, NULL, func, NULL);
    printf("------------- \n");
    printf("%ld \n", son_id);
    printf("------------- \n");

    while(1){
        sleep(1);
        printf("main_pid: %d \n", getpid());
        printf("main_thread_id: %ld \n", pthread_self());
    }

    return 0;
}

