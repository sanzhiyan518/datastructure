#include "queue.h"
#include <stdlib.h>

QueueList * queuelist_init() {
    QueueList * q = (QueueList *)malloc(sizeof(*q));
    //��ʼ����ͷ���β��Ϊ��
    q->front = q->rear = NULL;
    return q;
}

void queuelist_destroy(QueueList * q) {
    if(q == NULL)
        return;

    //�����ڴ��ͷ�
    Node * front = q->front;
    while(front != NULL) {
        Node * tmp = front;
        front = tmp->next;
        free(tmp);
    }

    //�����ڴ��ͷ�
    free(q);
}

int queuelist_empty(QueueList * q) {
    //��ͷ�Ƿ��
    return q == NULL ? -1 : (q->front == NULL ? 0 : -1);
}

int queuelist_enter(QueueList * q, void * data) {
    if(q == NULL)
        return -1;

    //Ԫ���ڴ����
    Node * n = (Node * )malloc(sizeof(*n));
    n->data = data;
    //��Ԫ�ؼ�������β��
    n->next = NULL;
    //ԭ��β����Ϊ�գ�������
    if(q->rear != NULL)
        q->rear->next = n;

    if(q->front == NULL)
        //����ԭ��Ϊ�նӣ�����
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
