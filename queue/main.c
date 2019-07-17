#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "queue.h"

void test_arrayqueue() {
    ArrayQueue * q = (ArrayQueue *)malloc(sizeof(ArrayQueue));
    int i = 0;
    int  * p;

    q->capacity = 10;
    arrayqueue_init(q, free);

    for(i = 0; i < 10; i ++) {
        p = (int *)malloc(sizeof(int));
        *p = i;
        arrayqueue_enqueue(q, p);
    }

    for(i = 0; i < 10; i++) {
        if(arrayqueue_dequeue(q, (void **)&p)  == 0)
            free(p);
    }

    i = arrayqueue_is_empty(q);

    arrayqueue_destroy(q);

    q->capacity = 3;
    arrayqueue_init(q, free);

    for(i = 0; i < 5; i++) {
        p = (int *)malloc(sizeof(int));
        *p = i;
        arrayqueue_enqueue(q, p);
        if(i >=2)
            if(arrayqueue_dequeue(q, (void **)&p)  == 0)
                free(p);
    }

    arrayqueue_destroy(q);
    free(q);
}

void test_listqueue() {
    ListQueue * q = (ListQueue *)malloc(sizeof(ListQueue));
    int i = 0;
    int  * p;

    listqueue_init(q, free);

    for(i = 0; i < 10; i ++) {
        p = (int *)malloc(sizeof(int));
        *p = i;
        listqueue_enqueue(q, p);
    }

    for(i = 0; i < 10; i++) {
        if(listqueue_dequeue(q, (void **)&p)  == 0)
            free(p);
    }

    i = listqueue_is_empty(q);

    listqueue_destroy(q);

    listqueue_init(q, free);

    for(i = 0; i < 5; i++) {
        p = (int *)malloc(sizeof(int));
        *p = i;
        listqueue_enqueue(q, p);
        if(i >=2)
            if(listqueue_dequeue(q, (void **)&p)  == 0)
                free(p);
    }

    listqueue_destroy(q);
    free(q);
}

void test_arrayqueue_asm() {
    ArrayQueue * q = (ArrayQueue *)malloc(sizeof(ArrayQueue));
    int i = 0;
    int  * p;

    q->capacity = 10;
    arrayqueue_init_asm(q, free);
    //memset(q->data, 0, 80);
    for(i = 0; i < 10; i ++) {
        p = (int *)malloc(sizeof(int));
        *p = i;
        arrayqueue_enqueue_asm(q, p);
    }

    for(i = 0; i < 10; i++) {
        if(arrayqueue_dequeue_asm(q, (void **)&p)  == 0)
            free(p);
    }

    i = arrayqueue_is_empty(q);

    arrayqueue_destroy_asm(q);

    q->capacity = 3;
    arrayqueue_init_asm(q, free);

    for(i = 0; i < 5; i++) {
        p = (int *)malloc(sizeof(int));
        *p = i;
        arrayqueue_enqueue_asm(q, p);
        if(i >=2)
            if(arrayqueue_dequeue_asm(q, (void **)&p)  == 0)
                free(p);
    }

    arrayqueue_destroy_asm(q);
    free(q);
}

void test_listqueue_asm() {
    ListQueue * q = (ListQueue *)malloc(sizeof(ListQueue));
    int i = 0;
    int  * p;

    listqueue_init_asm(q, free);

    for(i = 0; i < 10; i ++) {
        p = (int *)malloc(sizeof(int));
        *p = i;
        listqueue_enqueue_asm(q, p);
    }

    for(i = 0; i < 10; i++) {
        if(listqueue_dequeue_asm(q, (void **)&p)  == 0)
            free(p);
    }

    i = listqueue_is_empty(q);

    listqueue_destroy_asm(q);

    listqueue_init_asm(q, free);

    for(i = 0; i < 5; i++) {
        p = (int *)malloc(sizeof(int));
        *p = i;
        listqueue_enqueue_asm(q, p);
        if(i >=2)
            if(listqueue_dequeue_asm(q, (void **)&p)  == 0)
                free(p);
    }

    listqueue_destroy_asm(q);
    free(q);
}


#define MAX_LOOP 10000000

int main() {
    int i, j;
    clock_t  t = 0;

    printf("ArrayQueue's size is %ld\n", sizeof(ArrayQueue));
    printf("The member of ArrayQueue capacity's offset is %ld\n", (size_t)( &((ArrayQueue *)0)->capacity));
    printf("The member of ArrayQueue size's offset is %ld\n", (size_t)( &((ArrayQueue *)0)->size));
    printf("The member of ArrayQueue front's offset is %ld\n", (size_t)( &((ArrayQueue *)0)->front));
    printf("The member of ArrayQueue rear's offset is %ld\n", (size_t)( &((ArrayQueue *)0)->rear));
    printf("The member of ArrayQueue data's offset is %ld\n", (size_t)( &((ArrayQueue *)0)->data));

    for(j= 0; j < 10; j++) {
        t = clock();
        for(i= 0; i < MAX_LOOP; i++)
            test_arrayqueue();
        printf("C array queue Use Time:%f ms\n", (double)(clock() - t)/CLOCKS_PER_SEC * 1000);

        t = clock();
        for(i= 0; i < MAX_LOOP; i++)
            test_listqueue();
        printf("C list queue Use Time:%f ms\n", (double)(clock() - t)/CLOCKS_PER_SEC * 1000);

            t = clock();
        for(i= 0; i < MAX_LOOP; i++)
            test_arrayqueue_asm();
        printf("ASM array queue Use Time:%f ms\n", (double)(clock() - t)/CLOCKS_PER_SEC * 1000);

        t = clock();
        for(i= 0; i < MAX_LOOP; i++)
            test_listqueue_asm();
        printf("ASM list queue Use Time:%f ms\n", (double)(clock() - t)/CLOCKS_PER_SEC * 1000);
    }
    return 0;
}
