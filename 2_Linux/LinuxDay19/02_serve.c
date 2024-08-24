#include <header.h>

// 定义一个结构体, 用来描述某一个客户端的链接状态
typedef struct client_s{
    int net_fd;
    int alive;
    time_t last_time;// 用来记录当前这个用户, 上一次的说话时间
} client_t;

int main(){

    char *port = "8080";
    char *ip = "192.168.106.130";

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    int reuse = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(port));
    sockaddr.sin_addr.s_addr = inet_addr(ip);
    bind(socket_fd, (struct sockaddr *)&sockaddr,  sizeof(sockaddr));

    listen(socket_fd, 10);


    client_t list[100];// 用来存储连接的数组
    memset(list, 0, sizeof(list));
    int size = 0; // 记录数组中存储到那个位置了

    fd_set base_set;
    FD_ZERO(&base_set);
    FD_SET(socket_fd, &base_set);

    // 让程序一直运行
    while(1){
        fd_set set;
        memcpy(&set, &base_set, sizeof(base_set));

        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        select(100, &set, NULL, NULL, &tv);

        if(FD_ISSET(socket_fd, &set)){
            // 有新链接仅来: 获得新链接, 存储, 监听
            int net_fd = accept(socket_fd, NULL, NULL);
            // 记录这个链接
            list[size].net_fd = net_fd;
            list[size].alive = 1;
            time(&list[size].last_time);
            size++;
            // 放入监听
            FD_SET(net_fd, &base_set);
        }
        // 需要检测, 是不是某个客户端发信息, 导致select就绪
        // 遍历所有链接
        for(int i=0; i<size; i++){
            if(list[i].alive == 1 && FD_ISSET(list[i].net_fd, &set)){
                // 就是这个i位置的客户端发信息: 读取信息转发
                char buf[60] = {0};
                int ret_recv = recv(list[i].net_fd, buf, sizeof(buf), 0);
                time(&list[i].last_time);
                if(ret_recv == 0){
                    printf("连接断开 \n");
                    // 说明这个客户端, 断开了连接: 修改状态, 移除监听
                    list[i].alive = 0;
                    FD_CLR(list[i].net_fd, &base_set);
                    close(list[i].net_fd);
                    continue;
                }
                // 走到这, 读到了这个客户端的数据-> 转发
                // 遍历所有客户端, 转发
                for(int j=0; j<size; j++){
                    if(i==j || list[j].alive ==0){
                        continue;
                    }
                    send(list[j].net_fd, buf, sizeof(buf), 0);
                }

            }
        }

        // 检测是否超时
        for(int k=0; k<size; k++){
            time_t now_time;
            time(&now_time);
            if(list[k].alive == 1 && now_time-list[k].last_time > 10){
                // 超时剔除: 
                list[k].alive = 0;
                FD_CLR(list[k].net_fd, &base_set);
                close(list[k].net_fd);
            }
        }
    }


    return 0;
}

