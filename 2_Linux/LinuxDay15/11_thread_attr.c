#include <header.h>

// 给线程设置属性
void *func(void *arg){

    return NULL;
}
int main(int argc,char*argv[])
{
   pthread_attr_t attr;
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

   pthread_t tid;
   pthread_create(&tid, &attr, func, NULL);

   int res = pthread_join(tid, NULL);
   THREAD_ERROR_CHECK(res, "join");

   pthread_attr_destroy(&attr);
   return 0;
}
