#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <stdio.h>

//ɢ�к���
typedef unsigned int (*hash)(const void *data);
//��ֵ�ȽϺ���
typedef int (*match)(const void * key1, const void * key2);
//Ԫ�����ٺ���
typedef void (*destroy)(void * data);
//������ṹ�嶨��
typedef struct Node_ {
    struct Node_ * next;
    void * data;
} Node;


typedef struct HanshTable_ {
    int buckets;                //��ϣͰ��
    hash hash;                  //��ϣ����
    match match;
    destroy destroy;          //Ԫ�����ٺ���
    Node ** table;             //��ϣͰ����
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
