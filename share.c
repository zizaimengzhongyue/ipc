#include<sys/types.h>
#include<unistd.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct {
    char name[4];
    int age;
} people;

int main(int argc, char* *argv) {
    pid_t result;
    people *p_map;
    char temp;
    p_map = (people *)mmap(NULL, sizeof(people) * 10, PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    result = fork();
    if (result < 0) {
        perror("创建子进程失败");
        exit(0);
    } else if (result == 0) {
        sleep(2);
        int age = 0;
        for (int i = 0; i < 5; i++) {
            printf("子进程读取: 第 %d 个人的年龄是: %d\n", i + 1, (*(p_map + i)).age);
            age += (*(p_map + i)).age;
        }
        (*p_map).age = age;
        munmap(p_map, sizeof(people) * 10);
        exit(0);
    } else {
        temp = 'a';
        for (int i = 0; i < 5; i++) {
            temp += 1;
            memcpy((*(p_map + i)).name, &temp, 2);
            (*(p_map + i)).age = 20 + i;
        }
        sleep(5);
        printf("父进程读取: 五个人的年龄和是: %d\n", (*p_map).age);
        printf("解除内存映射...\n");
        munmap(p_map, sizeof(people) * 10);
        printf("解除内存映射成功\n");
    }
}