#include <stdio.h>
#include <time.h>
#include "clist.h"
static inline int compare_int(const void * a, const void * b) {
    //printf("key1=%d,key2=%d\n", *(int*)a, *(int *)b);
    return (*(int *)a == *(int *)b) ? 0 : 1;
}

void test1() {
    int j = 0;
    for(j = 0; j < 1000000; j++)
    {
        int arr[6] = {1,2,3,4,5,6};
        int i = 1;
        CList * l;
        CListElement * e;

        l = clist_init(compare_int);

        clist_insert(l, NULL, (void *)arr);
        clist_print(l);
        clist_delete(l, (void *)arr);

        clist_insert(l, NULL, (void *)(arr + 2));
        clist_insert(l, NULL, (void *)arr);
        clist_print(l);
        e = clist_search(l, &i);
        clist_insert(l, e, (void *)(arr + 1));
        clist_print(l);

        clist_insert(l, l->head->prev, (void *)(arr + 4));
        clist_print(l);
        i = 3;
        e = clist_search(l, &i);
        clist_insert(l, e, (void *)(arr + 3));
        clist_insert(l, l->head->prev, (void *)(arr + 5));
        clist_print(l);

        i = 1;
        clist_delete(l, &i);
        clist_print(l);
        i = 6;
        clist_delete(l, &i);
        clist_print(l);
        i = 3;
        clist_delete(l, &i);
        clist_print(l);
        i = 5;
        clist_delete(l, &i);
        clist_print(l);
        i = 4;
        clist_delete(l, &i);
        clist_print(l);
        clist_print(l);

        clist_destroy(l);
    }
    printf("c --- j == %d\n", j);
}

void test2() {
    int j = 0;
    for(j = 0; j <  1000000; j++) {
        int arr[6] = {1,2,3,4,5,6};
        int i = 1;
        CList * l;
        CListElement * e;
        l = clist_init_asm(compare_int);
        clist_insert_asm(l, NULL, (void *)arr);
        clist_print(l);
        clist_delete_asm(l, (void *)arr);

        clist_insert_asm(l, NULL, (void *)(arr + 2));
        clist_insert_asm(l, NULL, (void *)arr);
        clist_print(l);
        e = clist_search_asm(l, &i);
        clist_insert_asm(l, e, (void *)(arr + 1));
        clist_print(l);

        clist_insert_asm(l, l->head->prev, (void *)(arr + 4));
        clist_print(l);
        i = 3;
        e = clist_search_asm(l, &i);
        clist_insert_asm(l, e, (void *)(arr + 3));
        clist_insert_asm(l, l->head->prev, (void *)(arr + 5));
        clist_print(l);

        i = 1;
        clist_delete_asm(l, &i);
        clist_print(l);
        i = 6;
        clist_delete_asm(l, &i);
        clist_print(l);
        i = 3;
        clist_delete_asm(l, &i);
        clist_print(l);
        i = 5;
        clist_delete_asm(l, &i);
        clist_print(l);
        i = 4;
        clist_delete_asm(l, &i);
        clist_print(l);
        clist_print(l);
        clist_destroy_asm(l);
    }
    printf("a ---- j == %d\n", j);
}
void tt()
{
    printf("%d\n", 1);
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
