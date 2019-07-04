#include <stdio.h>
#include "stack.h"
#include "stack_list.h"
#include <time.h>
void test1() {
int val[5] = {0, 1, 2, 4, 5};
    int * pi;
    int i = 0;
    for(i = 0; i < 100000000; i ++) {
        Stack * s = stack_init(1000);
        stack_push(s, val);
        stack_push(s, val + 1);
        stack_push(s, val + 2);
        stack_pop(s, (void **)(& pi));
        //printf("%d\n", *pi);
        stack_pop(s, (void **)(& pi));
        //printf("%d\n", *pi);
        stack_pop(s, (void **)(& pi));
        //printf("%d\n", *pi);
        stack_destroy(s);
    }
}

void test2() {
int val[5] = {0, 1, 2, 4, 5};
    int * pi;
    int i = 0;
    for(i = 0; i < 100000000; i ++) {
        Stack * s = stack_init_asm(1000);
        stack_push_asm(s, val);
        stack_push_asm(s, val + 1);
        stack_push_asm(s, val + 2);
        stack_pop_asm(s, (void **)(& pi));
        //printf("%d\n", *pi);
        stack_pop_asm(s, (void **)(& pi));
        //printf("%d\n", *pi);
        stack_pop_asm(s, (void **)(& pi));
        //printf("%d\n", *pi);
        stack_destroy_asm(s);
    }
}

void test3() {
int val[5] = {0, 1, 2, 4, 5};
    int * pi;
    int i = 0;
    for(i = 0; i < 10000000; i ++) {
        StackList s = stacklist_init();
        stacklist_push(s, val);
        stacklist_push(s, val + 1);
        stacklist_push(s, val + 2);
        stacklist_pop(s, (void **)(& pi));
        //printf("%d\n", *pi);
        stacklist_pop(s, (void **)(& pi));
        //printf("%d\n", *pi);
        //stacklist_pop(s, (void **)(& pi));
        //printf("%d\n", *pi);
        stacklist_destroy(s);
    }
}

void test4() {
int val[5] = {0, 1, 2, 4, 5};
    int * pi;
    int i = 0;
    for(i = 0; i < 10000000; i ++) {
        StackList s = stacklist_init_asm();
        stacklist_push_asm(s, val);
        stacklist_push_asm(s, val + 1);
        stacklist_push_asm(s, val + 2);
        stacklist_pop_asm(s, (void **)(& pi));
        //printf("%d\n", *pi);
        stacklist_pop_asm(s, (void **)(& pi));
        //printf("%d\n", *pi);
        //stacklist_pop(s, (void **)(& pi));
        //printf("%d\n", *pi);
        stacklist_destroy_asm(s);
    }
}

int main() {
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
