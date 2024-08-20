#include <header.h>

int num = 20;
int flag = 0; // 0没有加过票, 1: 加过票了
pthread_mutex_t lock;

void *func(void *p){

    // 加票
    while(1){

        pthread_mutex_lock(&lock);
        if(num < 5){
            num = num+10;
            flag = 1;
            pthread_mutex_unlock(&lock);
            break;
        }
        pthread_mutex_unlock(&lock);
    }


    return NULL;
}
int main(){

    pthread_mutex_init(&lock, NULL);
    pthread_t son_id;
    pthread_create(&son_id, NULL, func, NULL);

    // 卖票
    while(1){
        // 一直卖票

        pthread_mutex_lock(&lock);
        if(num <= 0 && flag == 1){
            // 意味着加过票, 也卖完了
            pthread_mutex_unlock(&lock);
            break;
        }

        // 走到这: 要么有票,  要么没票但是还没有加票
        if(num <= 0){
            // 票卖完还没有加票-> 等待加票
            pthread_mutex_unlock(&lock);
            continue;
        }

        // 有票: 产生随机数, 减票
        struct timeval nowTime;
        gettimeofday(&nowTime, NULL);
        srand((unsigned int) nowTime.tv_usec );
        double rand_num = (double)rand()/RAND_MAX;

        if(rand_num < 0.5){
            // 有人买票
            num--;
            printf("票卖一张: 剩余: %d \n", num);
        }

        pthread_mutex_unlock(&lock);

    }

    pthread_join(son_id, NULL);
    return 0;
}

