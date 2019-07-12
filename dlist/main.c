#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "dlist.h"

static int match_int(const void * data1, const void * data2) {
    return (*(int *)data1 == *(int *)data2) ? 1 : 0;
}
/*
static void dlist_int_print(DList * list) {
    DListElement * element = dlist_head(list);

    while(element != NULL) {
        printf("--%d--", *(int *)(dlist_data(element)));
        element = dlist_next(element);
    }
    printf("\n");
}
*/
static DListElement * dlist_search(DList * list, void * data) {
    DListElement * element = dlist_head(list);
    match match = list->match;

    if(match == NULL)
        return NULL;

    while(element != NULL) {
        if(match(data, dlist_data(element)))
            return element;
        element = dlist_next(element);
    }

    return NULL;
}

void test_int() {
    int ** array = (int **)malloc(sizeof(int*) * 8);
    int i = 0;
    DList * list = (DList *)malloc(sizeof(DList));
    DListElement * element;
    int * pi;

    for(i = 0; i < 8; i++) {
        pi = (int *)malloc(sizeof(int));
        *pi = i;
        array[i] = pi;
    }

    dlist_init(list, free);
    list->match = match_int;

    dlist_ins_prev(list, NULL, array[0]); //[0]
    dlist_ins_prev(list, dlist_head(list), array[1]); //[1,0]
    dlist_ins_next(list, dlist_head(list), array[2]); //[1,2,0]
    dlist_ins_prev(list, NULL, array[3]); //[1,2,0]
    dlist_ins_next(list, dlist_tail(list), array[3]);  //[1,2,0,3]
    dlist_ins_prev(list, dlist_tail(list), array[4]); //[1,2,0,4,3]
    //dlist_int_print(list);

    element = dlist_search(list, array[0]);
    dlist_ins_prev(list, element, array[5]); //[1,2,5,0,4,3]
    dlist_ins_next(list, element, array[6]); //[1,2,5,0,6,4,3]
    //dlist_int_print(list);

    element = dlist_head(list);
    if(dlist_remove(list, element, (void **)&pi) == 0)  //[2,5,0,6,4,3]
        free(pi);

    //dlist_int_print(list);
    element = dlist_tail(list);
    if(dlist_remove(list, element, (void **)&pi) == 0)  //[2,5,0,6,4]
        free(pi);

    //dlist_int_print(list);
    element = dlist_search(list, array[0]);
    if(dlist_remove(list, element, (void **)&pi) == 0) //[2,5,6,4]
        free(pi);

    //dlist_int_print(list);
    while(dlist_size(list) > 2)
        if(dlist_remove(list, dlist_tail(list), (void **)&pi) == 0)
            free(pi);

    dlist_destroy(list);
    free(array);
}

void test_int1() {
    int ** array = (int **)malloc(sizeof(int*) * 8);
    int i = 0;
    DList * list = (DList *)malloc(sizeof(DList));
    DListElement * element;
    int * pi;

    for(i = 0; i < 8; i++) {
        pi = (int *)malloc(sizeof(int));
        *pi = i;
        array[i] = pi;
    }

    dlist_init_asm(list, free);
    list->match = match_int;

    dlist_ins_prev_asm(list, NULL, array[0]); //[0]
    dlist_ins_prev_asm(list, dlist_head(list), array[1]); //[1,0]
    dlist_ins_next_asm(list, dlist_head(list), array[2]); //[1,2,0]
    dlist_ins_prev_asm(list, NULL, array[3]); //[1,2,0]
    dlist_ins_next_asm(list, dlist_tail(list), array[3]);  //[1,2,0,3]
    dlist_ins_prev_asm(list, dlist_tail(list), array[4]); //[1,2,0,4,3]
    //dlist_int_print(list);

    element = dlist_search(list, array[0]);
    dlist_ins_prev_asm(list, element, array[5]); //[1,2,5,0,4,3]
    dlist_ins_next_asm(list, element, array[6]); //[1,2,5,0,6,4,3]
    //dlist_int_print(list);

    element = dlist_head(list);
    if(dlist_remove_asm(list, element, (void **)&pi) == 0)  //[2,5,0,6,4,3]
        free(pi);

    //dlist_int_print(list);
    element = dlist_tail(list);
    if(dlist_remove_asm(list, element, (void **)&pi) == 0)  //[2,5,0,6,4]
        free(pi);

    //dlist_int_print(list);
    element = dlist_search(list, array[0]);
    if(dlist_remove_asm(list, element, (void **)&pi) == 0) //[2,5,6,4]
        free(pi);

    //dlist_int_print(list);
    while(dlist_size(list) > 2)
        if(dlist_remove_asm(list, dlist_tail(list), (void **)&pi) == 0)
            free(pi);

    dlist_destroy_asm(list);
    free(array);
}

int main() {
    int i, j;

    time_t start,stop;
    for(j = 0; j < 10; j++) {
        start = time(NULL);
        for(i = 0; i < 100000000; i++)
            test_int();
        stop = time(NULL);
        printf("c Use Time:%ld\n",(stop-start));

        start = time(NULL);
        for(i = 0; i < 100000000; i++)
            test_int1();
        stop = time(NULL);
        printf("asm Use Time:%ld\n",(stop-start));
    }

    return 0;
}
