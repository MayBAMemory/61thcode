#include <header.h>

void *func(void *p){

    printf("i am son ");

    pthread_exit(NULL);

    printf("i am son2 \n");
}
int main(){

    pthread_t son_id;
    pthread_create(&son_id, NULL, func, NULL);

    sleep(10);

    return 0;
}

