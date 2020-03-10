#include<string.h>
#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
int main() {
    pid_t result;
    int r_num;
    int pipe_fd[2];
    char buf_r[100], buf_w[100];
    memset(buf_r, 0, sizeof(buf_r));
    if (pipe(pipe_fd) < 0) {
        printf("创建管道失败\n");
        return -1;
    }
    result = fork();
    if (result < 0) {
        perror("创建管道失败\n");
        return -1;
    } else if (result == 0) {
        close(pipe_fd[1]);
        r_num = read(pipe_fd[0], buf_r, 100);
        if (r_num > 0) {
            printf("子进程从管道读取 %d 个字符，读取的字符串是: %s\n", r_num, buf_r);
            close(pipe_fd[0]);
            exit(0);
        } 
    } else {
        close(pipe_fd[0]);
        printf("请从键盘输入写入管道的字符串: \n");
        scanf("%s", buf_w);
        if (write(pipe_fd[1], buf_w, strlen(buf_w)) != -1) {
            printf("父进程向管道写入: %s\n", buf_w);
            close(pipe_fd[1]);
            waitpid(result, NULL, 0);
            exit(0);
        }
    }
    
    return 0;
}

