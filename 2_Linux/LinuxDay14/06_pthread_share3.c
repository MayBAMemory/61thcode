#include <header.h>

// 两个线程访问栈上数据

void * func(void *p){
    int *num = (int *)p;

    printf("son num: %d \n", *num);
    *num = 11;
    printf("son num: %d \n", *num);

    return NULL;
}
int main(){
    int num = 10;

    pthread_t son_id;
    pthread_create(&son_id, NULL, func, &num);

    printf("mian num: %d \n", num);
    sleep(1);
    num++;
    printf("main num: %d \n", num);


    return 0;
}

