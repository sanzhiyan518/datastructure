#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "clist.h"
typedef struct TestStruct {
    int i;
    int j;
}TestStruct;

typedef struct MStruct {
    int *p;
    int i ;
} MStruct;

void clist_print(CList * list)
{
    CListElement * pos = list->head;
    do {
        TestStruct * p = (TestStruct *)(pos->data);
        printf("--%d--", p->i);
        pos = pos->next;
    } while(pos != list->head);
    printf("\n");
}

CListElement * clist_search(CList * list, int i, int j) {
    CListElement * pos = list->head;
    do {
        TestStruct * p = (TestStruct *)(pos->data);
        if(i == p->i && j == p->j)
            return pos;
        pos = pos->prev;
    } while(pos != list->head);
    return NULL;
}

void test() {
    int i = 0;
    CList * list = (CList *)malloc(sizeof(CList));
    CListElement * pos;
    TestStruct *p ;

    clist_init(list, free);

    for(; i < 5; i++) {
        p = (TestStruct *)malloc(sizeof(TestStruct));
        p->i = i;
        p->j = i + 100;
        clist_ins_next(list, list->head, p);
    }

    //clist_print(list);
    for(i = 5; i < 10; i++) {
        p = (TestStruct *)malloc(sizeof(TestStruct));
        p->i = i;
        p->j = i + 100;
        clist_ins_next(list, list->head->prev, p);
    }
    //clist_print(list);

    pos = clist_search(list, 2, 102);
    if(clist_rem_next(list, pos, (void **)&p) == 0)
        free(p);

    if(clist_rem_next(list, list->head->prev, (void **)&p) == 0)
        free(p);


    //clist_print(list);

    while(clist_size(list) > 2) {
        if(clist_rem_next(list, list->head, (void **)&p) == 0)
            free(p);
    }

    clist_destroy(list);
    free(list);
}

void test_asm() {
    int i = 0;
    CList * list = (CList *)malloc(sizeof(CList));
    CListElement * pos;
    TestStruct *p ;

    clist_init_asm(list, free);

    for(; i < 5; i++) {
        p = (TestStruct *)malloc(sizeof(TestStruct));
        p->i = i;
        p->j = i + 100;
        clist_ins_next_asm(list, list->head, p);
    }

    //clist_print(list);
    for(i = 5; i < 10; i++) {
        p = (TestStruct *)malloc(sizeof(TestStruct));
        p->i = i;
        p->j = i + 100;
        clist_ins_next_asm(list, list->head->prev, p);
    }
    //clist_print(list);

    pos = clist_search(list, 2, 102);
    if(clist_rem_next_asm(list, pos, (void **)&p) == 0)
        free(p);

    if(clist_rem_next_asm(list, list->head->prev, (void **)&p) == 0)
        free(p);


    //clist_print(list);

    while(clist_size(list) > 2) {
        if(clist_rem_next_asm(list, list->head, (void **)&p) == 0)
            free(p);
    }

    clist_destroy_asm(list);
    free(list);
}

int main() {
    int i = 0;
    int t = 0;



    t = clock();
    for(; i < 100000000; i++)
        test();

    printf("C Use Time:%.31f ms\n", (double)(clock() - t)/CLOCKS_PER_SEC * 1000);

     t = clock();
    for(i = 0; i < 100000000; i++)
        test_asm();
    printf("ASM Use Time:%.31f ms\n", (double)(clock() - t)/CLOCKS_PER_SEC * 1000);
    return 0;
}
