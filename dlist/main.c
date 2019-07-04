#include <stdio.h>
#include <time.h>
#include "dlist.h"
static inline int compare_int(const void * a, const void * b) {
    //printf("key1=%d,key2=%d\n", *(int*)a, *(int *)b);
    return (*(int *)a == *(int *)b) ? 1 : 0;
}

void test1() {
    int j = 0;
    for(j = 0; j < 100000; j++) {
        int arr[6] = {1,2,3,4,5,6};
        int i = 1;
        DList * l;
        DListElement * e;

        l = dlist_init(compare_int);

        dlist_insert(l, NULL, (void *)arr);
        dlist_print(l);
        dlist_delete(l, (void *)arr);

        dlist_insert(l, NULL, (void *)(arr + 2));
        dlist_insert(l, NULL, (void *)arr);
        dlist_print(l);
        e = dlist_search(l, &i);
        dlist_insert(l, e, (void *)(arr + 1));
        dlist_print(l);

        dlist_append(l, (void *)(arr + 4));
        dlist_print(l);
        i = 3;
        e = dlist_search(l, &i);
        dlist_insert(l, e, (void *)(arr + 3));
        dlist_append(l, (void *)(arr + 5));
        dlist_print(l);

        i = 1;
        dlist_delete(l, &i);
        dlist_print(l);
        i = 6;
        dlist_delete(l, &i);
        dlist_print(l);
        i = 3;
        dlist_delete(l, &i);
        dlist_print(l);
        i = 5;
        dlist_delete(l, &i);
        dlist_print(l);
        i = 4;
        dlist_delete(l, &i);
        dlist_print(l);
        dlist_print(l);

        dlist_destroy(l);
    }
}

void test2() {
    int j = 0;
    for(j = 0; j < 100000; j++) {
        int arr[6] = {1,2,3,4,5,6};
        int i = 1;
        DList * l;
        DListElement * e;

        l = dlist_init_asm(compare_int);

        dlist_insert_asm(l, NULL, (void *)arr);
        dlist_print(l);
        dlist_delete_asm(l, (void *)arr);

        dlist_insert_asm(l, NULL, (void *)(arr + 2));
        dlist_insert_asm(l, NULL, (void *)arr);
        dlist_print(l);
        e = dlist_search_asm(l, &i);
        dlist_insert_asm(l, e, (void *)(arr + 1));
        dlist_print(l);

        dlist_append(l, (void *)(arr + 4));
        dlist_print(l);
        i = 3;
        e = dlist_search_asm(l, &i);
        dlist_insert_asm(l, e, (void *)(arr + 3));
        dlist_append(l, (void *)(arr + 5));
        dlist_print(l);

        i = 1;
        dlist_delete_asm(l, &i);
        dlist_print(l);
        i = 6;
        dlist_delete_asm(l, &i);
        dlist_print(l);
        i = 3;
        dlist_delete_asm(l, &i);
        dlist_print(l);
        i = 5;
        dlist_delete_asm(l, &i);
        dlist_print(l);
        i = 4;
        dlist_delete_asm(l, &i);
        dlist_print(l);
        dlist_print(l);

        dlist_destroy_asm(l);
    }
}
int main() {
    time_t start,stop;
    int i = 0;
    for(; i < 10; i++) {
    start = time(NULL);
    test1();
    stop = time(NULL);
    printf("c---Use Time:%ld\n",(stop-start));

    start = time(NULL);
    test2();
    stop = time(NULL);
    printf("a----Use Time:%ld\n",(stop-start));
    }
    return 0;
}
