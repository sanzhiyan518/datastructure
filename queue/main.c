#include "queue.h"
#include <stdio.h>
#include <time.h>

void test1() {
    int val[5] = {0, 1, 2, 4, 5};
    int * pi;
    int i = 0;
    for(i = 0; i < 100000000; i ++) {
        Queue * q = queue_init(3);
        queue_enter(q, val);
        queue_enter(q, val + 1);
        queue_enter(q, val + 2);
        queue_enter(q, val + 3);
        queue_delete(q, (void **)(&pi));
        //printf("%d\n", *pi);
        queue_delete(q, (void **)(&pi));
        //printf("%d\n", *pi);
        queue_delete(q, (void **)(&pi));
        //printf("%d\n", *pi);
        queue_delete(q, (void **)(&pi));
        //printf("%d\n", *pi);
        queue_enter(q, val + 3);
        queue_delete(q, (void **)(&pi));
        //printf("%d\n", *pi);
        queue_destroy(q);
    }
}

void test2() {
    int val[5] = {0, 1, 2, 4, 5};
    int * pi;
    int i = 0;
    for(i = 0; i < 100000000; i ++) {
        Queue * q = queue_init_asm(3);
        queue_enter_asm(q, val);
        queue_enter_asm(q, val + 1);
        queue_enter_asm(q, val + 2);
        queue_enter_asm(q, val + 3);
        queue_delete_asm(q, (void **)(&pi));
        //printf("%d\n", *pi);
        queue_delete_asm(q, (void **)(&pi));
        //printf("%d\n", *pi);
        queue_delete_asm(q, (void **)(&pi));
        //printf("%d\n", *pi);
        queue_delete_asm(q, (void **)(&pi));
        //printf("%d\n", *pi);
        queue_enter_asm(q, val + 3);
        queue_delete_asm(q, (void **)(&pi));
        //printf("%d\n", *pi);
        queue_destroy_asm(q);
    }
}

void test3() {
    int val[5] = {0, 1, 2, 4, 5};
    int * pi;
    int i = 0;
    for(i = 0; i < 100000000; i ++) {
        QueueList * q = queuelist_init();
        queuelist_enter(q, val);
        queuelist_enter(q, val + 1);
        queuelist_enter(q, val + 2);
        queuelist_delete(q, (void **)(&pi));
        //printf("%d\n", *pi);
        queuelist_delete(q, (void **)(&pi));
//        printf("%d\n", *pi);
//        queuelist_delete(q, (void **)(&pi));
//        printf("%d\n", *pi);
//        queuelist_delete(q, (void **)(&pi));
//        printf("%d\n", *pi);
//        queuelist_delete(q, (void **)(&pi));
//        printf("%d\n", *pi);
        queuelist_destroy(q);
    }
}

void test4() {
    int val[5] = {0, 1, 2, 4, 5};
    int * pi;
    int i = 0;
    for(i = 0; i < 100000000; i ++) {
        QueueList * q = queuelist_init_asm();
        queuelist_enter_asm(q, val);
        queuelist_enter_asm(q, val + 1);
        queuelist_enter_asm(q, val + 2);
        queuelist_delete_asm(q, (void **)(&pi));
        //printf("%d\n", *pi);
        queuelist_delete_asm(q, (void **)(&pi));
        //printf("%d\n", *pi);
//        queuelist_delete_asm(q, (void **)(&pi));
//        printf("%d\n", *pi);
//        queuelist_delete_asm(q, (void **)(&pi));
//        printf("%d\n", *pi);
//        queuelist_delete_asm(q, (void **)(&pi));
//        printf("%d\n", *pi);
        queuelist_destroy_asm(q);
    }
}
int main(){
    time_t start,stop;
    start = time(NULL);
    test3();
    stop = time(NULL);
    printf("c---Use Time:%ld\n",(stop-start));


    start = time(NULL);
    test4();
    stop = time(NULL);
    printf("c---Use Time:%ld\n",(stop-start));

}
