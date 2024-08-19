#include <header.h>

void *func(void *p){

    sleep(10);

    return (void *)3;
}
int main(){

    pthread_t son_id;
    pthread_create(&son_id, NULL, func, NULL);

    printf("main1 \n");

    void *num;
    pthread_join(son_id, &num);
    printf("main2: %ld \n", (long )num);

    return 0;
}

