#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>

typedef void (*destroy)(void * data);

//数组实现队列的结构体定义
typedef struct ArrayQueue {
    destroy destroy;   //元素销毁函数
    int capacity;         //队列总长度
    int size;             //当前队列的长度
    int front;           //队头
    int rear;             //队尾
    void ** data;     //元素数组
} ArrayQueue;

//单链表实现队列结构体定义
typedef struct Node_ {
    struct Node_ * next;
    void * data;
} Node;

typedef struct ListQueue_ {
    destroy destroy;  //元素销毁函数
    Node * front;       //队头
    Node * rear;        //队尾
} ListQueue;

//初始化队列
void arrayqueue_init(ArrayQueue * q, destroy destroy);
void arrayqueue_init_asm(ArrayQueue * q, destroy destroy);
void listqueue_init(ListQueue * q, destroy destroy);
void listqueue_init_asm(ListQueue * q, destroy destroy);

//队列销毁
void arrayqueue_destroy(ArrayQueue * q);
void arrayqueue_destroy_asm(ArrayQueue * q);
void listqueue_destroy(ListQueue * q);
void listqueue_destroy_asm(ListQueue * q);

//入队操作
int arrayqueue_enqueue(ArrayQueue * q, void * data);
int arrayqueue_enqueue_asm(ArrayQueue * q, void * data);
int listqueue_enqueue(ListQueue * q, void * data);
int listqueue_enqueue_asm(ListQueue * q, void * data);

//出队操作
int arrayqueue_dequeue(ArrayQueue * q, void ** data);
int arrayqueue_dequeue_asm(ArrayQueue * q, void ** data);
int listqueue_dequeue(ListQueue * q, void ** data);
int listqueue_dequeue_asm(ListQueue * q, void ** data);

//队列是否为空
#define arrayqueue_is_empty(queue) ((queue)->size == 0 ? 0 : -1)
#define listqueue_is_empty(queue) ((queue)->rear == NULL ? 0 : -1)

#endif // QUEUE_H_
