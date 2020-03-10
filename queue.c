#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<unistd.h>

struct msgmbuf {
    long msg_type;
    char msg_text[512];
};

int main() {
    int qid;
    key_t key;
    int len;
    struct msgmbuf msg;
    key = ftok(".", 123);
    if (key == -1) {
        perror("创建消息队列出错\n");
        exit(1);
    }
    qid = msgget(key, IPC_CREAT|0666);
    if (qid == -1) {
        perror("创建消息队列出错\n");
        exit(1);
    }
    printf("创建、打开的队列号是: %d\n", qid);
    puts("请输入要加入队列的消息: ");
    if((fgets((&msg)->msg_text, 512, stdin)) == NULL) {
        puts("没有消息");
        exit(1);
    }
    msg.msg_type = getpid();
    len = strlen(msg.msg_text);
    if (msgsnd(qid, &msg, len, 0) < 0) {
        perror("添加消息出错");
        exit(1);
    }
    if(msgrcv(qid, &msg, 512, 0, 0) < 0) {
        perror("添加消息出错");
        exit(1);
    }
    printf("读取的消息是: %s\n", (&msg)->msg_text);
    if(msgctl(qid, IPC_RMID, NULL) < 0) {
        perror("删除消息队列出错");
        exit(1);
    }
    exit(0);
}