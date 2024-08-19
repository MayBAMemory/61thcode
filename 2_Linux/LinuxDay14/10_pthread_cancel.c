#include <header.h>

// 线程的被动退出
// 一个线程, 让另外一个线程退出


void *func(void *p){

    // 如果当前线程的退出标记位, 被别的线程所修改
    // 那么在当前进程中, 不会去时时刻刻关注退出标记位的
    // 只有当前进程在运行到某些特定的函数的时候, 才会去检查退出标记位
    // 这种会去检查当前线程的退出标记位的函数: 叫取消点函数
    while(1){
        // sleep(1);
        char buf[60] = {0};
        read(STDIN_FILENO, buf, sizeof(buf));
        printf("buf: %s \n", buf);
    }

    return NULL;
}
int main(){

    pthread_t son_id;
    pthread_create(&son_id, NULL, func, NULL);


    // pthread_cancel:给指定的线程发送信息(不是信号: 修改对方的退出标记位), 让指定的线程退出
    pthread_cancel(son_id);

    pthread_join(son_id, NULL);
    printf("子线程退出, 程序要结束 \n");

    return 0;
}

