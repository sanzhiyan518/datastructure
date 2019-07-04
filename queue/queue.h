#ifndef QUEUE_H_
#define QUEUE_H_

//数组实现队列的结构体定义
typedef struct Queue {
    int length;     //队列总长度
    int size;       //当前队列的长度
    int front;    //队头
    int rear;    //队尾
    void ** data;   //元素数组
} Queue;

//队列创建
Queue * queue_init(int length);
Queue * queue_init_asm(int length);

//队列销毁
void queue_destroy(Queue * q);
void queue_destroy_asm(Queue * q);

//入队操作
int queue_enter(Queue * q, void * data);
int queue_enter_asm(Queue * q, void * data);

//出队操作
int queue_delete(Queue * q, void ** data);
int queue_delete_asm(Queue * q, void ** data);

//队列是否己满
int queue_full(Queue * q);
int queue_full_asm(Queue * q);

//队列是否为空
int queue_empty(Queue * q);
int queue_empty_asm(Queue * q);

//单链表实现队列
typedef struct Node {
    struct Node * next;
    void * data;
} Node;

typedef struct QueueList {
    Node * front;       //队头
    Node * rear;        //队尾
} QueueList;

//队列构建
QueueList * queuelist_init();
QueueList * queuelist_init_asm();

//队列销毁
void queuelist_destroy(QueueList * q);
void queuelist_destroy_asm(QueueList * q);

//队列是否为空
int queuelist_empty(QueueList * q);
int queuelist_empty_asm(QueueList * q);

//队列入队
int queuelist_enter(QueueList * q, void * data);
int queuelist_enter_asm(QueueList * q, void * data);

//队列出队
int queuelist_delete(QueueList * q, void ** data);
int queuelist_delete_asm(QueueList * q, void ** data);

#endif // QUEUE_H_
