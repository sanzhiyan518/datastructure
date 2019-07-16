#include "stack.h"
#include <stdlib.h>
#include <time.h>

void test_liststack() {
    ListStack * s = (ListStack *)malloc(sizeof(ListStack));
    int i = 0;
    int  * p;

    liststack_init(s, free);
    for(i = 0; i < 10; i ++) {
        p = (int *)malloc(sizeof(int));
        *p = i;
        liststack_push(s, p);
    }

    for(i = 0; i < 10; i++) {
        if(liststack_pop(s, (void **)&p)  == 0)
            free(p);
    }

    i = liststack_is_empty(s);

    for(i = 0; i < 5; i++) {
        p = (int *)malloc(sizeof(int));
        *p = i;
        liststack_push(s, p);
    }

    p = liststack_peek(s);

    liststack_destroy(s);
    free(s);
}

void test_arraystack() {
    ArrayStack * s = (ArrayStack *)malloc(sizeof(ArrayStack));
    int i = 0;
    int  * p;

    s->deepth = 10;

    arraystack_init(s, free);
    for(i = 0; i < 10; i ++) {
        p = (int *)malloc(sizeof(int));
        *p = i;
        arraystack_push(s, p);
    }

    for(i = 0; i < 10; i++) {
        if(arraystack_pop(s, (void **)&p)  == 0)
            free(p);
    }

    i = arraystack_is_empty(s);

    for(i = 0; i < 5; i++) {
        p = (int *)malloc(sizeof(int));
        *p = i;
        arraystack_push(s, p);
    }

    p = arraystack_peek(s);

    arraystack_destroy(s);
    free(s);
}

void test_liststack_asm() {
    ListStack * s = (ListStack *)malloc(sizeof(ListStack));
    int i = 0;
    int  * p;

    liststack_init_asm(s, free);
    for(i = 0; i < 10; i ++) {
        p = (int *)malloc(sizeof(int));
        *p = i;
        liststack_push_asm(s, p);
    }

    for(i = 0; i < 10; i++) {
        if(liststack_pop_asm(s, (void **)&p)  == 0)
            free(p);
    }

    i = liststack_is_empty(s);

    for(i = 0; i < 5; i++) {
        p = (int *)malloc(sizeof(int));
        *p = i;
        liststack_push_asm(s, p);
    }

    p = liststack_peek(s);

    liststack_destroy_asm(s);
    free(s);
}

void test_arraystack_asm() {
    ArrayStack * s = (ArrayStack *)malloc(sizeof(ArrayStack));
    int i = 0;
    int  * p;

    s->deepth = 10;

    arraystack_init_asm(s, free);
    for(i = 0; i < 10; i ++) {
        p = (int *)malloc(sizeof(int));
        *p = i;
        arraystack_push_asm(s, p);
    }

    for(i = 0; i < 10; i++) {
        if(arraystack_pop_asm(s, (void **)&p)  == 0)
            free(p);
    }

    i = arraystack_is_empty(s);

    for(i = 0; i < 5; i++) {
        p = (int *)malloc(sizeof(int));
        *p = i;
        arraystack_push_asm(s, p);
    }

    p = arraystack_peek(s);

    arraystack_destroy_asm(s);
    free(s);
}

#define MAX_LOOP 10000000
int main() {
    int i;
    clock_t  t = 0;

    printf("ArrayStack's size is %ld\n", sizeof(ArrayStack));
    printf("The member of ArrayStack deepth's offset is %ld\n", (size_t)( &((ArrayStack *)0)->deepth));
    printf("The member of ArrayStack deepth's offset is %ld\n", (size_t)&((ArrayStack *)0)->top);
    printf("The member of ArrayStack deepth's offset is %ld\n", (size_t)&((ArrayStack *)0)->data);

    t = clock();
    for(i= 0; i < MAX_LOOP; i++)
        test_liststack();
    printf("C list stack Use Time:%f ms\n", (double)(clock() - t)/CLOCKS_PER_SEC * 1000);

    t = clock();
    for(i= 0; i < MAX_LOOP; i++)
        test_arraystack();
    printf("C array stack Use Time:%f ms\n", (double)(clock() - t)/CLOCKS_PER_SEC * 1000);

    t = clock();
    for(i= 0; i < MAX_LOOP; i++)
        test_liststack_asm();
    printf("ASM list stack Use Time:%f ms\n", (double)(clock() - t)/CLOCKS_PER_SEC * 1000);

    t = clock();
    for(i= 0; i < MAX_LOOP; i++)
        test_arraystack_asm();
    printf("ASM array stack Use Time:%f ms\n", (double)(clock() - t)/CLOCKS_PER_SEC * 1000);

    return 0;
}
