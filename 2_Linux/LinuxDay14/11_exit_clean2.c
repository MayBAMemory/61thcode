#include <header.h>

// 线程的退出, 和资源释放的问题
//
void func_close(void *p){
    printf("func_close \n");
    long fd = (long) p;
    close(fd);
}
void func_free(void *p){
    printf("func_free \n");
    free(p);
}
void *func(void *p){

    int fd = open("./Makefile", O_RDWR);
    pthread_cleanup_push(func_close, (void *)fd);

    void *addr = malloc(10);
    pthread_cleanup_push(func_free, addr);


    while(1){
        sleep(1);
    }


    // free(addr);
    pthread_cleanup_pop(1);

    pthread_exit(NULL);

    pthread_cleanup_pop(1);
    //close(fd);
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

