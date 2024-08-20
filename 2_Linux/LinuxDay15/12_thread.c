#include <header.h>
// ctime的线程安全问题
void *func(void *arg){

   time_t childTime;
   time(&childTime);
   char *str = ctime(&childTime);

   printf("child time = %s \n", str);
   sleep(5);
   printf("child time = %s \n", str);
}
int main(int argc,char*argv[])
{
   pthread_t tid;
   pthread_create(&tid,NULL,func, NULL);

   sleep(3);
   time_t mainTime;
   time(&mainTime);

   printf("main time = %s \n", ctime(&mainTime));

   pthread_join(tid, NULL);
   return 0;
}
