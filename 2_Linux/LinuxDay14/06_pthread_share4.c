#include <header.h>

// 两个线程访问栈上数据

void * func(void *p){
    int *num = (int *)p;

    printf("son num: %d \n", *num);
    *num = 11;
    printf("son num: %d \n", *num);

    return NULL;
}

void a(){
    int num = 10;

    pthread_t son_id;
    pthread_create(&son_id, NULL, func, &num);

}
int main(){

    a();

    sleep(2);

    return 0;
}

