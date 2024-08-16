#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main() {
    int shm_fd = shm_open("/test", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, 4096);

    void *ptr = mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    if (fork() == 0) {
        sprintf((char *)ptr, "Hello from child!");
    } else { 
        wait(NULL); 
        printf("shared memory: %s \n", (char *)ptr);
    }

    munmap(ptr, 4096);
    shm_unlink("/test");
    return 0;
}
