#include <header.h>

void a(){
    pthread_exit((void *) 100);
    return ;
}
void *func(void *p){

    a();
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

