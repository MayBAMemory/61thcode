#include <header.h>

int main(){

    int socket_fd[2];
    socketpair(AF_LOCAL, SOCK_STREAM, 0, socket_fd);

    if(fork() == 0){

        int x = open("./01_client", O_RDONLY);
        // socket_fd[0]: 收信息

        struct msghdr msg;
        bzero(&msg, sizeof(msg));

        // 准备正文信息
        char str[60] = {0};
        struct iovec vec[1];
        vec[0].iov_base = str;
        vec[0].iov_len = sizeof(str);

        msg.msg_iov = vec;
        msg.msg_iovlen = 1;

        // 准备控制信息
        struct cmsghdr *cms = (struct cmsghdr *) malloc( CMSG_LEN(sizeof(int)) );
        cms->cmsg_len = CMSG_LEN(sizeof(int)); // 指明这个结构体的大小
        cms->cmsg_level = SOL_SOCKET;
        cms->cmsg_type = SCM_RIGHTS;


        msg.msg_control = cms;
        msg.msg_controllen = CMSG_LEN(sizeof(int));


        sleep(3);
        recvmsg(socket_fd[0], &msg, 0);


        void *p = CMSG_DATA(cms);
        int *fd = (int *)p;
        printf("son file_fd: %d \n", *fd);

        write(*fd, "123456789", 9);

        close(socket_fd[0]);
        close(socket_fd[1]);

        close(*fd);
    }else{
        // socket_fd[1]: 发信息
        int file_fd = open("1.txt", O_RDWR);
        printf("main: %d \n", file_fd);

        struct msghdr msg;
        bzero(&msg, sizeof(msg));

        // 准备正文信息
        char *str = "hello";
        struct iovec vec[1];
        vec[0].iov_base = str;
        vec[0].iov_len = strlen(str);

        msg.msg_iov = vec;
        msg.msg_iovlen = 1;

        // 准备控制信息

        struct cmsghdr *cms = (struct cmsghdr *) malloc( CMSG_LEN(sizeof(int)) );
        cms->cmsg_len = CMSG_LEN(sizeof(int)); // 指明这个结构体的大小
        cms->cmsg_level = SOL_SOCKET;
        cms->cmsg_type = SCM_RIGHTS;

        void *p = CMSG_DATA(cms);
        int *fd = (int *)p;
        *fd = file_fd;

        msg.msg_control = cms;
        msg.msg_controllen = CMSG_LEN(sizeof(int));


        sendmsg(socket_fd[1], &msg, 0);

        close(file_fd);
        sleep(10);


        close(socket_fd[0]);
        close(socket_fd[1]);
    }

    return 0;
}

