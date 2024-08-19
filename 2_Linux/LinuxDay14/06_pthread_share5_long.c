#include <header.h>

void *func(void *p){

    long num = (long) p;
    num++;

    printf("son: %ld \n", num);

    return NULL;
}
int main(){

    long num = 10;

    pthread_t son_id;
    pthread_create(&son_id, NULL, func, (void *)num);

    sleep(1);

    printf("main num: %ld \n", num);

    return 0;
}

