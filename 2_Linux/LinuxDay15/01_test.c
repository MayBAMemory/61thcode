#include <header.h>
int num =10;


// A线程
void *func(void *p){

    //pthread_exit(NULL);

    return NULL;
}

// 主线程
int main(){

    //pthread_create( 新的线程的id, 给新的线程的属性,  新的线程的入口函数,  给新的线程传参 );

    // pthread_exit(NULL);

    //pthread_cancel(A线程的id);

    //pthread_join(要捕捉的退出的线程id,   这个退出线程的返回值);
    return 0;
}

