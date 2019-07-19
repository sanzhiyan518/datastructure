#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <stdio.h>

//散列函数
typedef unsigned int (*hash)(const void *data);
//键值比较函数
typedef int (*match)(const void * key1, const void * key2);
//元素销毁函数
typedef void (*destroy)(void * data);
//单链表结构体定义
typedef struct Node_ {
    struct Node_ * next;
    void * data;
} Node;


typedef struct HanshTable_ {
    int buckets;                //哈希桶数
    hash hash;                  //哈希函数
    match match;
    destroy destroy;          //元素销毁函数
    Node ** table;             //哈希桶数组
} HashTable;

void hashtable_init(HashTable * hashtable, int buckets, hash hash, match match, destroy  destroy);
void hashtable_init_asm(HashTable * hashtable, int buckets, hash hash, match match, destroy  destroy);

void hashtable_destroy(HashTable * hashtable);
void hashtable_destroy_asm(HashTable * hashtable);

int hashtable_insert(HashTable * hashtable,  void * data);
int hashtable_insert_asm(HashTable * hashtable, void * data);

int hashtable_remove(HashTable * hashtable,  void ** data);
int hashtable_remove_asm(HashTable * hashtable,  void ** data);

int hashtable_lookup(HashTable * hashtable, void ** data);
int hashtable_lookup_asm(HashTable * hashtable, void ** data);

#endif // HASHTABLE_H_
