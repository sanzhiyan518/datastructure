#include <stdio.h>
#include <time.h>
#include "slist.h"
static inline int compare_int(void * a, void * b) {
    return (*(int *)a == *(int *)b) ? 1 : 0;
}

//´òÓ¡
static void list_print(List * list) {
    ListElement * element;
    for_each(element, list) {
        printf("--%d--", *(int *)(element->data));
    }
    printf("\n");
}

int main() {
    int arr[5] = {1,2,3,4,5};
    int i = 1;
    List * l;
    time_t start,stop;

//    start = time(NULL);
//    for(i = 0; i <10000000; i++) {
//        l = list_init(compare_int);
//        list_insert_(l, NULL, (void *)arr);
//        list_insert(l, NULL, (void *)(arr + 1));
//        list_insert(l, NULL, (void *)(arr + 2));
//        list_insert(l, NULL, (void *)(arr + 3));
//        list_insert(l, NULL, (void *)(arr + 4));
//        list_destroy(l);
//    }
////
//    stop = time(NULL);
//    printf("Use Time:%ld\n",(stop-start));
//    start = time(NULL);
//    for(i = 0; i <10000000; i++) {
//        l = list_init_asm(compare_int);
//        list_insert(l, NULL, (void *)arr);
//        list_insert(l, NULL, (void *)(arr + 1));
//        list_insert(l, NULL, (void *)(arr + 2));
//        list_insert(l, NULL, (void *)(arr + 3));
//        list_insert(l, NULL, (void *)(arr + 4));
//        list_destroy_asm(l);
//    }
//    stop = time(NULL);
//    printf("Use Time:%ld\n",(stop-start));
//    printf("%d\n", mysizeof(int));
    l = list_init_asm(compare_int);
    list_insert_asm(l, NULL, (void *)arr);
    list_insert_asm(l, NULL, (void *)(arr + 2));
    list_print(l);
    ListElement * e = list_search_asm(l, &i);
    list_insert_asm(l, e, (void *)(arr + 3));
    list_insert_asm(l, e, (void *)(arr + 1));
    list_append(l, (void *)(arr + 4));
    list_print(l);
    list_delete_asm(l, (void *)(arr));
    list_print(l);
    list_delete_asm(l, (void *)(arr + 1));
    list_print(l);
    list_delete_asm(l, (void *)(arr + 3));
    list_print(l);
    list_delete_asm(l, (void *)(arr + 2));
    list_print(l);
    list_destroy_asm(l);
    return 0;
}
