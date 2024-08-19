#include <header.h>

// 两个线程访问数据段
int num = 0;

void * func(void *p){

    for(int i=0; i<10000000; i++){
        num++;
    }

    return NULL;
}
int main(){

    pthread_t son_id;
    pthread_create(&son_id, NULL, func, NULL);

    for(int i=0; i<10000000; i++){
        num++;
    }

    pthread_join(son_id, NULL);
    printf("num: %d \n", num);

    return 0;
}

