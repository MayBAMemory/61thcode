#include <header.h>

// 两个线程访问堆上的数据

void * func(void *p){
    char *str = (char *)p;

    printf("son str: %s \n", str);
    strcpy(str, "123");
    printf("son str: %s \n", str);

    return NULL;
}
int main(){

    char *str = (char *)malloc(20);
    strcpy(str, "hello");

    pthread_t son_id;
    pthread_create(&son_id, NULL, func, (void *)str);

    printf("mian str: %s \n", str);
    sleep(1);
    printf("mian str: %s \n", str);


    free(str);
    return 0;
}

