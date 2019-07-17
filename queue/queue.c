#include <stdlib.h>
#include <string.h>
#include "queue.h"


//��ʼ������
void arrayqueue_init(ArrayQueue * q, destroy destroy) {
    size_t s = (size_t)(q->capacity * sizeof(void *));
    q->destroy = destroy;
    q->size = 0;
    q->front = 0;
    q->rear = -1;
    //����Ԫ���ڴ�
    q->data = (void **) malloc(s);
    memset(q->data, 0, s);
}

void listqueue_init(ListQueue * q, destroy destroy) {
    q->destroy = destroy;
    q->front = NULL;
    q->rear = NULL;
}

//��������
void arrayqueue_destroy(ArrayQueue * q) {
    destroy destroy = q->destroy;

    //����Ԫ��
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

//��Ӳ���
int arrayqueue_enqueue(ArrayQueue * q, void * data) {
    //����������-1
    if(q->size == q->capacity)
        return -1;

    //��β��1
    q->rear++;
    //������ﵽ�������򷵻ص���ʼ
    if(q->rear >= q->capacity)
        q->rear = 0;

    //
    q->data[q->rear] = data;
    q->size ++;
    return 0;
}

int listqueue_enqueue(ListQueue * q, void * data) {
    Node * node = (Node *)malloc(sizeof(Node));

    //�ڴ����ʧ�ܷ���-1
    if(node == NULL)
        return -1;

    node->data = data;
    node->next = NULL;

    if(q->rear == NULL)
        //����Ϊ���޸Ķ���ͷ��Ԫ��
        q->front = node;
    else
        //�ڶ�β׷��
        q->rear->next = node;

    q->rear = node;
    return 0;
}

//���Ӳ���
int arrayqueue_dequeue(ArrayQueue * q, void ** data) {
    //�ն��з���-1
    if(q->size == 0)
        return -1;

    //ȡ����ͷԪ�ش���
    *data = q->data[q->front];
    q->data[q->front] = NULL;
    //����Ԫ������1
    q->size--;
    //��ͷ��1,�����������ص���ʼ
    if(++q->front == q->capacity)
        q->front = 0;

    return 0;
}

int listqueue_dequeue(ListQueue * q, void ** data) {
    Node * node = q->front;
    //�ն��з���-1
    if(node == NULL)
        return -1;

    //��������
    *data = node->data;
    //�޸Ķ���ͷ
    q->front = node->next;
    //���Ϊ��ջ�������б�βΪͷ
    if(q->front == NULL)
        q->rear = NULL;
    //�ͷ�Ԫ���ڴ�
    free(node);
    return 0;
}
