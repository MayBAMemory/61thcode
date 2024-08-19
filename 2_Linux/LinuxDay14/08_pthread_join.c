#include <header.h>

void *func(void *p){

    sleep(30);

    return NULL;
}
int main(){

    pthread_t son_id;
    pthread_create(&son_id, NULL, func, NULL);

    printf("main1 \n");

    pthread_join(son_id, NULL);
    printf("main2 \n");

    return 0;
}

