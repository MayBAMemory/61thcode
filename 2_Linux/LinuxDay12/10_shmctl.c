#include <header.h>

int main(){


    key_t key_id = ftok("./01_test", 10);


   int shmid = shmget(key_id,4096,0600|IPC_CREAT);
   char *p = (char *)shmat(shmid,NULL,0);


   
   int ret = shmctl(shmid,IPC_RMID,NULL);

    return 0;
}

