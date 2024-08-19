#include <header.h>

void *func(void *p){
    printf("i am son \n");

    return NULL;
}
int main(){

    pthread_t son_id;
    int ret = pthread_create(&son_id, NULL, func, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_create");


    printf("i am main \n");

    usleep(30);

    return 0;
}

