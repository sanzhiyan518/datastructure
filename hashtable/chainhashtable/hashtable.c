#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

void hashtable_init(HashTable * hashtable, int buckets, hash hash, match match, destroy  destroy) {
    Node **table;
    int l = buckets * sizeof(Node *);

    hashtable->buckets = buckets;
    hashtable->hash = hash;
    hashtable->match = match;
    hashtable->destroy = destroy;
    //哈希桶数组分配内存,并清零
    table =  (Node **)malloc(l);
    hashtable->table = table;
    memset(table, 0, l);
}

void hashtable_destroy(HashTable * hashtable) {
    Node ** table = hashtable->table;
    Node ** start = table, **end = table + hashtable->buckets;
    destroy destroy = hashtable->destroy;

    //哈希结体成员置零
    memset(hashtable, 0, sizeof(HashTable));

    //释放哈希桶，如果提供了元素销毁函数，则对每元素数据成员调用元素销毁函数
    while(start < end ) {
        Node * bucket = *start, * prev;
        while(bucket != NULL) {
            prev = bucket;
            bucket = bucket->next;
            if(destroy)
                free(prev->data);
            free(prev);
        }
        start ++;
    }

    //释放哈希桶数组内存块
    free(table);
}

int hashtable_insert(HashTable * hashtable, void * data) {
    //获取哈希桶的槽位
    int hash = hashtable->hash(data) % (hashtable->buckets);
    Node ** table = hashtable->table;
    Node * bucket = table[hash], * node;

    //分配链表元素
    node = (Node *)malloc(sizeof(Node));

    if(node == NULL)
        return -1;

    node->data = data;
    node->next = NULL;
    //元素链入哈希桶
    if(bucket == NULL) {
        //此槽位哈希桶空
        table[hash] = node;
        node->next = NULL;
    } else {
        //加入头之后
        node->next = bucket->next;
        bucket->next = node;
    }
    return 0;
}

int hashtable_remove(HashTable * hashtable,  void ** data) {
    //获取哈希桶的槽位
    int hash = hashtable->hash(*data) % (hashtable->buckets);
    Node ** table = hashtable->table;
    Node * prev = NULL;
    Node * node = table[hash];
    match match = hashtable->match;

    //遍历哈希桶中链表元素，获取删除元素
    while(node != NULL) {
        //比较元素是否相等
        if(match(*data, node->data) == 0) {
            if(prev == NULL)
                //为链表头，则需要修改哈希桶数组
                table[hash] = node->next;
             else
                //修改前驱的后继为元素的后继
                prev->next = node->next;

            //传出数据，释放元素内存块，返回0
            *data = node->data;
            free(node);
            return 0;
        }
        //
        prev = node;
        node = node->next;
    }

    //未找到返回-1
    return -1;
}

int hashtable_lookup(HashTable * hashtable, void ** data) {
    //获取哈希桶的槽位
    int hash = hashtable->hash(*data) % (hashtable->buckets);
    Node * node = hashtable->table[hash];
    match match = hashtable->match;

    //遍历哈希桶中链表元素，获取删除元素
    while(node != NULL) {
        //比较元素是否相等
        if(match(*data, node->data) == 0) {
            *data = node->data;
            return 0;
        }
        node = node->next;
    }

    //未找到返回-1
    return -1;
}
