#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>

typedef void (*destroy)(void * data);

//����ʵ�ֶ��еĽṹ�嶨��
typedef struct ArrayQueue {
    destroy destroy;   //Ԫ�����ٺ���
    int capacity;         //�����ܳ���
    int size;             //��ǰ���еĳ���
    int front;           //��ͷ
    int rear;             //��β
    void ** data;     //Ԫ������
} ArrayQueue;

//������ʵ�ֶ��нṹ�嶨��
typedef struct Node_ {
    struct Node_ * next;
    void * data;
} Node;

typedef struct ListQueue_ {
    destroy destroy;  //Ԫ�����ٺ���
    Node * front;       //��ͷ
    Node * rear;        //��β
} ListQueue;

//��ʼ������
void arrayqueue_init(ArrayQueue * q, destroy destroy);
void arrayqueue_init_asm(ArrayQueue * q, destroy destroy);
void listqueue_init(ListQueue * q, destroy destroy);
void listqueue_init_asm(ListQueue * q, destroy destroy);

//��������
void arrayqueue_destroy(ArrayQueue * q);
void arrayqueue_destroy_asm(ArrayQueue * q);
void listqueue_destroy(ListQueue * q);
void listqueue_destroy_asm(ListQueue * q);

//��Ӳ���
int arrayqueue_enqueue(ArrayQueue * q, void * data);
int arrayqueue_enqueue_asm(ArrayQueue * q, void * data);
int listqueue_enqueue(ListQueue * q, void * data);
int listqueue_enqueue_asm(ListQueue * q, void * data);

//���Ӳ���
int arrayqueue_dequeue(ArrayQueue * q, void ** data);
int arrayqueue_dequeue_asm(ArrayQueue * q, void ** data);
int listqueue_dequeue(ListQueue * q, void ** data);
int listqueue_dequeue_asm(ListQueue * q, void ** data);

//�����Ƿ�Ϊ��
#define arrayqueue_is_empty(queue) ((queue)->size == 0 ? 0 : -1)
#define listqueue_is_empty(queue) ((queue)->rear == NULL ? 0 : -1)

#endif // QUEUE_H_
