#include <header.h>

int main(int argc,char*argv[])
{
    int flag = 0;

    if(fork() == 0){
        setsid();
        chdir("/");
        umask(0);
        for(int i = 0; i < 1024; i++){
            close(i);
        }
        while(1){
            sleep(1);

            // 获取当前时间
            time_t now = time(NULL);
            // 讲time_t转化为tm
            struct tm *local = localtime(&now);
            //获得时间
            int year = local->tm_year+1900;
            int month = local->tm_mon+1;
            int day = local->tm_mday;
            int hour = local->tm_hour;
            int min = local->tm_min;
            int second = local->tm_sec;

            // 日志打印
            if(flag == 0)
                syslog(LOG_INFO, "%d-%02d-%02d %02d:%02d:%02d \n", year, month, day, hour, min, second);
        }
    }
    return 0;
}
