#include <header.h>

int num = 20;
int flag = 0; // 0没有加过票, 1: 加过票了
pthread_mutex_t lock;
pthread_cond_t cond;

void *func(void *p){


    pthread_mutex_lock(&lock);
    if(num < 5){
        // 可以加票
        num = num+10;
        flag = 1;
    }else{
        // 票数大于等于5张, 不可加票
        // -> 主动陷入阻塞, 把锁释放, 等待别人唤醒加票
        pthread_cond_wait(&cond, &lock);
        // 走到下面, 被别人唤醒 -> 意味着通知我加票
        num = num+10;
        flag = 1;
    }
    pthread_mutex_unlock(&lock);
    // 把卖票程序唤醒
    pthread_cond_signal(&cond);

    return NULL;
}
int main(){

    pthread_cond_init(&cond, NULL);
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

        // 走到这: 如果票数小于5张, 并且没有加过票 -> 喊醒加票程序加票
        //      并且自己陷入阻塞, 等待加票程序加票完成-> 把自己喊醒
        if(num < 5 && flag == 0){
            pthread_cond_signal(&cond);
            pthread_cond_wait(&cond, &lock);
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
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return 0;
}

