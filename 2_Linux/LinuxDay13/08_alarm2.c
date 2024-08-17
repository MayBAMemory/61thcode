#include <header.h>

void func(int sig_value){
}
void mySleep(int sec){
   signal(SIGALRM, func);

   alarm(sec);

   sigset_t set;
   sigemptyset(&set);
   sigsuspend(&set);
}
int main(int argc,char*argv[])
{
   printf("-- \n");
   mySleep(10);
   printf("-- \n");
   mySleep(2);
   printf("-- \n");
   return 0;
}
