#include <header.h>

// 两个线程访问数据段
int num = 10;

void * func(void *p){

    printf("son num: %d \n", num);
    num++;
    printf("son num: %d \n", num);

    return NULL;
}
int main(){

    pthread_t son_id;
    pthread_create(&son_id, NULL, func, NULL);

    printf("mian num: %d \n", num);
    sleep(1);
    num++;
    printf("main num: %d \n", num);


    return 0;
}

