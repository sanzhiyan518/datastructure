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
    //��ϣͰ��������ڴ�,������
    table =  (Node **)malloc(l);
    hashtable->table = table;
    memset(table, 0, l);
}

void hashtable_destroy(HashTable * hashtable) {
    Node ** table = hashtable->table;
    Node ** start = table, **end = table + hashtable->buckets;
    destroy destroy = hashtable->destroy;

    //��ϣ�����Ա����
    memset(hashtable, 0, sizeof(HashTable));

    //�ͷŹ�ϣͰ������ṩ��Ԫ�����ٺ��������ÿԪ�����ݳ�Ա����Ԫ�����ٺ���
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

    //�ͷŹ�ϣͰ�����ڴ��
    free(table);
}

int hashtable_insert(HashTable * hashtable, void * data) {
    //��ȡ��ϣͰ�Ĳ�λ
    int hash = hashtable->hash(data) % (hashtable->buckets);
    Node ** table = hashtable->table;
    Node * bucket = table[hash], * node;

    //��������Ԫ��
    node = (Node *)malloc(sizeof(Node));

    if(node == NULL)
        return -1;

    node->data = data;
    node->next = NULL;
    //Ԫ�������ϣͰ
    if(bucket == NULL) {
        //�˲�λ��ϣͰ��
        table[hash] = node;
        node->next = NULL;
    } else {
        //����ͷ֮��
        node->next = bucket->next;
        bucket->next = node;
    }
    return 0;
}

int hashtable_remove(HashTable * hashtable,  void ** data) {
    //��ȡ��ϣͰ�Ĳ�λ
    int hash = hashtable->hash(*data) % (hashtable->buckets);
    Node ** table = hashtable->table;
    Node * prev = NULL;
    Node * node = table[hash];
    match match = hashtable->match;

    //������ϣͰ������Ԫ�أ���ȡɾ��Ԫ��
    while(node != NULL) {
        //�Ƚ�Ԫ���Ƿ����
        if(match(*data, node->data) == 0) {
            if(prev == NULL)
                //Ϊ����ͷ������Ҫ�޸Ĺ�ϣͰ����
                table[hash] = node->next;
             else
                //�޸�ǰ���ĺ��ΪԪ�صĺ��
                prev->next = node->next;

            //�������ݣ��ͷ�Ԫ���ڴ�飬����0
            *data = node->data;
            free(node);
            return 0;
        }
        //
        prev = node;
        node = node->next;
    }

    //δ�ҵ�����-1
    return -1;
}

int hashtable_lookup(HashTable * hashtable, void ** data) {
    //��ȡ��ϣͰ�Ĳ�λ
    int hash = hashtable->hash(*data) % (hashtable->buckets);
    Node * node = hashtable->table[hash];
    match match = hashtable->match;

    //������ϣͰ������Ԫ�أ���ȡɾ��Ԫ��
    while(node != NULL) {
        //�Ƚ�Ԫ���Ƿ����
        if(match(*data, node->data) == 0) {
            *data = node->data;
            return 0;
        }
        node = node->next;
    }

    //δ�ҵ�����-1
    return -1;
}
