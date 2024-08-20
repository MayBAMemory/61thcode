#include <header.h>
char *fun(){
    static char p[20] = {0};
    for(int i=0; i<20; i++){
        if(p[i] == 0){
            p[i] = 'a';
            break;
        }
    }
    return p;
}

int sum(int num1, int num2){
    return num1+num2;
}
int main(int argc,char*argv[])
{
    char *p1 = fun();
    printf("p = %s \n", p1);

    char *p2 = fun();
    printf("p = %s \n", p2);
    return 0;
}
