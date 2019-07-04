#include <stdlib.h>
#include "queue.h"

Queue * queue_init(int length) {
    Queue * q = (Queue *)malloc(sizeof(*q));
    q->length = length;
    q->size = 0;
    q->front = -1;
    q->rear = 0;
    q->data = (void **)malloc(sizeof(void *) * length);
    return q;
}

void queue_destroy(Queue * q) {
    if(q == NULL)
        return;
    free(q->data);
    free(q);
}
int queue_full(Queue * q) {
    return q == NULL ? -1 : (q->size == q->length ? 0 :-1);
}

int queue_empty(Queue * q) {
    return q == NULL ? -1 : (q->size == 0 ? 0 : -1);
}

int queue_enter(Queue * q, void * data) {
    if(queue_full(q) == 0)
        return -1;

    q->front++;
    q->size++;
    if(q->front >= q->length)
        q->front = 0;
    q->data[q->front] = data;
    return 0;
}

int queue_delete(Queue * q, void **data) {
    if(queue_empty(q) == 0)
        return -1;
    *data = q->data[q->rear];
    q->rear++;
    q->size--;
    if(q->rear >= q->length)
        q->rear = 0;
    return 0;
}
