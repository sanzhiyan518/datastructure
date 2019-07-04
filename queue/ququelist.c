#include "queue.h"
#include <stdlib.h>

QueueList * queuelist_init() {
    QueueList * q = (QueueList *)malloc(sizeof(*q));
    //初始化队头与队尾都为空
    q->front = q->rear = NULL;
    return q;
}

void queuelist_destroy(QueueList * q) {
    if(q == NULL)
        return;

    //链表内存释放
    Node * front = q->front;
    while(front != NULL) {
        Node * tmp = front;
        front = tmp->next;
        free(tmp);
    }

    //队列内存释放
    free(q);
}

int queuelist_empty(QueueList * q) {
    //队头是否空
    return q == NULL ? -1 : (q->front == NULL ? 0 : -1);
}

int queuelist_enter(QueueList * q, void * data) {
    if(q == NULL)
        return -1;

    //元素内存分配
    Node * n = (Node * )malloc(sizeof(*n));
    n->data = data;
    //新元素加入链表尾部
    n->next = NULL;
    //原队尾若不为空，入链表
    if(q->rear != NULL)
        q->rear->next = n;

    if(q->front == NULL)
        //表明原来为空队，设置
        q->front = n;

    q->rear = n;
    return 0;
}

int queuelist_delete(QueueList * q, void ** data) {
    if(queuelist_empty(q) == 0)
        return -1;

    Node * n = q->front;
    *data = n->data;
    q->front = n->next;
    free(n);
    return 0;
}
