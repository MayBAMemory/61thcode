#include <header.h>

void *func(void *p){

    //return (void *) 10;
    void *str = malloc(10);
    strcpy((char *)str, "hello");

    return str;
}
int main(){

    pthread_t son_id;
    pthread_create(&son_id, NULL, func, NULL);


    //void *num;
    //pthread_join(son_id, &num);
    //printf("num: %ld \n",  (long)num);

    void *str;
    pthread_join(son_id, &str);
    printf("str: %s \n", (char *)str);
    free(str);
    
    return 0;
}

