#include <stdlib.h>
#include <time.h>
#include "hashtable.h"

static unsigned int hash_int(const void * data)
{
    unsigned int key = *(unsigned int *)(data);
    key += ~(key << 15);
    key ^=  (key >> 10);
    key +=  (key << 3);
    key ^=  (key >> 6);
    key += ~(key << 11);
    key ^=  (key >> 16);
    return key;
}

static int match_int(const void * data1, const void * data2) {
    return (*(int *)data1 == *(int *)data2) ? 0 : -1;
}

void test_c() {
    HashTable * h = (HashTable *)malloc(sizeof(HashTable));
    int i, *p, j;

    hashtable_init(h, 10003, hash_int, match_int, free);

    srand((unsigned)time(NULL));

    for(i = 0; i < 10000; i++) {
        p = (int *)malloc(sizeof(int));
        *p = i;
        hashtable_insert(h, p);
    }

    for(i = 0; i < 10; i++) {
        p = &j;
        j =  rand() % 10000;
        if(hashtable_lookup(h, (void **)&p) != 0)
            printf("%d is not found!\n", j);
    }

    for(i = 0; i < 10; i++) {
        p = &j;
        j =  rand() % 10000;
        if(hashtable_remove(h, (void **)&p) == 0)
            free(p);
    }

    hashtable_destroy(h);
}

void test_asm() {
    HashTable * h = (HashTable *)malloc(sizeof(HashTable));
    int i, *p, j;

    hashtable_init_asm(h, 10003, hash_int, match_int, free);

    srand((unsigned)time(NULL));

    for(i = 0; i < 10000; i++) {
        p = (int *)malloc(sizeof(int));
        *p = i;
        hashtable_insert_asm(h, p);
    }

    for(i = 0; i < 10; i++) {
        p = &j;
        j =  rand() % 10000;
        if(hashtable_lookup_asm(h, (void **)&p) != 0)
            printf("%d is not found!\n", j);
    }

    for(i = 0; i < 10; i++) {
        p = &j;
        j =  rand() % 10000;
        if(hashtable_remove_asm(h, (void **)&p) == 0)
            free(p);
    }

    hashtable_destroy_asm(h);
}


#define MAX_LOOP 1000

int main() {
    int i, j;
    clock_t  t = 0;


    printf("HashTable's size is %ld\n", sizeof(HashTable));
    printf("The member of HashTable hash's offset is %ld\n", (size_t)( &((HashTable *)0)->hash));
    printf("The member of HashTable match's offset is %ld\n", (size_t)( &((HashTable *)0)->match));
    printf("The member of HashTable destroy's offset is %ld\n", (size_t)( &((HashTable *)0)->destroy));
    printf("The member of HashTable table's offset is %ld\n", (size_t)( &((HashTable *)0)->table));

    for(j= 0; j < 10; j++) {
        t = clock();
        for(i= 0; i < MAX_LOOP; i++)
            test_c();
        printf("C chain hashtable Use Time:%f ms\n", (double)(clock() - t)/CLOCKS_PER_SEC * 1000);

        t = clock();
        for(i= 0; i < MAX_LOOP; i++)
            test_asm();
        printf("ASM chain hashtable Use Time:%f ms\n", (double)(clock() - t)/CLOCKS_PER_SEC * 1000);
    }
    return 0;
}
