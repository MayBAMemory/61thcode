#include <header.h>

// 线程的退出, 和资源释放的问题
void *func(void *p){

    int fd = open("./Makefile", O_RDWR);
    void *addr = malloc(10);
    while(1){
        sleep(1);
    }

    free(addr);
    close(fd);
    return NULL;
}
int main(){

    pthread_t son_id;
    pthread_create(&son_id, NULL, func, NULL);

    sleep(1);

    pthread_cancel(son_id);

    pthread_join(son_id, NULL);
    printf("子线程退出, 程序要结束 \n");

    return 0;
}

