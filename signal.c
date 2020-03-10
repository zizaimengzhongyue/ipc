#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
int main() {
    pid_t result;
    int ret;
    result = fork();
    if (result < 0) {
        perror("创建子进程失败");
    } else if (result == 0) {
        //子进程
        raise(SIGSTOP);
        exit(0);
    } else {
        //父进程
        printf("父进程的进程号(PID)是: %d; 子进程的进程号(PID)是: %d\n", getpid(), result);
        ret = kill(result, SIGKILL);
        if (ret == 0) {
            printf("kill 函数返回值是: %d, 发出的 SIGKILL 信号结束的子进程进程号: %d\n", ret, result);
        } else {
            perror("kill 函数结束子进程失败\n");
        }
    }
    return 0;
}
