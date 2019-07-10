#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "slist.h"

static int match_int(const void * data1, const void * data2) {
    return (*(int *)data1 == *(int *)data2) ? 1 : 0;
}

static void list_int_print(List * list) {
    ListElement * element = list_head(list);

    while(element != NULL) {
        printf("--%d--", *(int *)(list_data(element)));
        element = list_next(element);
    }
    printf("\n");
}

static ListElement * list_search(List * list, void * data) {
    ListElement * element = list_head(list);
    match match = list->match;

    if(match == NULL)
        return NULL;

    while(element != NULL) {
        if(match(data, list_data(element)))
            return element;
        element = list_next(element);
    }

    return NULL;
}

void test_int1() {
    int array1[100], array2[100];
    int l1 = sizeof(array1)/sizeof(array1[0]), l2 = sizeof(array2)/sizeof(array2[0]);
    List * list = (List *)malloc(sizeof(List));
    int i = 0, j;
    int * pi;
    ListElement * prev;

    for(; i < l1; i++)
        array1[i] = i;

    for(i = 0; i < l2; i++)
        array2[i] = l1 + i;


    list_init(list, NULL);
    list->match = match_int;

    for(i = 0; i < l1; i++)
        list_ins_next(list, NULL, (void *)(array1 + i));

    srand((unsigned)time(NULL));

    for(i = 0; i < l2; i++) {
        j = rand() % l1;
        prev = list_search(list, (void *)(array1 + j));
        list_ins_next(list, prev, (void *)(array2 + i));
    }
    //list_int_print(list);


    for(i = 0; i < l1; i++) {
        list_rem_next(list, NULL, (void **)&pi);
    }

    for(i = 0; i < l2/2; i++) {
        j = rand() % l2;
        prev = list_search(list, (void *)(array2 + j));
        if(prev)
            list_rem_next(list, prev, (void **)&pi);
    }

    while(list_size(list) > 10) {
        list_rem_next(list, NULL, (void **)&pi);
    }

    list_destroy(list);
    free(list);
}

void test_int2() {
    int l1 = 100, l2 = 100;
    int  ** array1 = (int **)malloc(sizeof(int *) * l1);
    int ** array2 = (int **)malloc(sizeof(int *) * l2);
    int * pi;
    List * list = (List *)malloc(sizeof(List));
    int i = 0, j;
    ListElement * prev;

    for(; i < l1; i++) {
        pi = (int *)malloc(sizeof(int));
        *pi = i;
        array1[i] = pi;
    }

    for(i = 0; i < l2; i++) {
        pi = (int *)malloc(sizeof(int));
        *pi = i + l1;
        array2[i] = pi;
    }

    list_init(list, free);
    list->match = match_int;

    for(i = 0; i < l1; i++)
        list_ins_next(list, NULL, (void *)(array1[i]));

    srand((unsigned)time(NULL));

    for(i = 0; i < l2; i++) {
        j = rand() % l1;
        prev = list_search(list, (void *)(array1[j]));
        list_ins_next(list, prev, (void *)(array2[i]));
    }
    //list_int_print(list);

    for(i = 0; i < l1; i++) {
        if(list_rem_next(list, NULL, (void **)&pi) == 0)
            free(pi);
    }

    for(i = 0; i < l2/2; i++) {
        j = rand() % l2;
        prev = list_search(list, (void *)(array2[j]));
        if(prev)
            if(list_rem_next(list, prev, (void **)&pi) == 0)
                free(pi);
    }

    while(list_size(list) > 10) {
        list_rem_next(list, NULL, (void **)&pi);
        free(pi);
    }

    list_destroy(list);
    free(array1);
    free(array2);
    free(list);
}

void test_int3() {
    int array1[100], array2[100];
    int l1 = sizeof(array1)/sizeof(array1[0]), l2 = sizeof(array2)/sizeof(array2[0]);
    List * list = (List *)malloc(sizeof(List));
    int i = 0, j;
    int * pi;
    ListElement * prev;

    for(; i < l1; i++)
        array1[i] = i;

    for(i = 0; i < l2; i++)
        array2[i] = l1 + i;


    list_init_asm(list, NULL);
    list->match = match_int;

    for(i = 0; i < l1; i++)
        list_ins_next_asm(list, NULL, (void *)(array1 + i));

    srand((unsigned)time(NULL));

    for(i = 0; i < l2; i++) {
        j = rand() % l1;
        prev = list_search(list, (void *)(array1 + j));
        list_ins_next_asm(list, prev, (void *)(array2 + i));
    }

    for(i = 0; i < l1; i++) {
        list_rem_next_asm(list, NULL, (void **)&pi);
    }

    for(i = 0; i < l2/2; i++) {
        j = rand() % l2;
        prev = list_search(list, (void *)(array2 + j));
        if(prev)
            list_rem_next_asm(list, prev, (void **)&pi);
    }

    while(list_size(list) > 10) {
        list_rem_next_asm(list, NULL, (void **)&pi);
    }

    list_destroy_asm(list);
    free(list);
}

void test_int4() {
    int l1 = 100, l2 = 100;
    int  ** array1 = (int **)malloc(sizeof(int *) * l1);
    int ** array2 = (int **)malloc(sizeof(int *) * l2);
    int * pi;
    List * list = (List *)malloc(sizeof(List));
    int i = 0, j;
    ListElement * prev;

    for(; i < l1; i++) {
        pi = (int *)malloc(sizeof(int));
        *pi = i;
        array1[i] = pi;
    }

    for(i = 0; i < l2; i++) {
        pi = (int *)malloc(sizeof(int));
        *pi = i + l1;
        array2[i] = pi;
    }

    list_init_asm(list, free);
    list->match = match_int;

    for(i = 0; i < l1; i++)
        list_ins_next_asm(list, NULL, (void *)(array1[i]));

    srand((unsigned)time(NULL));

    for(i = 0; i < l2; i++) {
        j = rand() % l1;
        prev = list_search(list, (void *)(array1[j]));
        list_ins_next_asm(list, prev, (void *)(array2[i]));
    }

    for(i = 0; i < l1; i++) {
        if(list_rem_next_asm(list, NULL, (void **)&pi) == 0)
            free(pi);
    }

    for(i = 0; i < l2/2; i++) {
        j = rand() % l2;
        prev = list_search(list, (void *)(array2[j]));
        if(prev)
            if(list_rem_next_asm(list, prev, (void **)&pi) == 0)
                free(pi);
    }

    while(list_size(list) > 10) {
        list_rem_next_asm(list, NULL, (void **)&pi);
        free(pi);
    }

    list_destroy_asm(list);
    free(array1);
    free(array2);
    free(list);
}

int main() {
    int i;
    time_t start,stop;

    start = time(NULL);
    for(i = 0; i < 100000; i++) {
        test_int1();
        test_int2();
    }
    stop = time(NULL);
    printf("Use Time:%ld\n",(stop-start));
    start = time(NULL);
    for(i = 0; i < 100000; i++) {
        test_int3();
        test_int4();
    }
    stop = time(NULL);
    printf("Use Time:%ld\n",(stop-start));
    return 0;
}
