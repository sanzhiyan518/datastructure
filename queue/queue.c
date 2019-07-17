#include <stdlib.h>
#include <string.h>
#include "queue.h"


//初始化队列
void arrayqueue_init(ArrayQueue * q, destroy destroy) {
    size_t s = (size_t)(q->capacity * sizeof(void *));
    q->destroy = destroy;
    q->size = 0;
    q->front = 0;
    q->rear = -1;
    //分配元素内存
    q->data = (void **) malloc(s);
    memset(q->data, 0, s);
}

void listqueue_init(ListQueue * q, destroy destroy) {
    q->destroy = destroy;
    q->front = NULL;
    q->rear = NULL;
}

//队列销毁
void arrayqueue_destroy(ArrayQueue * q) {
    destroy destroy = q->destroy;

    //销毁元素
    if(destroy) {
        int i = 0;
        for(; i < q->capacity; i++)
            if(q->data[i] != NULL)
                destroy(q->data[i]);
    }

    q->size = 0;
    q->front = 0;
    q->rear = -1;
    free(q->data);
    q->data = NULL;
}

void listqueue_destroy(ListQueue * q) {
    destroy destroy = q->destroy;
    Node * node = q->front, * prev;

    while(node != NULL) {
        prev = node;
        node = node->next;
        if(destroy)
            destroy(prev->data);
        free(prev);
    }

    q->front = q->rear = NULL;
}

//入队操作
int arrayqueue_enqueue(ArrayQueue * q, void * data) {
    //队列满返回-1
    if(q->size == q->capacity)
        return -1;

    //队尾加1
    q->rear++;
    //如果己达到容量，则返回到起始
    if(q->rear >= q->capacity)
        q->rear = 0;

    //
    q->data[q->rear] = data;
    q->size ++;
    return 0;
}

int listqueue_enqueue(ListQueue * q, void * data) {
    Node * node = (Node *)malloc(sizeof(Node));

    //内存分配失败返回-1
    if(node == NULL)
        return -1;

    node->data = data;
    node->next = NULL;

    if(q->rear == NULL)
        //队列为空修改队列头新元素
        q->front = node;
    else
        //在队尾追加
        q->rear->next = node;

    q->rear = node;
    return 0;
}

//出队操作
int arrayqueue_dequeue(ArrayQueue * q, void ** data) {
    //空队列返回-1
    if(q->size == 0)
        return -1;

    //取出队头元素传出
    *data = q->data[q->front];
    q->data[q->front] = NULL;
    //队列元素数减1
    q->size--;
    //队头加1,己达容量返回到起始
    if(++q->front == q->capacity)
        q->front = 0;

    return 0;
}

int listqueue_dequeue(ListQueue * q, void ** data) {
    Node * node = q->front;
    //空队列返回-1
    if(node == NULL)
        return -1;

    //传出数据
    *data = node->data;
    //修改队列头
    q->front = node->next;
    //如果为空栈则设置列表尾为头
    if(q->front == NULL)
        q->rear = NULL;
    //释放元素内存
    free(node);
    return 0;
}
