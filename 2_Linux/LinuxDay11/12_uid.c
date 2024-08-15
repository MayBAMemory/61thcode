#include <header.h>

int main(){
    // 获得真实的程序用户id, 和 真实的程序用户组id
  printf("current process uid: %d \n", getuid());
  printf("current process group uid: %d \n", getgid());


  printf("current process euid: %d \n", geteuid());
  printf("current process e group uid: %d \n", getegid());

    return 0;
}

