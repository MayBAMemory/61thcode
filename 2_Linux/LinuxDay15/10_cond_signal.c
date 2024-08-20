#include <header.h>

pthread_mutex_t lock;
pthread_cond_t cond;

void *func1(void *p){

    pthread_mutex_lock(&lock);

    pthread_cond_wait(&cond, &lock);
    printf(" func1 \n");

    pthread_mutex_unlock(&lock);
    return NULL;
}
void *func2(void *p){
    pthread_mutex_lock(&lock);

    pthread_cond_wait(&cond, &lock);
    printf(" func2 \n");

    pthread_mutex_unlock(&lock);

    return NULL;
}
int main(){
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_t son_id1, son_id2;
    pthread_create(&son_id1, NULL, func1, NULL);
    pthread_create(&son_id2, NULL, func2, NULL);


    sleep(10);
    pthread_cond_signal(&cond);

    pthread_join(son_id1, NULL);
    pthread_join(son_id2, NULL);
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;
}

